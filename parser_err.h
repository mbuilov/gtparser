#ifndef PARSER_ERR_H_INCLUDED
#define PARSER_ERR_H_INCLUDED

/*******************************************************************************
* Generic Text parsing functions
* Copyright (C) 2008-2017 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* parser_err.h */

/* declaration for exported functions, such as __declspec(dllexport)/__declspec(dllimport) or __attribute__((visibility("default"))) */
#ifndef GTPARSER_EXPORTS
#define GTPARSER_EXPORTS
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* if error buffer is big enough, then reserve some space at front of it for error prefix:
  "filename: parse error at (4294967295:4294967295):" */
/* filename_reserve - how much space to reserve for printing file name passed to parser_err_prepend_at...() */
/* returns pointer to space inside error buffer to print error message to
  or returns err_buf, if err_buf_size is not big enough */
GTPARSER_EXPORTS char *parser_err_reserve(char err_buf[/*err_buf_size*/], size_t err_buf_size, size_t filename_reserve/*0?*/)
#ifdef __GNUC__
__attribute__ ((const))
#endif
;

/* don't reserve space for file name */
#define parser_err_reserve_(err_buf, err_buf_size) \
	parser_err_reserve(err_buf, err_buf_size, /*filename_reserve:*/0)

/* if error buffer is big enough, then compose error message in form
  "filename: parse error at (0:0): error message" */
/* err_buf, err_buf_size, filename_reserve - the same values that were passed to parser_err_reserve()
  if error message was printed to err_buf (i.e. err points inside err_buf[err_buf_size]) */
/* filename - if not NULL, then '\0'-terminated C-string */
/* returns passed err or pointer to error message inside error buffer */
GTPARSER_EXPORTS const char *parser_err_prepend_at(
	char err_buf[/*err_buf_size*/], size_t err_buf_size,
	size_t filename_reserve/*0?*/, const char *filename/*NULL?,'\0'-terminated*/,
	const char *err/*!=NULL*/, unsigned line/*0?*/, unsigned column/*0?*/);

/* same as parser_err_prepend_at(), but don't print column number */
static inline const char *parser_err_prepend_at_line(
	char err_buf[/*err_buf_size*/], size_t err_buf_size,
	size_t filename_reserve/*0?*/, const char *filename/*NULL?,'\0'-terminated*/,
	const char *err/*!=NULL*/, unsigned line/*!=0*/)
{
	return parser_err_prepend_at(
		err_buf, err_buf_size,
		filename_reserve/*0?*/, filename/*NULL?,'\0'-terminated*/,
		err, line, 0);
}

/* same as parser_err_prepend_at(), but don't print line number */
static inline const char *parser_err_prepend_at_char(
	char err_buf[/*err_buf_size*/], size_t err_buf_size,
	size_t filename_reserve/*0?*/, const char *filename/*NULL?,'\0'-terminated*/,
	const char *err/*!=NULL*/, unsigned column/*!=0*/)
{
	return parser_err_prepend_at(
		err_buf, err_buf_size,
		filename_reserve/*0?*/, filename/*NULL?,'\0'-terminated*/,
		err, 0, column);
}

/* don't reserve space for file name */
#define parser_err_prepend_at_(err_buf, err_buf_size, err, line, column) \
	parser_err_prepend_at(err_buf, err_buf_size, /*filename_reserve:*/0, /*filename:*/NULL, err, line, column)

#define parser_err_prepend_at_line_(err_buf, err_buf_size, err, line) \
	parser_err_prepend_at_line(err_buf, err_buf_size, /*filename_reserve:*/0, /*filename:*/NULL, err, line)

#define parser_err_prepend_at_char_(err_buf, err_buf_size, err, column) \
	parser_err_prepend_at_char(err_buf, err_buf_size, /*filename_reserve:*/0, /*filename:*/NULL, err, column)

/* print error message into err_buf as follows:

  PARSER_ERR_START
  PARSER_ERR_PRINT_CONSTANT("error message");
  PARSER_ERR_PRINT_STRING_LEN(cstr, len);
  PARSER_ERR_PRINT_STRING(msg_cstr);
  PARSER_ERR_PRINT_CHAR('x');
  PARSER_ERR_END
*/

static inline char *parser_err_print_char(char c, char *buf/*<=end*/, const char *const end)
{
	if (buf < end)
		*buf++ = c;
	return buf;
}

/* print c-string to buffer,
  trim printed string if necessary,
  returns pointer to next char in buf after printed string */
GTPARSER_EXPORTS char *parser_err_print_string(const char *string, char *buf, const char *const end);

/* same as parser_err_print_string(), but print only string_len chars of string */
GTPARSER_EXPORTS char *_parser_err_print_string(const char *string, size_t string_len, char *buf, const char *const end);

/* err_buf and err_buf_size must be defined */
#define PARSER_ERR_START \
if (err_buf_size) { \
	char *__buf = err_buf; const char *const __end = __buf + err_buf_size - 1/*'\0'*/;

#define PARSER_ERR_PRINT_CONSTANT(__string) \
	__buf = _parser_err_print_string(__string"", sizeof(__string"") - 1 + \
		0*sizeof(int[1-2*(1 == sizeof(__string))]) + \
		0*sizeof(int[1-2*(sizeof(__string) > (~0u >> 1))]), __buf, __end)

#define PARSER_ERR_PRINT_STRING_LEN(__str, __len) \
	__buf = _parser_err_print_string(__str, __len, __buf, __end)

#define PARSER_ERR_PRINT_STRING(__str) \
	__buf = parser_err_print_string(__str, __buf, __end)

#define PARSER_ERR_PRINT_CHAR(__c) \
	__buf = parser_err_print_char(__c, __buf, __end)

#define PARSER_ERR_END \
	*__buf = '\0'; \
}

#ifdef __cplusplus
}
#endif

#endif /* PARSER_ERR_H_INCLUDED */
