/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2017 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* parser_err.c */

#include "gtparser/gtparser_config.h"
#include "gtparser/parser_err.h"

#define __MAX_OF__(a,b) ((a)>(b)?(a):(b))
#define parse_error_at "parse error at "
#define pe_reserve1 sizeof(parse_error_at "(4294967295:4294967295):") /* note: take into account terminating '\0' in string constant */
#define pe_reserve2 sizeof(parse_error_at "line 4294967295:")         /* note: take into account terminating '\0' in string constant */
#define pe_reserve3 sizeof(parse_error_at "char 4294967295:")         /* note: take into account terminating '\0' in string constant */
#define PE_RESERVE (__MAX_OF__(pe_reserve1, __MAX_OF__(pe_reserve2, pe_reserve3)))

GTPARSER_EXPORTS char *parser_err_reserve(char err_buf[], size_t err_buf_size, size_t filename_reserve/*0?*/)
{
	char *buf = err_buf;
	if (err_buf_size > PE_RESERVE) {
		buf += PE_RESERVE;
		if (filename_reserve) {
			err_buf_size -= PE_RESERVE;
			if (err_buf_size > 2/*": "*/ && err_buf_size - 2 > filename_reserve)
				buf += filename_reserve + 2/*": "*/;
		}
	}
	return buf;
}

GTPARSER_EXPORTS const char *parser_err_prepend_at(char err_buf[], size_t err_buf_size, size_t filename_reserve/*0?*/,
	const char *filename/*NULL?,'\0'-terminated*/, const char *err, unsigned line, unsigned column)
{
	char *buf = parser_err_reserve(err_buf, err_buf_size, filename_reserve);
	if (buf != err_buf) {
		char *err_buf_tail = err_buf;
		if (buf != err_buf + PE_RESERVE && filename) {
			size_t filename_len = STRLEN(filename);
			if (filename_len > filename_reserve) {
				/* trim head of filename */
				filename += filename_len - filename_reserve;
				filename_len = filename_reserve;
			}
			MEMCPY(err_buf, filename, filename_len);
			err_buf[filename_len++] = ':';
			err_buf[filename_len++] = ' ';
			err_buf_tail = err_buf + filename_len;
		}
		{
			/* buf has at least one byte free before err_buf_end - guaranteed by parser_err_reserve() */
			int printed =
				!line   ? SPRINTF(err_buf_tail, parse_error_at "char %u:", column & 4294967295u) :
				!column ? SPRINTF(err_buf_tail, parse_error_at "line %u:", line & 4294967295u) :
				          SPRINTF(err_buf_tail, parse_error_at "(%u:%u):", line & 4294967295u, column & 4294967295u);
			err_buf_tail[printed++] = ' '; /* eat one byte reserved by '\0' in PE_RESERVE */
			if (err != buf) {
				char *dst = err_buf_tail + printed; /* (dst < err_buf + err_buf_size) because (err_buf_size > PE_RESERVE) */
				size_t free = (size_t)(err_buf + err_buf_size - dst) - 1/*for terminating '\0'*/; /* >= 0 */
				if (free) {
					size_t len = STRLEN(err);
					if (len > free)
						len = free; /* trim tail of error message */
					MEMCPY(dst, err, len);
					dst[len] = '\0';
				}
				err = err_buf;
			}
			else {
				/* [filename][printed]<-gap->[err]
				   ^err_buf  ^err_buf_tail   ^err  */
				size_t gap = (size_t)(err - printed - err_buf_tail);
				if (gap)
					MEMMOVE(err_buf + gap, err_buf, (size_t)(err_buf_tail + printed - err_buf)); /* move forward */
				err = err_buf + gap;
			}
		}
	}
	return err;
}

GTPARSER_EXPORTS char *parser_err_print_chars(char *buf/*<=end*/, const char *const end, const char chars[], size_t count)
{
	size_t buf_size = (size_t)(end - buf);
	if (count > buf_size)
		count = buf_size; /* trim chars array tail */
	MEMCPY(buf, chars, count);
	return buf + count;
}

#if (defined(__GNUC__) && (__GNUC__ > 3 || (3 == __GNUC__ && __GNUC_MINOR__ >= 1))) || \
    (defined(__clang__) && (__clang_major__ > 3 || (3 == __clang_major__  && __clang_minor__ >= 8)))
__attribute__ ((format(printf, 3, 4)))
#elif defined(_MSC_VER) && defined(_SAL_VERSION) && (_SAL_VERSION >= 20)
_At_(format, _Printf_format_string_)
#endif
GTPARSER_EXPORTS char *parser_err_print(char *buf/*<=end*/, const char *const end, const char *format/*'\0'-terminated*/, ...)
{
	va_list args;
	va_start(args, format);
	{
		size_t buf_size = (size_t)(end - buf);
		int n = VSNPRINTF(buf, buf_size, format, args);
		if (n < 0 || (size_t)n > buf_size)
			buf += buf_size;
		else
			buf += n;
	}
	va_end(args);
	return buf;
}
