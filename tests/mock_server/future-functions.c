/**************************************************
 *
 * Generated by build/generate-future-functions.py.
 *
 * DO NOT EDIT THIS FILE.
 *
 *************************************************/

/*
 * Define two sets of functions: background functions and future functions.

 * A background function like background_mongoc_cursor_next runs a driver
 * operation on a thread.

 * A future function like future_mongoc_cursor_next launches the background
 * operation and returns a future_t that will resolve when the operation
 * finishes.
 *
 * These are used with mock_server_t so you can run the driver on a thread while
 * controlling the server from the main thread.
 */

#include "mongoc-topology-private.h"

#include "future-functions.h"


static void *
background_mongoc_bulk_operation_execute (void *data)
{
   future_t *future = (future_t *) data;
   future_value_t return_value;

   return_value.type = future_value_uint32_t_type;

   future_value_set_uint32_t (
      &return_value,
      mongoc_bulk_operation_execute (
         future_value_get_mongoc_bulk_operation_ptr (future_get_param (future, 0)),
         future_value_get_bson_ptr (future_get_param (future, 1)),
         future_value_get_bson_error_ptr (future_get_param (future, 2))
      ));

   future_resolve (future, return_value);

   return NULL;
}

static void *
background_mongoc_client_command_simple (void *data)
{
   future_t *future = (future_t *) data;
   future_value_t return_value;

   return_value.type = future_value_bool_type;

   future_value_set_bool (
      &return_value,
      mongoc_client_command_simple (
         future_value_get_mongoc_client_ptr (future_get_param (future, 0)),
         future_value_get_const_char_ptr (future_get_param (future, 1)),
         future_value_get_const_bson_ptr (future_get_param (future, 2)),
         future_value_get_const_mongoc_read_prefs_ptr (future_get_param (future, 3)),
         future_value_get_bson_ptr (future_get_param (future, 4)),
         future_value_get_bson_error_ptr (future_get_param (future, 5))
      ));

   future_resolve (future, return_value);

   return NULL;
}

static void *
background_mongoc_client_kill_cursor (void *data)
{
   future_t *future = (future_t *) data;
   future_value_t return_value;

   return_value.type = future_value_void_type;

   mongoc_client_kill_cursor (
      future_value_get_mongoc_client_ptr (future_get_param (future, 0)),
      future_value_get_int64_t (future_get_param (future, 1)));

   future_resolve (future, return_value);

   return NULL;
}

static void *
background_mongoc_collection_aggregate (void *data)
{
   future_t *future = (future_t *) data;
   future_value_t return_value;

   return_value.type = future_value_mongoc_cursor_ptr_type;

   future_value_set_mongoc_cursor_ptr (
      &return_value,
      mongoc_collection_aggregate (
         future_value_get_mongoc_collection_ptr (future_get_param (future, 0)),
         future_value_get_mongoc_query_flags_t (future_get_param (future, 1)),
         future_value_get_const_bson_ptr (future_get_param (future, 2)),
         future_value_get_const_bson_ptr (future_get_param (future, 3)),
         future_value_get_const_mongoc_read_prefs_ptr (future_get_param (future, 4))
      ));

   future_resolve (future, return_value);

   return NULL;
}

static void *
background_mongoc_collection_count (void *data)
{
   future_t *future = (future_t *) data;
   future_value_t return_value;

   return_value.type = future_value_int64_t_type;

   future_value_set_int64_t (
      &return_value,
      mongoc_collection_count (
         future_value_get_mongoc_collection_ptr (future_get_param (future, 0)),
         future_value_get_mongoc_query_flags_t (future_get_param (future, 1)),
         future_value_get_const_bson_ptr (future_get_param (future, 2)),
         future_value_get_int64_t (future_get_param (future, 3)),
         future_value_get_int64_t (future_get_param (future, 4)),
         future_value_get_const_mongoc_read_prefs_ptr (future_get_param (future, 5)),
         future_value_get_bson_error_ptr (future_get_param (future, 6))
      ));

   future_resolve (future, return_value);

   return NULL;
}

static void *
background_mongoc_collection_find_and_modify_with_opts (void *data)
{
   future_t *future = (future_t *) data;
   future_value_t return_value;

   return_value.type = future_value_bool_type;

   future_value_set_bool (
      &return_value,
      mongoc_collection_find_and_modify_with_opts (
         future_value_get_mongoc_collection_ptr (future_get_param (future, 0)),
         future_value_get_const_bson_ptr (future_get_param (future, 1)),
         future_value_get_const_mongoc_find_and_modify_opts_ptr (future_get_param (future, 2)),
         future_value_get_bson_ptr (future_get_param (future, 3)),
         future_value_get_bson_error_ptr (future_get_param (future, 4))
      ));

   future_resolve (future, return_value);

   return NULL;
}

static void *
background_mongoc_collection_find_and_modify (void *data)
{
   future_t *future = (future_t *) data;
   future_value_t return_value;

   return_value.type = future_value_bool_type;

   future_value_set_bool (
      &return_value,
      mongoc_collection_find_and_modify (
         future_value_get_mongoc_collection_ptr (future_get_param (future, 0)),
         future_value_get_const_bson_ptr (future_get_param (future, 1)),
         future_value_get_const_bson_ptr (future_get_param (future, 2)),
         future_value_get_const_bson_ptr (future_get_param (future, 3)),
         future_value_get_const_bson_ptr (future_get_param (future, 4)),
         future_value_get_bool (future_get_param (future, 5)),
         future_value_get_bool (future_get_param (future, 6)),
         future_value_get_bool (future_get_param (future, 7)),
         future_value_get_bson_ptr (future_get_param (future, 8)),
         future_value_get_bson_error_ptr (future_get_param (future, 9))
      ));

   future_resolve (future, return_value);

   return NULL;
}

static void *
background_mongoc_collection_insert_bulk (void *data)
{
   future_t *future = (future_t *) data;
   future_value_t return_value;

   return_value.type = future_value_bool_type;

   future_value_set_bool (
      &return_value,
      mongoc_collection_insert_bulk (
         future_value_get_mongoc_collection_ptr (future_get_param (future, 0)),
         future_value_get_mongoc_insert_flags_t (future_get_param (future, 1)),
         future_value_get_const_bson_ptr_ptr (future_get_param (future, 2)),
         future_value_get_uint32_t (future_get_param (future, 3)),
         future_value_get_const_mongoc_write_concern_ptr (future_get_param (future, 4)),
         future_value_get_bson_error_ptr (future_get_param (future, 5))
      ));

   future_resolve (future, return_value);

   return NULL;
}

static void *
background_mongoc_cursor_destroy (void *data)
{
   future_t *future = (future_t *) data;
   future_value_t return_value;

   return_value.type = future_value_void_type;

   mongoc_cursor_destroy (
      future_value_get_mongoc_cursor_ptr (future_get_param (future, 0)));

   future_resolve (future, return_value);

   return NULL;
}

static void *
background_mongoc_cursor_next (void *data)
{
   future_t *future = (future_t *) data;
   future_value_t return_value;

   return_value.type = future_value_bool_type;

   future_value_set_bool (
      &return_value,
      mongoc_cursor_next (
         future_value_get_mongoc_cursor_ptr (future_get_param (future, 0)),
         future_value_get_const_bson_ptr_ptr (future_get_param (future, 1))
      ));

   future_resolve (future, return_value);

   return NULL;
}

static void *
background_mongoc_client_get_database_names (void *data)
{
   future_t *future = (future_t *) data;
   future_value_t return_value;

   return_value.type = future_value_char_ptr_ptr_type;

   future_value_set_char_ptr_ptr (
      &return_value,
      mongoc_client_get_database_names (
         future_value_get_mongoc_client_ptr (future_get_param (future, 0)),
         future_value_get_bson_error_ptr (future_get_param (future, 1))
      ));

   future_resolve (future, return_value);

   return NULL;
}

static void *
background_mongoc_database_get_collection_names (void *data)
{
   future_t *future = (future_t *) data;
   future_value_t return_value;

   return_value.type = future_value_char_ptr_ptr_type;

   future_value_set_char_ptr_ptr (
      &return_value,
      mongoc_database_get_collection_names (
         future_value_get_mongoc_database_ptr (future_get_param (future, 0)),
         future_value_get_bson_error_ptr (future_get_param (future, 1))
      ));

   future_resolve (future, return_value);

   return NULL;
}

static void *
background_mongoc_gridfs_file_readv (void *data)
{
   future_t *future = (future_t *) data;
   future_value_t return_value;

   return_value.type = future_value_ssize_t_type;

   future_value_set_ssize_t (
      &return_value,
      mongoc_gridfs_file_readv (
         future_value_get_mongoc_gridfs_file_ptr (future_get_param (future, 0)),
         future_value_get_mongoc_iovec_ptr (future_get_param (future, 1)),
         future_value_get_size_t (future_get_param (future, 2)),
         future_value_get_size_t (future_get_param (future, 3)),
         future_value_get_uint32_t (future_get_param (future, 4))
      ));

   future_resolve (future, return_value);

   return NULL;
}

static void *
background_mongoc_gridfs_file_seek (void *data)
{
   future_t *future = (future_t *) data;
   future_value_t return_value;

   return_value.type = future_value_int_type;

   future_value_set_int (
      &return_value,
      mongoc_gridfs_file_seek (
         future_value_get_mongoc_gridfs_file_ptr (future_get_param (future, 0)),
         future_value_get_int64_t (future_get_param (future, 1)),
         future_value_get_int (future_get_param (future, 2))
      ));

   future_resolve (future, return_value);

   return NULL;
}

static void *
background_mongoc_gridfs_file_writev (void *data)
{
   future_t *future = (future_t *) data;
   future_value_t return_value;

   return_value.type = future_value_ssize_t_type;

   future_value_set_ssize_t (
      &return_value,
      mongoc_gridfs_file_writev (
         future_value_get_mongoc_gridfs_file_ptr (future_get_param (future, 0)),
         future_value_get_mongoc_iovec_ptr (future_get_param (future, 1)),
         future_value_get_size_t (future_get_param (future, 2)),
         future_value_get_uint32_t (future_get_param (future, 3))
      ));

   future_resolve (future, return_value);

   return NULL;
}

static void *
background_mongoc_topology_select (void *data)
{
   future_t *future = (future_t *) data;
   future_value_t return_value;

   return_value.type = future_value_mongoc_server_description_ptr_type;

   future_value_set_mongoc_server_description_ptr (
      &return_value,
      mongoc_topology_select (
         future_value_get_mongoc_topology_ptr (future_get_param (future, 0)),
         future_value_get_mongoc_ss_optype_t (future_get_param (future, 1)),
         future_value_get_const_mongoc_read_prefs_ptr (future_get_param (future, 2)),
         future_value_get_int64_t (future_get_param (future, 3)),
         future_value_get_bson_error_ptr (future_get_param (future, 4))
      ));

   future_resolve (future, return_value);

   return NULL;
}

static void *
background_mongoc_client_get_gridfs (void *data)
{
   future_t *future = (future_t *) data;
   future_value_t return_value;

   return_value.type = future_value_mongoc_gridfs_ptr_type;

   future_value_set_mongoc_gridfs_ptr (
      &return_value,
      mongoc_client_get_gridfs (
         future_value_get_mongoc_client_ptr (future_get_param (future, 0)),
         future_value_get_const_char_ptr (future_get_param (future, 1)),
         future_value_get_const_char_ptr (future_get_param (future, 2)),
         future_value_get_bson_error_ptr (future_get_param (future, 3))
      ));

   future_resolve (future, return_value);

   return NULL;
}



future_t *
future_bulk_operation_execute (
   mongoc_bulk_operation_ptr bulk,
   bson_ptr reply,
   bson_error_ptr error)
{
   future_t *future = future_new (future_value_uint32_t_type,
                                  3);
   
   future_value_set_mongoc_bulk_operation_ptr (
      future_get_param (future, 0), bulk);
   
   future_value_set_bson_ptr (
      future_get_param (future, 1), reply);
   
   future_value_set_bson_error_ptr (
      future_get_param (future, 2), error);
   
   future_start (future, background_mongoc_bulk_operation_execute);
   return future;
}

future_t *
future_client_command_simple (
   mongoc_client_ptr client,
   const_char_ptr db_name,
   const_bson_ptr command,
   const_mongoc_read_prefs_ptr read_prefs,
   bson_ptr reply,
   bson_error_ptr error)
{
   future_t *future = future_new (future_value_bool_type,
                                  6);
   
   future_value_set_mongoc_client_ptr (
      future_get_param (future, 0), client);
   
   future_value_set_const_char_ptr (
      future_get_param (future, 1), db_name);
   
   future_value_set_const_bson_ptr (
      future_get_param (future, 2), command);
   
   future_value_set_const_mongoc_read_prefs_ptr (
      future_get_param (future, 3), read_prefs);
   
   future_value_set_bson_ptr (
      future_get_param (future, 4), reply);
   
   future_value_set_bson_error_ptr (
      future_get_param (future, 5), error);
   
   future_start (future, background_mongoc_client_command_simple);
   return future;
}

future_t *
future_client_kill_cursor (
   mongoc_client_ptr client,
   int64_t cursor_id)
{
   future_t *future = future_new (future_value_void_type,
                                  2);
   
   future_value_set_mongoc_client_ptr (
      future_get_param (future, 0), client);
   
   future_value_set_int64_t (
      future_get_param (future, 1), cursor_id);
   
   future_start (future, background_mongoc_client_kill_cursor);
   return future;
}

future_t *
future_collection_aggregate (
   mongoc_collection_ptr collection,
   mongoc_query_flags_t flags,
   const_bson_ptr pipeline,
   const_bson_ptr options,
   const_mongoc_read_prefs_ptr read_prefs)
{
   future_t *future = future_new (future_value_mongoc_cursor_ptr_type,
                                  5);
   
   future_value_set_mongoc_collection_ptr (
      future_get_param (future, 0), collection);
   
   future_value_set_mongoc_query_flags_t (
      future_get_param (future, 1), flags);
   
   future_value_set_const_bson_ptr (
      future_get_param (future, 2), pipeline);
   
   future_value_set_const_bson_ptr (
      future_get_param (future, 3), options);
   
   future_value_set_const_mongoc_read_prefs_ptr (
      future_get_param (future, 4), read_prefs);
   
   future_start (future, background_mongoc_collection_aggregate);
   return future;
}

future_t *
future_collection_count (
   mongoc_collection_ptr collection,
   mongoc_query_flags_t flags,
   const_bson_ptr query,
   int64_t skip,
   int64_t limit,
   const_mongoc_read_prefs_ptr read_prefs,
   bson_error_ptr error)
{
   future_t *future = future_new (future_value_int64_t_type,
                                  7);
   
   future_value_set_mongoc_collection_ptr (
      future_get_param (future, 0), collection);
   
   future_value_set_mongoc_query_flags_t (
      future_get_param (future, 1), flags);
   
   future_value_set_const_bson_ptr (
      future_get_param (future, 2), query);
   
   future_value_set_int64_t (
      future_get_param (future, 3), skip);
   
   future_value_set_int64_t (
      future_get_param (future, 4), limit);
   
   future_value_set_const_mongoc_read_prefs_ptr (
      future_get_param (future, 5), read_prefs);
   
   future_value_set_bson_error_ptr (
      future_get_param (future, 6), error);
   
   future_start (future, background_mongoc_collection_count);
   return future;
}

future_t *
future_collection_find_and_modify_with_opts (
   mongoc_collection_ptr collection,
   const_bson_ptr query,
   const_mongoc_find_and_modify_opts_ptr opts,
   bson_ptr reply,
   bson_error_ptr error)
{
   future_t *future = future_new (future_value_bool_type,
                                  5);
   
   future_value_set_mongoc_collection_ptr (
      future_get_param (future, 0), collection);
   
   future_value_set_const_bson_ptr (
      future_get_param (future, 1), query);
   
   future_value_set_const_mongoc_find_and_modify_opts_ptr (
      future_get_param (future, 2), opts);
   
   future_value_set_bson_ptr (
      future_get_param (future, 3), reply);
   
   future_value_set_bson_error_ptr (
      future_get_param (future, 4), error);
   
   future_start (future, background_mongoc_collection_find_and_modify_with_opts);
   return future;
}

future_t *
future_collection_find_and_modify (
   mongoc_collection_ptr collection,
   const_bson_ptr query,
   const_bson_ptr sort,
   const_bson_ptr update,
   const_bson_ptr fields,
   bool _remove,
   bool upsert,
   bool _new,
   bson_ptr reply,
   bson_error_ptr error)
{
   future_t *future = future_new (future_value_bool_type,
                                  10);
   
   future_value_set_mongoc_collection_ptr (
      future_get_param (future, 0), collection);
   
   future_value_set_const_bson_ptr (
      future_get_param (future, 1), query);
   
   future_value_set_const_bson_ptr (
      future_get_param (future, 2), sort);
   
   future_value_set_const_bson_ptr (
      future_get_param (future, 3), update);
   
   future_value_set_const_bson_ptr (
      future_get_param (future, 4), fields);
   
   future_value_set_bool (
      future_get_param (future, 5), _remove);
   
   future_value_set_bool (
      future_get_param (future, 6), upsert);
   
   future_value_set_bool (
      future_get_param (future, 7), _new);
   
   future_value_set_bson_ptr (
      future_get_param (future, 8), reply);
   
   future_value_set_bson_error_ptr (
      future_get_param (future, 9), error);
   
   future_start (future, background_mongoc_collection_find_and_modify);
   return future;
}

future_t *
future_collection_insert_bulk (
   mongoc_collection_ptr collection,
   mongoc_insert_flags_t flags,
   const_bson_ptr_ptr documents,
   uint32_t n_documents,
   const_mongoc_write_concern_ptr write_concern,
   bson_error_ptr error)
{
   future_t *future = future_new (future_value_bool_type,
                                  6);
   
   future_value_set_mongoc_collection_ptr (
      future_get_param (future, 0), collection);
   
   future_value_set_mongoc_insert_flags_t (
      future_get_param (future, 1), flags);
   
   future_value_set_const_bson_ptr_ptr (
      future_get_param (future, 2), documents);
   
   future_value_set_uint32_t (
      future_get_param (future, 3), n_documents);
   
   future_value_set_const_mongoc_write_concern_ptr (
      future_get_param (future, 4), write_concern);
   
   future_value_set_bson_error_ptr (
      future_get_param (future, 5), error);
   
   future_start (future, background_mongoc_collection_insert_bulk);
   return future;
}

future_t *
future_cursor_destroy (
   mongoc_cursor_ptr cursor)
{
   future_t *future = future_new (future_value_void_type,
                                  1);
   
   future_value_set_mongoc_cursor_ptr (
      future_get_param (future, 0), cursor);
   
   future_start (future, background_mongoc_cursor_destroy);
   return future;
}

future_t *
future_cursor_next (
   mongoc_cursor_ptr cursor,
   const_bson_ptr_ptr doc)
{
   future_t *future = future_new (future_value_bool_type,
                                  2);
   
   future_value_set_mongoc_cursor_ptr (
      future_get_param (future, 0), cursor);
   
   future_value_set_const_bson_ptr_ptr (
      future_get_param (future, 1), doc);
   
   future_start (future, background_mongoc_cursor_next);
   return future;
}

future_t *
future_client_get_database_names (
   mongoc_client_ptr client,
   bson_error_ptr error)
{
   future_t *future = future_new (future_value_char_ptr_ptr_type,
                                  2);
   
   future_value_set_mongoc_client_ptr (
      future_get_param (future, 0), client);
   
   future_value_set_bson_error_ptr (
      future_get_param (future, 1), error);
   
   future_start (future, background_mongoc_client_get_database_names);
   return future;
}

future_t *
future_database_get_collection_names (
   mongoc_database_ptr database,
   bson_error_ptr error)
{
   future_t *future = future_new (future_value_char_ptr_ptr_type,
                                  2);
   
   future_value_set_mongoc_database_ptr (
      future_get_param (future, 0), database);
   
   future_value_set_bson_error_ptr (
      future_get_param (future, 1), error);
   
   future_start (future, background_mongoc_database_get_collection_names);
   return future;
}

future_t *
future_gridfs_file_readv (
   mongoc_gridfs_file_ptr file,
   mongoc_iovec_ptr iov,
   size_t iovcnt,
   size_t min_bytes,
   uint32_t timeout_msec)
{
   future_t *future = future_new (future_value_ssize_t_type,
                                  5);
   
   future_value_set_mongoc_gridfs_file_ptr (
      future_get_param (future, 0), file);
   
   future_value_set_mongoc_iovec_ptr (
      future_get_param (future, 1), iov);
   
   future_value_set_size_t (
      future_get_param (future, 2), iovcnt);
   
   future_value_set_size_t (
      future_get_param (future, 3), min_bytes);
   
   future_value_set_uint32_t (
      future_get_param (future, 4), timeout_msec);
   
   future_start (future, background_mongoc_gridfs_file_readv);
   return future;
}

future_t *
future_gridfs_file_seek (
   mongoc_gridfs_file_ptr file,
   int64_t delta,
   int whence)
{
   future_t *future = future_new (future_value_int_type,
                                  3);
   
   future_value_set_mongoc_gridfs_file_ptr (
      future_get_param (future, 0), file);
   
   future_value_set_int64_t (
      future_get_param (future, 1), delta);
   
   future_value_set_int (
      future_get_param (future, 2), whence);
   
   future_start (future, background_mongoc_gridfs_file_seek);
   return future;
}

future_t *
future_gridfs_file_writev (
   mongoc_gridfs_file_ptr file,
   mongoc_iovec_ptr iov,
   size_t iovcnt,
   uint32_t timeout_msec)
{
   future_t *future = future_new (future_value_ssize_t_type,
                                  4);
   
   future_value_set_mongoc_gridfs_file_ptr (
      future_get_param (future, 0), file);
   
   future_value_set_mongoc_iovec_ptr (
      future_get_param (future, 1), iov);
   
   future_value_set_size_t (
      future_get_param (future, 2), iovcnt);
   
   future_value_set_uint32_t (
      future_get_param (future, 3), timeout_msec);
   
   future_start (future, background_mongoc_gridfs_file_writev);
   return future;
}

future_t *
future_topology_select (
   mongoc_topology_ptr topology,
   mongoc_ss_optype_t optype,
   const_mongoc_read_prefs_ptr read_prefs,
   int64_t local_threshold_ms,
   bson_error_ptr error)
{
   future_t *future = future_new (future_value_mongoc_server_description_ptr_type,
                                  5);
   
   future_value_set_mongoc_topology_ptr (
      future_get_param (future, 0), topology);
   
   future_value_set_mongoc_ss_optype_t (
      future_get_param (future, 1), optype);
   
   future_value_set_const_mongoc_read_prefs_ptr (
      future_get_param (future, 2), read_prefs);
   
   future_value_set_int64_t (
      future_get_param (future, 3), local_threshold_ms);
   
   future_value_set_bson_error_ptr (
      future_get_param (future, 4), error);
   
   future_start (future, background_mongoc_topology_select);
   return future;
}

future_t *
future_client_get_gridfs (
   mongoc_client_ptr client,
   const_char_ptr db,
   const_char_ptr prefix,
   bson_error_ptr error)
{
   future_t *future = future_new (future_value_mongoc_gridfs_ptr_type,
                                  4);
   
   future_value_set_mongoc_client_ptr (
      future_get_param (future, 0), client);
   
   future_value_set_const_char_ptr (
      future_get_param (future, 1), db);
   
   future_value_set_const_char_ptr (
      future_get_param (future, 2), prefix);
   
   future_value_set_bson_error_ptr (
      future_get_param (future, 3), error);
   
   future_start (future, background_mongoc_client_get_gridfs);
   return future;
}
