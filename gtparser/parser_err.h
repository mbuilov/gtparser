#ifndef PARSER_ERR_H_INCLUDED
#define PARSER_ERR_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2018 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* parser_err.h */

#include "gtparser/gtparser.h"

#ifdef __cplusplus
extern "C" {
#endif

/* if error buffer is big enough, then reserve some space at front of it for error prefix:
  "filename: parse error at (4294967295:4294967295):" */
/* err_buf_size - size of err_buf */
/* filename_reserve - how much space to reserve for printing file name passed to gt_parser_err_prepend_at() */
/* returns pointer to a space inside error buffer to print error message details to,
  or returns err_buf, if err_buf_size is too small */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_At(err_buf, A_Pre_writable_size(err_buf_size))
#endif
GTPARSER_EXPORTS char *gt_parser_err_reserve(char err_buf[/*err_buf_size*/], size_t err_buf_size, size_t filename_reserve/*0?*/)
#ifdef __GNUC__
__attribute__ ((const))
#endif
;

/* don't reserve space for file name (if parsing a buffer instead of a source file) */
#define gt_parser_err_reserve_(err_buf, err_buf_size) \
	gt_parser_err_reserve(err_buf, err_buf_size, /*filename_reserve:*/0)

/* if error buffer is big enough, then compose error message in form
  "filename: parse error at (0:0): error message" */
/* err_buf_size - size of err_buf */
/* filename_reserve - how much space to reserve for printing file name */
/* filename - if not NULL, then '\0'-terminated C-string */
/* err - '\0'-terminated error message,
  if error message was printed to err_buf (i.e. err is the value returned by gt_parser_err_reserve()),
  then err_buf, err_buf_size, filename_reserve - must be the same that were passed to gt_parser_err_reserve() */
/* line & column - position in source file where a parsing error occurred,
  if line is 0, then only column number is printed,
  if column is 0, then only line number is printed */
/* returns pointer to composed error message inside err_buf or err, if err_buf_size is too small */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Ret_z
A_Nonnull_arg(5)
A_At(err_buf, A_Pre_writable_size(err_buf_size))
A_At(filename, A_In_opt_z)
A_At(err, A_In_z)
#endif
GTPARSER_EXPORTS const char *gt_parser_err_prepend_at(
	char err_buf[/*err_buf_size*/], size_t err_buf_size,
	size_t filename_reserve/*0?*/, const char *filename/*NULL?,'\0'-terminated*/,
	const char *err/*!=NULL,'\0'-terminated*/, unsigned line/*0?*/, unsigned column/*0?*/);

/* same as gt_parser_err_prepend_at(), but don't print column number */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Ret_z
A_Nonnull_arg(5)
A_At(err_buf, A_Pre_writable_size(err_buf_size))
A_At(filename, A_In_opt_z)
A_At(err, A_In_z)
A_Pre_satisfies(line)
#endif
static inline const char *gt_parser_err_prepend_at_line(
	char err_buf[/*err_buf_size*/], size_t err_buf_size,
	size_t filename_reserve/*0?*/, const char *filename/*NULL?,'\0'-terminated*/,
	const char *err/*!=NULL,'\0'-terminated*/, unsigned line/*!=0*/)
{
	return gt_parser_err_prepend_at(
		err_buf, err_buf_size,
		filename_reserve/*0?*/, filename/*NULL?,'\0'-terminated*/,
		err, line, 0);
}

/* same as gt_parser_err_prepend_at(), but don't print line number */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Check_return
A_Ret_z
A_Nonnull_arg(5)
A_At(err_buf, A_Pre_writable_size(err_buf_size))
A_At(filename, A_In_opt_z)
A_At(err, A_In_z)
A_Pre_satisfies(column)
#endif
static inline const char *gt_parser_err_prepend_at_char(
	char err_buf[/*err_buf_size*/], size_t err_buf_size,
	size_t filename_reserve/*0?*/, const char *filename/*NULL?,'\0'-terminated*/,
	const char *err/*!=NULL,'\0'-terminated*/, unsigned column/*!=0*/)
{
	return gt_parser_err_prepend_at(
		err_buf, err_buf_size,
		filename_reserve/*0?*/, filename/*NULL?,'\0'-terminated*/,
		err, 0, column);
}

/* don't reserve space for file name (if parsing a buffer instead of a source file) */
#define gt_parser_err_prepend_at_(err_buf, err_buf_size, err, line, column) \
	gt_parser_err_prepend_at(err_buf, err_buf_size, /*filename_reserve:*/0, /*filename:*/NULL, err, line, column)

#define gt_parser_err_prepend_at_line_(err_buf, err_buf_size, err, line) \
	gt_parser_err_prepend_at_line(err_buf, err_buf_size, /*filename_reserve:*/0, /*filename:*/NULL, err, line)

#define gt_parser_err_prepend_at_char_(err_buf, err_buf_size, err, column) \
	gt_parser_err_prepend_at_char(err_buf, err_buf_size, /*filename_reserve:*/0, /*filename:*/NULL, err, column)

/* print formatted message in error buffer,
  trim message tail if necessary to fit it in the buffer,
  returns pointer to next char after printed message or end */
/* NOTE: error buffer may be not '\0'-terminated after the call - use gt_parser_err_finish() */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_arg(1)
A_Nonnull_arg(2)
A_Nonnull_arg(3)
A_At(buf, A_Out_writes_to_ptr(end))
A_At(end, A_Notnull)
A_At(format, A_Printf_format_string)
A_Printf_format_at(3, 4)
#elif (defined(__GNUC__) && (__GNUC__ > 3 || (3 == __GNUC__ && __GNUC_MINOR__ >= 1))) || \
  (defined(__clang__) && (__clang_major__ > 3 || (3 == __clang_major__  && __clang_minor__ >= 8)))
__attribute__ ((format(printf, 3, 4)))
#elif defined(_MSC_VER) && defined(_SAL_VERSION) && (_SAL_VERSION >= 20)
_At_(format, _Printf_format_string_)
#endif
GTPARSER_EXPORTS char *gt_parser_err_print(char *buf/*<=end*/, const char *const end, const char *format/*'\0'-terminated*/, ...);

/* append string to error buffer,
  trim string tail if necessary to fit it in the buffer,
  returns pointer to next char after appended string or end */
/* NOTE: error buffer may be not '\0'-terminated after the call - use gt_parser_err_finish() */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(buf, A_Out_writes_to_ptr(end))
A_At(end, A_Notnull)
A_At(string, A_In_z)
#endif
GTPARSER_EXPORTS char *gt_parser_err_print_string(char *buf/*<=end*/, const char *const end, const char *string/*'\0'-terminated*/);

/* append chars to error buffer,
  trim chars array tail if necessary to fit it in the buffer,
  returns pointer to next char after appended chars or end */
/* NOTE: error buffer may be not '\0'-terminated after the call - use gt_parser_err_finish() */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_arg(1)
A_Nonnull_arg(2)
A_At(buf, A_Out_writes_to_ptr(end))
A_At(end, A_Notnull)
A_At(chars, A_In_reads(count))
#endif
GTPARSER_EXPORTS char *gt_parser_err_print_chars(char *buf/*<=end*/, const char *const end, const char chars[], size_t count);

/* append character to error buffer if there is a place for it,
  returns pointer to next char after appended char or end */
/* NOTE: error buffer may be not '\0'-terminated after the call - use gt_parser_err_finish() */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(buf, A_Notnull)
A_At(end, A_Notnull)
A_Pre_satisfies(buf <= end)
#endif
static inline char *gt_parser_err_print_char(char *buf/*<=end*/, const char *const end, char c)
{
	if (buf != end)
		*buf++ = c;
	return buf;
}

/* append string constant to error buffer,
  trim string tail if necessary to fit it in the buffer,
  returns pointer to next char after appended string or end */
/* NOTE: error buffer may be not '\0'-terminated after the call - use gt_parser_err_finish() */
#define gt_parser_err_print_string_constant(buf/*<=end*/, end, s) \
	gt_parser_err_print_chars(buf, end, s, sizeof("" s) - 1)

/* terminate error buffer with '\0' */
/* err_space - error buffer size */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Nonnull_all_args
A_At(buf, A_Notnull)
A_At(end, A_Notnull)
A_Pre_satisfies(buf <= end)
#endif
static inline void gt_parser_err_finish(char *buf/*<=end*/, const char *const end, size_t err_space)
{
	if (buf < end)
		*buf = '\0';
	else if (err_space)
		buf[-1] = '\0';
}

#ifdef __cplusplus
}
#endif

#endif /* PARSER_ERR_H_INCLUDED */
