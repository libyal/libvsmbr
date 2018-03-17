/*
 * Python object wrapper of libvsmbr_partition_t
 *
 * Copyright (C) 2010-2018, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyvsmbr_error.h"
#include "pyvsmbr_integer.h"
#include "pyvsmbr_libcerror.h"
#include "pyvsmbr_libvsmbr.h"
#include "pyvsmbr_partition.h"
#include "pyvsmbr_python.h"
#include "pyvsmbr_unused.h"

PyMethodDef pyvsmbr_partition_object_methods[] = {

	{ "get_type",
	  (PyCFunction) pyvsmbr_partition_get_type,
	  METH_NOARGS,
	  "get_type() -> Integer or None\n"
	  "\n"
	  "Retrieves the type." },

	{ "read_buffer",
	  (PyCFunction) pyvsmbr_partition_read_buffer,
	  METH_VARARGS | METH_KEYWORDS,
	  "read_buffer(size) -> Binary string or None\n"
	  "\n"
	  "Reads a buffer of data." },

	{ "read_buffer_at_offset",
	  (PyCFunction) pyvsmbr_partition_read_buffer_at_offset,
	  METH_VARARGS | METH_KEYWORDS,
	  "read_buffer_at_offset(size, offset) -> Binary string or None\n"
	  "\n"
	  "Reads a buffer of data at a specific offset." },

	{ "seek_offset",
	  (PyCFunction) pyvsmbr_partition_seek_offset,
	  METH_VARARGS | METH_KEYWORDS,
	  "seek_offset(offset, whence) -> None\n"
	  "\n"
	  "Seeks an offset within the data." },

	{ "get_offset",
	  (PyCFunction) pyvsmbr_partition_get_offset,
	  METH_NOARGS,
	  "get_offset() -> Integer or None\n"
	  "\n"
	  "Retrieves the current offset within the data." },

	{ "read",
	  (PyCFunction) pyvsmbr_partition_read_buffer,
	  METH_VARARGS | METH_KEYWORDS,
	  "read(size) -> String\n"
	  "\n"
	  "Reads a buffer of data." },

	{ "seek",
	  (PyCFunction) pyvsmbr_partition_seek_offset,
	  METH_VARARGS | METH_KEYWORDS,
	  "seek(offset, whence) -> None\n"
	  "\n"
	  "Seeks an offset within the data." },

	{ "tell",
	  (PyCFunction) pyvsmbr_partition_get_offset,
	  METH_NOARGS,
	  "tell() -> Integer\n"
	  "\n"
	  "Retrieves the current offset within the data." },

	{ "get_size",
	  (PyCFunction) pyvsmbr_partition_get_size,
	  METH_NOARGS,
	  "get_size() -> Integer or None\n"
	  "\n"
	  "Retrieves the size." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyvsmbr_partition_object_get_set_definitions[] = {

	{ "type",
	  (getter) pyvsmbr_partition_get_type,
	  (setter) 0,
	  "The type.",
	  NULL },

	{ "size",
	  (getter) pyvsmbr_partition_get_size,
	  (setter) 0,
	  "The size.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyvsmbr_partition_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyvsmbr.partition",
	/* tp_basicsize */
	sizeof( pyvsmbr_partition_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyvsmbr_partition_free,
	/* tp_print */
	0,
	/* tp_getattr */
	0,
	/* tp_setattr */
	0,
	/* tp_compare */
	0,
	/* tp_repr */
	0,
	/* tp_as_number */
	0,
	/* tp_as_sequence */
	0,
	/* tp_as_mapping */
	0,
	/* tp_hash */
	0,
	/* tp_call */
	0,
	/* tp_str */
	0,
	/* tp_getattro */
	0,
	/* tp_setattro */
	0,
	/* tp_as_buffer */
	0,
	/* tp_flags */
	Py_TPFLAGS_DEFAULT,
	/* tp_doc */
	"pyvsmbr partition object (wraps libvsmbr_partition_t)",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	0,
	/* tp_iternext */
	0,
	/* tp_methods */
	pyvsmbr_partition_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyvsmbr_partition_object_get_set_definitions,
	/* tp_base */
	0,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	(initproc) pyvsmbr_partition_init,
	/* tp_alloc */
	0,
	/* tp_new */
	0,
	/* tp_free */
	0,
	/* tp_is_gc */
	0,
	/* tp_bases */
	NULL,
	/* tp_mro */
	NULL,
	/* tp_cache */
	NULL,
	/* tp_subclasses */
	NULL,
	/* tp_weaklist */
	NULL,
	/* tp_del */
	0
};

/* Creates a new partition object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsmbr_partition_new(
           libvsmbr_partition_t *partition,
           PyObject *parent_object )
{
	pyvsmbr_partition_t *pyvsmbr_partition = NULL;
	static char *function                  = "pyvsmbr_partition_new";

	if( partition == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid partition.",
		 function );

		return( NULL );
	}
	/* PyObject_New does not invoke tp_init
	 */
	pyvsmbr_partition = PyObject_New(
	                     struct pyvsmbr_partition,
	                     &pyvsmbr_partition_type_object );

	if( pyvsmbr_partition == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize partition.",
		 function );

		goto on_error;
	}
	pyvsmbr_partition->partition     = partition;
	pyvsmbr_partition->parent_object = parent_object;

	Py_IncRef(
	 (PyObject *) pyvsmbr_partition->parent_object );

	return( (PyObject *) pyvsmbr_partition );

on_error:
	if( pyvsmbr_partition != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvsmbr_partition );
	}
	return( NULL );
}

/* Intializes a partition object
 * Returns 0 if successful or -1 on error
 */
int pyvsmbr_partition_init(
     pyvsmbr_partition_t *pyvsmbr_partition )
{
	static char *function = "pyvsmbr_partition_init";

	if( pyvsmbr_partition == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid partition.",
		 function );

		return( -1 );
	}
	/* Make sure libvsmbr partition is set to NULL
	 */
	pyvsmbr_partition->partition = NULL;

	PyErr_Format(
	 PyExc_NotImplementedError,
	 "%s: initialize of partition not supported.",
	 function );

	return( -1 );
}

/* Frees a partition object
 */
void pyvsmbr_partition_free(
      pyvsmbr_partition_t *pyvsmbr_partition )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pyvsmbr_partition_free";
	int result                  = 0;

	if( pyvsmbr_partition == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid partition.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyvsmbr_partition );

	if( ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: missing ob_type.",
		 function );

		return;
	}
	if( ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( pyvsmbr_partition->partition != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libvsmbr_partition_free(
		          &( pyvsmbr_partition->partition ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyvsmbr_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to free libvsmbr partition.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	if( pyvsmbr_partition->parent_object != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyvsmbr_partition->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyvsmbr_partition );
}

/* Retrieves the type
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsmbr_partition_get_type(
           pyvsmbr_partition_t *pyvsmbr_partition,
           PyObject *arguments PYVSMBR_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyvsmbr_partition_get_type";
	uint8_t type             = 0;
	int result               = 0;

	PYVSMBR_UNREFERENCED_PARAMETER( arguments )

	if( pyvsmbr_partition == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid partition.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvsmbr_partition_get_type(
	          pyvsmbr_partition->partition,
	          &type,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyvsmbr_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve type.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
#if PY_MAJOR_VERSION >= 3
	integer_object = PyLong_FromLong(
	                  (long) type );
#else
	integer_object = PyInt_FromLong(
	                  (long) type );
#endif
	return( integer_object );
}

/* Reads data at the current offset into a buffer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsmbr_partition_read_buffer(
           pyvsmbr_partition_t *pyvsmbr_partition,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *integer_object    = NULL;
	PyObject *string_object     = NULL;
	libcerror_error_t *error    = NULL;
	char *buffer                = NULL;
	static char *function       = "pyvsmbr_partition_read_buffer";
	static char *keyword_list[] = { "size", NULL };
	ssize_t read_count          = 0;
	int64_t read_size           = 0;
	int result                  = 0;

	if( pyvsmbr_partition == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid partition.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "|O",
	     keyword_list,
	     &integer_object ) == 0 )
	{
		return( NULL );
	}
	if( integer_object == NULL )
	{
		result = 0;
	}
	else
	{
		result = PyObject_IsInstance(
		          integer_object,
		          (PyObject *) &PyLong_Type );

		if( result == -1 )
		{
			pyvsmbr_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to determine if integer object is of type long.",
			 function );

			return( NULL );
		}
#if PY_MAJOR_VERSION < 3
		else if( result == 0 )
		{
			PyErr_Clear();

			result = PyObject_IsInstance(
			          integer_object,
			          (PyObject *) &PyInt_Type );

			if( result == -1 )
			{
				pyvsmbr_error_fetch_and_raise(
				 PyExc_RuntimeError,
				 "%s: unable to determine if integer object is of type int.",
				 function );

				return( NULL );
			}
		}
#endif
	}
	if( result != 0 )
	{
		if( pyvsmbr_integer_signed_copy_to_64bit(
		     integer_object,
		     &read_size,
		     &error ) != 1 )
		{
			pyvsmbr_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to convert integer object into read size.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
	}
	else if( ( integer_object == NULL )
	      || ( integer_object == Py_None ) )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libvsmbr_partition_get_size(
		          pyvsmbr_partition->partition,
		          (size64_t *) &read_size,
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pyvsmbr_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to retrieve size.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
	}
	else
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported integer object type.",
		 function );

		return( NULL );
	}
	if( read_size == 0 )
	{
#if PY_MAJOR_VERSION >= 3
		string_object = PyBytes_FromString(
		                 "" );
#else
		string_object = PyString_FromString(
		                 "" );
#endif
		return( string_object );
	}
	if( read_size < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid read size value less than zero.",
		 function );

		return( NULL );
	}
	/* Make sure the data fits into a memory buffer
	 */
	if( ( read_size > (int64_t) INT_MAX )
	 || ( read_size > (int64_t) SSIZE_MAX ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid argument read size value exceeds maximum.",
		 function );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	string_object = PyBytes_FromStringAndSize(
	                 NULL,
	                 (Py_ssize_t) read_size );

	buffer = PyBytes_AsString(
	          string_object );
#else
	/* Note that a size of 0 is not supported
	 */
	string_object = PyString_FromStringAndSize(
	                 NULL,
	                 (Py_ssize_t) read_size );

	buffer = PyString_AsString(
	          string_object );
#endif
	Py_BEGIN_ALLOW_THREADS

	read_count = libvsmbr_partition_read_buffer(
	              pyvsmbr_partition->partition,
	              (uint8_t *) buffer,
	              (size_t) read_size,
	              &error );

	Py_END_ALLOW_THREADS

	if( read_count == -1 )
	{
		pyvsmbr_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to read data.",
		 function );

		libcerror_error_free(
		 &error );

		Py_DecRef(
		 (PyObject *) string_object );

		return( NULL );
	}
	/* Need to resize the string here in case read_size was not fully read.
	 */
#if PY_MAJOR_VERSION >= 3
	if( _PyBytes_Resize(
	     &string_object,
	     (Py_ssize_t) read_count ) != 0 )
#else
	if( _PyString_Resize(
	     &string_object,
	     (Py_ssize_t) read_count ) != 0 )
#endif
	{
		Py_DecRef(
		 (PyObject *) string_object );

		return( NULL );
	}
	return( string_object );
}

/* Reads data at a specific offset into a buffer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsmbr_partition_read_buffer_at_offset(
           pyvsmbr_partition_t *pyvsmbr_partition,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *integer_object    = NULL;
	PyObject *string_object     = NULL;
	libcerror_error_t *error    = NULL;
	char *buffer                = NULL;
	static char *function       = "pyvsmbr_partition_read_buffer_at_offset";
	static char *keyword_list[] = { "size", "offset", NULL };
	ssize_t read_count          = 0;
	off64_t read_offset         = 0;
	int64_t read_size           = 0;
	int result                  = 0;

	if( pyvsmbr_partition == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid partition.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "OL",
	     keyword_list,
	     &integer_object,
	     &read_offset ) == 0 )
	{
		return( NULL );
	}
	result = PyObject_IsInstance(
	          integer_object,
	          (PyObject *) &PyLong_Type );

	if( result == -1 )
	{
		pyvsmbr_error_fetch_and_raise(
		 PyExc_RuntimeError,
		 "%s: unable to determine if integer object is of type long.",
		 function );

		return( NULL );
	}
#if PY_MAJOR_VERSION < 3
	else if( result == 0 )
	{
		PyErr_Clear();

		result = PyObject_IsInstance(
		          integer_object,
		          (PyObject *) &PyInt_Type );

		if( result == -1 )
		{
			pyvsmbr_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to determine if integer object is of type int.",
			 function );

			return( NULL );
		}
	}
#endif
	if( result != 0 )
	{
		if( pyvsmbr_integer_signed_copy_to_64bit(
		     integer_object,
		     &read_size,
		     &error ) != 1 )
		{
			pyvsmbr_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to convert integer object into read size.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
	}
	else
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: unsupported integer object type.",
		 function );

		return( NULL );
	}
	if( read_size == 0 )
	{
#if PY_MAJOR_VERSION >= 3
		string_object = PyBytes_FromString(
		                 "" );
#else
		string_object = PyString_FromString(
		                 "" );
#endif
		return( string_object );
	}
	if( read_size < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid read size value less than zero.",
		 function );

		return( NULL );
	}
	/* Make sure the data fits into a memory buffer
	 */
	if( ( read_size > (int64_t) INT_MAX )
	 || ( read_size > (int64_t) SSIZE_MAX ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid argument read size value exceeds maximum.",
		 function );

		return( NULL );
	}
	if( read_offset < 0 )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid read offset value less than zero.",
		 function );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	string_object = PyBytes_FromStringAndSize(
	                 NULL,
	                 (Py_ssize_t) read_size );

	buffer = PyBytes_AsString(
	          string_object );
#else
	/* Note that a size of 0 is not supported
	 */
	string_object = PyString_FromStringAndSize(
	                 NULL,
	                 (Py_ssize_t) read_size );

	buffer = PyString_AsString(
	          string_object );
#endif
	Py_BEGIN_ALLOW_THREADS

	read_count = libvsmbr_partition_read_buffer_at_offset(
	              pyvsmbr_partition->partition,
	              (uint8_t *) buffer,
	              (size_t) read_size,
	              (off64_t) read_offset,
	              &error );

	Py_END_ALLOW_THREADS

	if( read_count == -1 )
	{
		pyvsmbr_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to read data.",
		 function );

		libcerror_error_free(
		 &error );

		Py_DecRef(
		 (PyObject *) string_object );

		return( NULL );
	}
	/* Need to resize the string here in case read_size was not fully read.
	 */
#if PY_MAJOR_VERSION >= 3
	if( _PyBytes_Resize(
	     &string_object,
	     (Py_ssize_t) read_count ) != 0 )
#else
	if( _PyString_Resize(
	     &string_object,
	     (Py_ssize_t) read_count ) != 0 )
#endif
	{
		Py_DecRef(
		 (PyObject *) string_object );

		return( NULL );
	}
	return( string_object );
}

/* Seeks a certain offset
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsmbr_partition_seek_offset(
           pyvsmbr_partition_t *pyvsmbr_partition,
           PyObject *arguments,
           PyObject *keywords )
{
	libcerror_error_t *error    = NULL;
	static char *function       = "pyvsmbr_partition_seek_offset";
	static char *keyword_list[] = { "offset", "whence", NULL };
	off64_t offset              = 0;
	int whence                  = 0;

	if( pyvsmbr_partition == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid partition.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "L|i",
	     keyword_list,
	     &offset,
	     &whence ) == 0 )
	{
		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	offset = libvsmbr_partition_seek_offset(
	          pyvsmbr_partition->partition,
	          offset,
	          whence,
	          &error );

	Py_END_ALLOW_THREADS

 	if( offset == -1 )
	{
		pyvsmbr_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to seek offset.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the offset
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsmbr_partition_get_offset(
           pyvsmbr_partition_t *pyvsmbr_partition,
           PyObject *arguments PYVSMBR_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyvsmbr_partition_get_offset";
	off64_t offset           = 0;
	int result               = 0;

	PYVSMBR_UNREFERENCED_PARAMETER( arguments )

	if( pyvsmbr_partition == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid partition.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvsmbr_partition_get_offset(
	          pyvsmbr_partition->partition,
	          &offset,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pyvsmbr_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve offset.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	integer_object = pyvsmbr_integer_signed_new_from_64bit(
	                  (int64_t) offset );

	return( integer_object );
}

/* Retrieves the size
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyvsmbr_partition_get_size(
           pyvsmbr_partition_t *pyvsmbr_partition,
           PyObject *arguments PYVSMBR_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pyvsmbr_partition_get_size";
	size64_t size            = 0;
	int result               = 0;

	PYVSMBR_UNREFERENCED_PARAMETER( arguments )

	if( pyvsmbr_partition == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid partition.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libvsmbr_partition_get_size(
	          pyvsmbr_partition->partition,
	          &size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyvsmbr_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: failed to retrieve size.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pyvsmbr_integer_unsigned_new_from_64bit(
	                  (uint64_t) size );

	return( integer_object );
}

