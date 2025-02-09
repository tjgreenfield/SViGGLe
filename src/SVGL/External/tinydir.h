/*
Copyright (c) 2013-2014, Cong Xu, Baudouin Feildel
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* Sourced from https://github.com/cxong/tinydir/blob/master/tinydir.h */

/* Modifications to remove c++11 compiler warnings about NULL/nullptr- Timothy Greenfield 2015 */

#ifndef TINYDIR_H
#define TINYDIR_H

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# ifdef _MSC_VER
#  pragma warning (disable : 4996)
# endif
#else
# include <dirent.h>
# include <libgen.h>
# include <sys/stat.h>
#endif


/* types */

/* Redefine NULL as nullptr so as to remove compiler warnings about setting pointers to '0' */
#if __cplusplus >= 201103L
#define _TINYDIR_NULL nullptr
#else
#define _TINYDIR_NULL NULL
#endif

#define _TINYDIR_PATH_MAX 4096
#ifdef _WIN32
/* extra chars for the "\\*" mask */
# define _TINYDIR_PATH_EXTRA 2
#else
# define _TINYDIR_PATH_EXTRA 0
#endif
#define _TINYDIR_FILENAME_MAX 256

#ifdef _MSC_VER
# define _TINYDIR_FUNC static __inline
#else
# define _TINYDIR_FUNC static __inline__
#endif

/* Allow user to use a custom allocator by defining _TINYDIR_MALLOC and _TINYDIR_FREE. */
#if    defined(_TINYDIR_MALLOC) &&  defined(_TINYDIR_FREE)
#elif !defined(_TINYDIR_MALLOC) && !defined(_TINYDIR_FREE)
#else
#error "Either define both alloc and free or none of them!"
#endif

#if !defined(_TINYDIR_MALLOC)
	#define _TINYDIR_MALLOC(_size) malloc(_size)
	#define _TINYDIR_FREE(_ptr)    free(_ptr)
#endif //!defined(_TINYDIR_MALLOC)

typedef struct
{
	char path[_TINYDIR_PATH_MAX];
	char name[_TINYDIR_FILENAME_MAX];
	char *extension;
	int is_dir;
	int is_reg;

#ifndef _WIN32
	struct stat _s;
#endif
} tinydir_file;

typedef struct
{
	char path[_TINYDIR_PATH_MAX];
	int has_next;
	size_t n_files;

	tinydir_file *_files;
#ifdef _WIN32
	HANDLE _h;
	WIN32_FIND_DATAA _f;
#else
	DIR *_d;
	struct dirent *_e;
#endif
} tinydir_dir;


/* declarations */

_TINYDIR_FUNC
int tinydir_open(tinydir_dir *dir, const char *path);
_TINYDIR_FUNC
int tinydir_open_sorted(tinydir_dir *dir, const char *path);
_TINYDIR_FUNC
void tinydir_close(tinydir_dir *dir);

_TINYDIR_FUNC
int tinydir_next(tinydir_dir *dir);
_TINYDIR_FUNC
int tinydir_readfile(const tinydir_dir *dir, tinydir_file *file);
_TINYDIR_FUNC
int tinydir_readfile_n(const tinydir_dir *dir, tinydir_file *file, size_t i);
_TINYDIR_FUNC
int tinydir_open_subdir_n(tinydir_dir *dir, size_t i);

_TINYDIR_FUNC
void _tinydir_get_ext(tinydir_file *file);
_TINYDIR_FUNC
int _tinydir_file_cmp(const void *a, const void *b);


/* definitions*/

_TINYDIR_FUNC
int tinydir_open(tinydir_dir *dir, const char *path)
{
	if (dir == _TINYDIR_NULL  || path == _TINYDIR_NULL  || strlen(path) == 0)
	{
		errno = EINVAL;
		return -1;
	}
	if (strlen(path) + _TINYDIR_PATH_EXTRA >= _TINYDIR_PATH_MAX)
	{
		errno = ENAMETOOLONG;
		return -1;
	}

	/* initialise dir */
	dir->_files = _TINYDIR_NULL ;
#ifdef _WIN32
	dir->_h = INVALID_HANDLE_VALUE;
#else
	dir->_d = _TINYDIR_NULL ;
#endif
	tinydir_close(dir);

	strcpy(dir->path, path);
#ifdef _WIN32
	strcat(dir->path, "\\*");
	dir->_h = FindFirstFileA(dir->path, &dir->_f);
	dir->path[strlen(dir->path) - 2] = '\0';
	if (dir->_h == INVALID_HANDLE_VALUE)
#else
	dir->_d = opendir(path);
	if (dir->_d == _TINYDIR_NULL )
#endif
	{
		errno = ENOENT;
		goto bail;
	}

	/* read first file */
	dir->has_next = 1;
#ifndef _WIN32
	dir->_e = readdir(dir->_d);
	if (dir->_e == _TINYDIR_NULL )
	{
		dir->has_next = 0;
	}
#endif

	return 0;

bail:
	tinydir_close(dir);
	return -1;
}

_TINYDIR_FUNC
int tinydir_open_sorted(tinydir_dir *dir, const char *path)
{
	/* Count the number of files first, to pre-allocate the files array */
	size_t n_files = 0;
	if (tinydir_open(dir, path) == -1)
	{
		return -1;
	}
	while (dir->has_next)
	{
		n_files++;
		if (tinydir_next(dir) == -1)
		{
			goto bail;
		}
	}
	tinydir_close(dir);

	if (tinydir_open(dir, path) == -1)
	{
		return -1;
	}

	dir->n_files = 0;
	dir->_files = (tinydir_file *)_TINYDIR_MALLOC(sizeof *dir->_files * n_files);
	if (dir->_files == _TINYDIR_NULL )
	{
		errno = ENOMEM;
		goto bail;
	}
	while (dir->has_next)
	{
		tinydir_file *p_file;
		dir->n_files++;

		p_file = &dir->_files[dir->n_files - 1];
		if (tinydir_readfile(dir, p_file) == -1)
		{
			goto bail;
		}

		if (tinydir_next(dir) == -1)
		{
			goto bail;
		}

		/* Just in case the number of files has changed between the first and
		second reads, terminate without writing into unallocated memory */
		if (dir->n_files == n_files)
		{
			break;
		}
	}

	qsort(dir->_files, dir->n_files, sizeof(tinydir_file), _tinydir_file_cmp);

	return 0;

bail:
	tinydir_close(dir);
	return -1;
}

_TINYDIR_FUNC
void tinydir_close(tinydir_dir *dir)
{
	if (dir == _TINYDIR_NULL )
	{
		return;
	}

	memset(dir->path, 0, sizeof(dir->path));
	dir->has_next = 0;
	dir->n_files = 0;
	if (dir->_files != _TINYDIR_NULL )
	{
		_TINYDIR_FREE(dir->_files);
	}
	dir->_files = _TINYDIR_NULL ;
#ifdef _WIN32
	if (dir->_h != INVALID_HANDLE_VALUE)
	{
		FindClose(dir->_h);
	}
	dir->_h = INVALID_HANDLE_VALUE;
#else
	if (dir->_d)
	{
		closedir(dir->_d);
	}
	dir->_d = _TINYDIR_NULL ;
	dir->_e = _TINYDIR_NULL ;
#endif
}

_TINYDIR_FUNC
int tinydir_next(tinydir_dir *dir)
{
	if (dir == _TINYDIR_NULL )
	{
		errno = EINVAL;
		return -1;
	}
	if (!dir->has_next)
	{
		errno = ENOENT;
		return -1;
	}

#ifdef _WIN32
	if (FindNextFileA(dir->_h, &dir->_f) == 0)
#else
	dir->_e = readdir(dir->_d);
	if (dir->_e == _TINYDIR_NULL )
#endif
	{
		dir->has_next = 0;
#ifdef _WIN32
		if (GetLastError() != ERROR_SUCCESS &&
			GetLastError() != ERROR_NO_MORE_FILES)
		{
			tinydir_close(dir);
			errno = EIO;
			return -1;
		}
#endif
	}

	return 0;
}

_TINYDIR_FUNC
int tinydir_readfile(const tinydir_dir *dir, tinydir_file *file)
{
	if (dir == _TINYDIR_NULL  || file == _TINYDIR_NULL )
	{
		errno = EINVAL;
		return -1;
	}
#ifdef _WIN32
	if (dir->_h == INVALID_HANDLE_VALUE)
#else
	if (dir->_e == _TINYDIR_NULL )
#endif
	{
		errno = ENOENT;
		return -1;
	}
	if (strlen(dir->path) +
		strlen(
#ifdef _WIN32
			dir->_f.cFileName
#else
			dir->_e->d_name
#endif
		) + 1 + _TINYDIR_PATH_EXTRA >=
		_TINYDIR_PATH_MAX)
	{
		/* the path for the file will be too long */
		errno = ENAMETOOLONG;
		return -1;
	}
	if (strlen(
#ifdef _WIN32
			dir->_f.cFileName
#else
			dir->_e->d_name
#endif
		) >= _TINYDIR_FILENAME_MAX)
	{
		errno = ENAMETOOLONG;
		return -1;
	}

	strcpy(file->path, dir->path);
	strcat(file->path, "/");
	strcpy(file->name,
#ifdef _WIN32
		dir->_f.cFileName
#else
		dir->_e->d_name
#endif
	);
	strcat(file->path, file->name);
#ifndef _WIN32
	if (stat(file->path, &file->_s) == -1)
	{
		return -1;
	}
#endif
	_tinydir_get_ext(file);

	file->is_dir =
#ifdef _WIN32
		!!(dir->_f.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
#else
		S_ISDIR(file->_s.st_mode);
#endif
	file->is_reg =
#ifdef _WIN32
		!!(dir->_f.dwFileAttributes & FILE_ATTRIBUTE_NORMAL) ||
		(
			!(dir->_f.dwFileAttributes & FILE_ATTRIBUTE_DEVICE) &&
			!(dir->_f.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
			!(dir->_f.dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED) &&
#ifdef FILE_ATTRIBUTE_INTEGRITY_STREAM
			!(dir->_f.dwFileAttributes & FILE_ATTRIBUTE_INTEGRITY_STREAM) &&
#endif
#ifdef FILE_ATTRIBUTE_NO_SCRUB_DATA
			!(dir->_f.dwFileAttributes & FILE_ATTRIBUTE_NO_SCRUB_DATA) &&
#endif
			!(dir->_f.dwFileAttributes & FILE_ATTRIBUTE_OFFLINE) &&
			!(dir->_f.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY));
#else
		S_ISREG(file->_s.st_mode);
#endif

	return 0;
}

_TINYDIR_FUNC
int tinydir_readfile_n(const tinydir_dir *dir, tinydir_file *file, size_t i)
{
	if (dir == _TINYDIR_NULL  || file == _TINYDIR_NULL )
	{
		errno = EINVAL;
		return -1;
	}
	if (i >= dir->n_files)
	{
		errno = ENOENT;
		return -1;
	}

	memcpy(file, &dir->_files[i], sizeof(tinydir_file));
	_tinydir_get_ext(file);

	return 0;
}

_TINYDIR_FUNC
int tinydir_open_subdir_n(tinydir_dir *dir, size_t i)
{
	char path[_TINYDIR_PATH_MAX];
	if (dir == _TINYDIR_NULL )
	{
		errno = EINVAL;
		return -1;
	}
	if (i >= dir->n_files || !dir->_files[i].is_dir)
	{
		errno = ENOENT;
		return -1;
	}

	strcpy(path, dir->_files[i].path);
	tinydir_close(dir);
	if (tinydir_open_sorted(dir, path) == -1)
	{
		return -1;
	}

	return 0;
}

/* Open a single file given its path */
_TINYDIR_FUNC
int tinydir_file_open(tinydir_file *file, const char *path)
{
	tinydir_dir dir;
	int result = 0;
	int found = 0;
	char dir_name_buf[_TINYDIR_PATH_MAX];
	char file_name_buf[_TINYDIR_FILENAME_MAX];
	char *dir_name;
	char *base_name;
#ifdef _WIN32
	char drive_buf[_TINYDIR_PATH_MAX];
	char ext_buf[_TINYDIR_FILENAME_MAX];
#endif

	if (file == _TINYDIR_NULL  || path == _TINYDIR_NULL  || strlen(path) == 0)
	{
		errno = EINVAL;
		return -1;
	}
	if (strlen(path) + _TINYDIR_PATH_EXTRA >= _TINYDIR_PATH_MAX)
	{
		errno = ENAMETOOLONG;
		return -1;
	}

	/* Get the parent path */
#ifdef _WIN32
	if (_splitpath_s(
			path,
			drive_buf, sizeof drive_buf,
			dir_name_buf, sizeof dir_name_buf,
			file_name_buf, sizeof file_name_buf,
			ext_buf, sizeof ext_buf))
	{
		errno = EINVAL;
		return -1;
	}
	/* Concatenate the drive letter and dir name to form full dir name */
	strcat(drive_buf, dir_name_buf);
	dir_name = drive_buf;
	/* Concatenate the file name and extension to form base name */
	strcat(file_name_buf, ext_buf);
	base_name = file_name_buf;
#else
	strcpy(dir_name_buf, path);
	dir_name = dirname(dir_name_buf);
	strcpy(file_name_buf, path);
	base_name = basename(file_name_buf);
#endif

	/* Open the parent directory */
	if (tinydir_open(&dir, dir_name) == -1)
	{
		return -1;
	}

	/* Read through the parent directory and look for the file */
	while (dir.has_next)
	{
		if (tinydir_readfile(&dir, file) == -1)
		{
			result = -1;
			goto bail;
		}
		if (strcmp(file->name, base_name) == 0)
		{
			/* File found */
			found = 1;
			goto bail;
		}
		tinydir_next(&dir);
	}
	if (!found)
	{
		result = -1;
		errno = ENOENT;
	}

bail:
	tinydir_close(&dir);
	return result;
}

_TINYDIR_FUNC
void _tinydir_get_ext(tinydir_file *file)
{
	char *period = strrchr(file->name, '.');
	if (period == _TINYDIR_NULL )
	{
		file->extension = &(file->name[strlen(file->name)]);
	}
	else
	{
		file->extension = period + 1;
	}
}

_TINYDIR_FUNC
int _tinydir_file_cmp(const void *a, const void *b)
{
	const tinydir_file *fa = (const tinydir_file *)a;
	const tinydir_file *fb = (const tinydir_file *)b;
	if (fa->is_dir != fb->is_dir)
	{
		return -(fa->is_dir - fb->is_dir);
	}
	return strncmp(fa->name, fb->name, _TINYDIR_FILENAME_MAX);
}

#endif
