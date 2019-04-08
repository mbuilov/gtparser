/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2018 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* parser_err.c */

#include "gtparser/gtparser_system.h"
#include "gtparser/parser_err.h"

#define PE_MAX_OF(a,b) ((a)>(b)?(a):(b))

#ifndef GTPARSER_ERROR_AT
#define GTPARSER_ERROR_AT "parse error at "
#endif

#ifndef GTPARSER_ERROR_LINE
#define GTPARSER_ERROR_LINE "line"
#endif

#ifndef GTPARSER_ERROR_COLUMN
#define GTPARSER_ERROR_COLUMN "char"
#endif

#define pe_reserve1 sizeof(GTPARSER_ERROR_AT "(4294967295:4294967295):")           /* note: take into account terminating '\0' */
#define pe_reserve2 sizeof(GTPARSER_ERROR_AT GTPARSER_ERROR_LINE   " 4294967295:") /* note: take into account terminating '\0' */
#define pe_reserve3 sizeof(GTPARSER_ERROR_AT GTPARSER_ERROR_COLUMN " 4294967295:") /* note: take into account terminating '\0' */
#define PE_RESERVE (PE_MAX_OF(pe_reserve1, PE_MAX_OF(pe_reserve2, pe_reserve3)))

#ifndef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
#define A_Use_decl_annotations
#endif

A_Use_decl_annotations
GTPARSER_EXPORTS char *gt_parser_err_reserve(char err_buf[], size_t err_buf_size, size_t filename_reserve/*0?*/)
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

A_Use_decl_annotations
GTPARSER_EXPORTS const char *gt_parser_err_prepend_at(char err_buf[], size_t err_buf_size, size_t filename_reserve/*0?*/,
	const char *filename/*NULL?,'\0'-terminated*/, const char *err, unsigned line, unsigned column)
{
	const char *const buf = gt_parser_err_reserve(err_buf, err_buf_size, filename_reserve);
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
			/* buf has at least one byte free before err_buf_end - guaranteed by gt_parser_err_reserve() */
			int printed =
				!line   ? SPRINTF(err_buf_tail, GTPARSER_ERROR_AT "char %u:", column & 4294967295u) :
				!column ? SPRINTF(err_buf_tail, GTPARSER_ERROR_AT "line %u:", line & 4294967295u) :
				          SPRINTF(err_buf_tail, GTPARSER_ERROR_AT "(%u:%u):", line & 4294967295u, column & 4294967295u);
			err_buf_tail[printed++] = ' '; /* eat one byte reserved by '\0' in PE_RESERVE */
			if (err != buf) {
				char *dst = err_buf_tail + printed; /* (dst < err_buf + err_buf_size) because (err_buf_size > PE_RESERVE) */
				const size_t free = (size_t)(err_buf + err_buf_size - dst) - 1/*for terminating '\0'*/; /* >= 0 */
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
				const size_t gap = (size_t)(err - printed - err_buf_tail);
				if (gap)
					MEMMOVE(err_buf + gap, err_buf, (size_t)(err_buf_tail + printed - err_buf)); /* move forward */
				err = err_buf + gap;
			}
		}
	}
	return err;
}

A_Use_decl_annotations
GTPARSER_EXPORTS char *gt_parser_err_print_chars(char *buf/*<=end*/, const char *const end, const char chars[], size_t count)
{
	const size_t buf_size = (size_t)(end - buf);
	if (count > buf_size)
		count = buf_size; /* trim chars array tail */
	MEMCPY(buf, chars, count);
	return buf + count;
}

A_Use_decl_annotations
GTPARSER_EXPORTS char *gt_parser_err_print_string(char *buf/*<=end*/, const char *const end, const char *string/*'\0'-terminated*/)
{
	return gt_parser_err_print_chars(buf, end, string, STRLEN(string));
}

#ifdef SAL_DEFS_H_INCLUDED
A_Use_decl_annotations
#elif defined(_MSC_VER) && defined(_SAL_VERSION) && (_SAL_VERSION >= 20)
_At_(format, _Printf_format_string_)
#endif
GTPARSER_EXPORTS char *gt_parser_err_print(char *buf/*<=end*/, const char *const end, const char *format/*'\0'-terminated*/, ...)
{
	va_list args;
	va_start(args, format);
	{
		size_t buf_size = (size_t)(end - buf);
		const int n = VSNPRINTF(buf, buf_size, format, args);
		if (n < 0 || (size_t)n > buf_size)
			buf += buf_size;
		else
			buf += n;
	}
	va_end(args);
	return buf;
}
