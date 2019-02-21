/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2018-2019 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* cstring_parser.inl */

/* ENDPARAM           - <empty> or <, const char *const end> */
/* ITER_NEXT(current) - src_iter_z_next_(current) or src_iter_next_(current, end) */
static enum GT_PARSE_CSTRING_ERR parse_cstring(
	struct src_iter_loc *const loc,
	const char **const current,
	size_t *const removed,
	const unsigned tab_size ENDPARAM)
{
	const char quote = src_iter_current_char_(*current);
	while (ITER_NEXT(current)) {
		char c = src_iter_current_char_(*current);
switch_c:
		if (quote == c)
			return GT_PARSE_CSTRING_OK; /* it points to the last quote */
		if ('\n' == c || '\r' == c)
			return GT_PARSE_CSTRING_UNESCAPED_NEWLINE; /* unescaped line-feed or carriage-return */
		if ('\\' == c) {
			if (!ITER_NEXT(current))
				break; /* error: unterminated string */
			(*removed)++; /* '\' must be removed */
			c = src_iter_current_char_(*current);
			if ('\r' == c) {
				if (!ITER_NEXT(current))
					break; /* error: unterminated string */
				c = src_iter_current_char_(*current);
				if ('\n' != c)
					return GT_PARSE_CSTRING_EXPECTING_LINE_FEED; /* expecting line-feed after carriage-return */
				(*removed) += 2; /* line continuation (split) must be removed */
			}
			else if ('\n' == c)
				(*removed)++; /* line continuation (split) must be removed */
			else if ('x' == c) {
				/* hexadecimal constant */
				if (!ITER_NEXT(current))
					break; /* error: unterminated string */
				c = src_iter_current_char_(*current);
				{
					const unsigned n = hex_char_value_(c);
					if (n > 15)
						return GT_PARSE_CSTRING_EXPECTING_HEX_DIGIT; /* expecting hexadecimal digit in hex escape sequence after \x */
					if (!ITER_NEXT(current))
						break; /* error: unterminated string */
					c = src_iter_current_char_(*current);
					{
						const unsigned m = hex_char_value_(c);
						if (m <= 15 && n + m) {
							(*removed) += 2; /* xf in "\xff" */
							continue;
						}
					}
					if (n) {
						(*removed)++; /* x in "\xf" */
						goto switch_c;
					}
					(*current)--; /* points to 0 in "\x0?" */
					c = '\0'; /* error: null inside string */
				}
			}
			else {
				unsigned n = digit_value(c);
				if (n <= 7) {
					/* octal constant */
					if (!ITER_NEXT(current))
						break; /* error: unterminated string */
					c = src_iter_current_char_(*current);
					{
						unsigned m = digit_value(c);
						if (m <= 7) {
							if (!ITER_NEXT(current))
								break; /* error: unterminated string */
							n = n*8 + m;
							c = src_iter_current_char_(*current);
							m = digit_value(c);
							if (m <= 7) {
								if (n*8 + m > 255) {
									(*current) -= 2; /* points to 777 in "\777" */
									return GT_PARSE_CSTRING_TOO_BIG_OCTAL; /* too big octal character value > 255 in string */
								}
								if (n + m) {
									(*removed) += 2; /* 12 in "\123" */
									continue;
								}
							}
							else if (n) {
								(*removed)++; /* 1 in "\12" */
								goto switch_c;
							}
							(*current)--; /* error: null inside string */
						}
						else if (n)
							goto switch_c;
					}
					(*current)--; /* points to first 0 in "\000" or in "\00" or in "\0" */
					c = '\0'; /* error: null inside string */
				}
			}
		}
		if ('\0' == c)
			return GT_PARSE_CSTRING_NULL_INSIDE_CSTRING; /* null character (with zero value) inside string is not allowed */
		src_iter_check_(&loc->line, &loc->back_column, *current, tab_size);
	}
	return GT_PARSE_CSTRING_UNTERMINATED; /* unterminated string */
}
