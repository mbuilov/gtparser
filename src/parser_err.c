/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2017 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* parser_err.c */

#include "gtparser/gtparser_config.h"
#include "gtparser/parser_err.h"

#define __MAX_OF__(a,b) ((a)>(b)?(a):(b))
#define pe_reserve1 sizeof("parse error at (4294967295:4294967295):") /* note: take into account teminating '\0' in string constant */
#define pe_reserve2 sizeof("parse error at line 4294967295:")         /* note: take into account teminating '\0' in string constant */
#define pe_reserve3 sizeof("parse error at char 4294967295:")         /* note: take into account teminating '\0' in string constant */
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
			size_t filename_len = GTPARSER_STRLEN(filename);
			if (filename_len > filename_reserve) {
				/* trim head of filename */
				filename += filename_len - filename_reserve;
				filename_len = filename_reserve;
			}
			GTPARSER_MEMCPY(err_buf, filename, filename_len);
			err_buf[filename_len++] = ':';
			err_buf[filename_len++] = ' ';
			err_buf_tail = err_buf + filename_len;
		}
		{
			/* buf has at least one byte free before err_buf_end - guaranteed by parser_err_reserve() */
			int printed =
				!line ? GTPARSER_SPRINTF(err_buf_tail, "parse error at char %u:", column & 4294967295u) :
				!column ? GTPARSER_SPRINTF(err_buf_tail, "parse error at line %u:", line & 4294967295u) :
				GTPARSER_SPRINTF(err_buf_tail, "parse error at (%u:%u):", line & 4294967295u, column & 4294967295u);
			err_buf_tail[printed++] = ' '; /* eat one byte reserved by '\0' in PE_RESERVE */
			if (err != buf) {
				char *dst = err_buf_tail + printed; /* (dst < err_buf + err_buf_size) because (err_buf_size > PE_RESERVE) */
				size_t free = (size_t)(err_buf + err_buf_size - dst) - 1/*for terminating '\0'*/; /* >= 0 */
				if (free) {
					size_t len = GTPARSER_STRLEN(err);
					if (len > free)
						len = free; /* trim tail of error message */
					GTPARSER_MEMCPY(dst, err, len);
					dst[len] = '\0';
				}
				err = err_buf;
			}
			else {
				/* [filename][printed]<-gap->[err]
				   ^err_buf  ^err_buf_tail   ^err  */
				size_t gap = (size_t)(err - printed - err_buf_tail);
				if (gap)
					GTPARSER_MEMMOVE(err_buf + gap, err_buf, (size_t)(err_buf_tail + printed - err_buf)); /* move forward */
				err = err_buf + gap;
			}
		}
	}
	return err;
}

GTPARSER_EXPORTS char *_parser_err_print_string(const char *string, size_t string_len, char *buf, const char *const end)
{
	if (string_len > (unsigned)(end - buf))
		string_len = (unsigned)(end - buf); /* trim string tail */
	GTPARSER_MEMCPY(buf, string, string_len);
	return buf + string_len;
}

GTPARSER_EXPORTS char *parser_err_print_string(const char *string, char *buf, const char *const end)
{
	return _parser_err_print_string(string, GTPARSER_STRLEN(string), buf, end);
}
