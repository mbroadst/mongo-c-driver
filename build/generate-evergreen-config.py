#!/usr/bin/env python
#
# Copyright 2018-present MongoDB, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Generate C Driver's config.yml for Evergreen testing.

We find that generating configuration from Python data structures and a template
file is more legible than Evergreen's matrix syntax or a handwritten file.

Written for Python 2.6+, requires Jinja 2 for templating.
"""

import sys
from collections import namedtuple, OrderedDict as OD
from itertools import product
from os.path import dirname, join as joinpath, normpath

try:
    import yaml
    import yamlordereddictloader
    from jinja2 import Environment, FileSystemLoader
except ImportError:
    sys.stderr.write("try 'pip install -r build/requirements.txt'")
    raise

this_dir = dirname(__file__)
evergreen_dir = normpath(joinpath(this_dir, '../.evergreen'))


class Task(object):
    name_prefix = 'test'

    def __new__(cls, *args, **kwargs):
        self = super(Task, cls).__new__(cls, *args, **kwargs)
        self.tags = []
        self.options = OD()
        self.depends_on = []
        return self

    def display(self, axis_name):
        value = getattr(self, axis_name)
        # E.g., if self.auth is False, return 'noauth'.
        if value is False:
            return 'no' + axis_name

        if value is True:
            return axis_name

        return value

    def on_off(self, axis_name):
        return 'on' if getattr(self, axis_name) else 'off'

    def as_dict(self):
        task = OD([('name', self.name), ('tags', self.tags)])
        task.update(self.options)
        if self.depends_on:
            task['depends_on'] = OD([
                ('name', name) for name in self.depends_on
            ])

        task['commands'] = commands = []
        if self.depends_on:
            commands.append(OD([
                ('func', 'fetch build'),
                ('vars', {'BUILD_NAME': self.depends_on[0]}),
            ]))
        return task

    def to_yaml(self):
        return yaml.dump(self.as_dict(), Dumper=yamlordereddictloader.Dumper)


integration_task_axes = OD([
    ('valgrind', ['valgrind', False]),
    ('asan', ['asan', False]),
    ('coverage', ['coverage', False]),
    ('version', ['latest', '4.0', '3.6', '3.4', '3.2', '3.0']),
    ('topology', ['server', 'replica_set', 'sharded_cluster']),
    ('auth', [True, False]),
    ('sasl', ['sasl', 'sspi', False]),
    ('ssl', ['openssl', 'darwinssl', 'winssl', False]),
])


class IntegrationTask(Task, namedtuple('Task', tuple(integration_task_axes))):
    @property
    def name(self):
        def name_part(axis_name):
            part = self.display(axis_name)
            if part == 'replica_set':
                return 'replica-set'
            elif part == 'sharded_cluster':
                return 'sharded'
            return part

        return self.name_prefix + '-' + '-'.join(
            name_part(axis_name) for axis_name in integration_task_axes
            if getattr(self, axis_name) or axis_name in ('auth', 'sasl', 'ssl'))

    def as_dict(self):
        task = super(IntegrationTask, self).as_dict()
        commands = task['commands']
        if self.coverage:
            commands.append(OD([
                ('func', 'debug-compile-coverage-notest-%s-%s' % (
                    self.display('sasl'), self.display('ssl')
                )),
            ]))
        commands.append(OD([
            ('func', 'bootstrap mongo-orchestration'),
            ('vars', OD([
                ('VERSION', self.version),
                ('TOPOLOGY', self.topology),
                ('AUTH', 'auth' if self.auth else 'noauth'),
                ('SSL', self.display('ssl')),
            ])),
        ]))
        commands.append(OD([
            ('func', 'run tests'),
            ('vars', OD([
                ('VALGRIND', self.on_off('valgrind')),
                ('ASAN', self.on_off('asan')),
                ('AUTH', self.display('auth')),
                ('SSL', self.display('ssl')),
            ])),
        ]))
        if self.coverage:
            commands.append(OD([
                ('func', 'update codecov.io'),
            ]))

        return task


auth_task_axes = OD([
    ('sasl', ['sasl', 'sspi', False]),
    ('ssl', ['openssl', 'darwinssl', 'winssl']),
])


class AuthTask(Task, namedtuple('Task', tuple(auth_task_axes))):
    name_prefix = 'authentication-tests'

    @property
    def name(self):
        rv = self.name_prefix + '-' + self.display('ssl')
        if self.sasl:
            return rv
        else:
            return rv + '-nosasl'

    def as_dict(self):
        task = super(AuthTask, self).as_dict()
        task['commands'].append(OD([
            ('func', 'run auth tests'),
        ]))
        return task


def matrix(cell_class, axes):
    return set(cell_class(*cell) for cell in product(*axes.values()))


class Prohibited(Exception):
    pass


def require(rule):
    if not rule:
        raise Prohibited()


def prohibit(rule):
    if rule:
        raise Prohibited()


def both_or_neither(rule0, rule1):
    if rule0:
        require(rule1)
    else:
        prohibit(rule1)


def allow_integration_test_task(task):
    if task.valgrind:
        prohibit(task.asan)
        prohibit(task.sasl)
        require(task.ssl in ('openssl', False))
        prohibit(task.coverage)
        # Valgrind only with auth+SSL or no auth + no SSL.
        if task.auth:
            require(task.ssl == 'openssl')
        else:
            prohibit(task.ssl)

    if task.auth:
        require(task.ssl)

    if task.sasl == 'sspi':
        # Only one task.
        require(task.topology == 'server')
        require(task.version == 'latest')
        require(task.ssl == 'winssl')
        require(task.auth)

    if not task.ssl:
        prohibit(task.sasl)

    if task.coverage:
        prohibit(task.sasl)

        if task.auth:
            require(task.ssl == 'openssl')
        else:
            prohibit(task.ssl)

    if task.asan:
        prohibit(task.sasl)
        prohibit(task.coverage)

        # Address sanitizer only with auth+SSL or no auth + no SSL.
        if task.auth:
            require(task.ssl == 'openssl')
        else:
            prohibit(task.ssl)


def make_integration_test_tasks():
    tasks_list = []
    for task in matrix(IntegrationTask, integration_task_axes):
        try:
            allow_integration_test_task(task)
        except Prohibited:
            continue

        if task.valgrind:
            task.tags.append('test-valgrind')
            task.options['exec_timeout_secs'] = 7200
        elif task.coverage:
            task.tags.append('test-coverage')
            task.options['exec_timeout_secs'] = 3600
        elif task.asan:
            task.tags.append('test-asan')
            task.options['exec_timeout_secs'] = 3600
        else:
            task.tags.append(task.topology)
            task.tags.append(task.version)
            task.tags.extend([task.display('ssl'),
                              task.display('sasl'),
                              task.display('auth')])

        # E.g., test-latest-server-auth-sasl-ssl needs debug-compile-sasl-ssl.
        if task.valgrind:
            task.depends_on.append('debug-compile-valgrind-memcheck')
        elif task.asan:
            task.depends_on.append('debug-compile-asan-clang-nosasl-%s' % (
                task.display('ssl'),))
        elif not task.coverage:
            task.depends_on.append('debug-compile-%s-%s' % (
                task.display('sasl'), task.display('ssl')))

        tasks_list.append(task)

    return tasks_list


def allow_auth_test_task(task):
    both_or_neither(task.ssl == 'winssl', task.sasl == 'sspi')
    if not task.sasl:
        require(task.ssl == 'openssl')


def make_auth_test_tasks():
    tasks_list = []
    for task in matrix(AuthTask, auth_task_axes):
        try:
            allow_auth_test_task(task)
        except Prohibited:
            continue

        task.tags.extend(['authentication-tests',
                         task.display('ssl'),
                         task.display('sasl')])

        task.depends_on.append('debug-compile-%s-%s' % (
            task.display('sasl'), task.display('ssl')))

        tasks_list.append(task)

    return tasks_list


env = Environment(loader=FileSystemLoader(this_dir),
                  trim_blocks=True,
                  lstrip_blocks=True,
                  extensions=['jinja2.ext.loopcontrols'])

env.filters['tag_list'] = lambda value: (
        '[' + ', '.join('"%s"' % (tag,) for tag in value) + ']')

print('.evergreen/config.yml')
f = open(joinpath(evergreen_dir, 'config.yml'), 'w+')
t = env.get_template('config.yml.template')
f.write(t.render(globals()))
f.write('\n')