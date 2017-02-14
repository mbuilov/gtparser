/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2017 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* cstring_parser.c */

#include "gtparser/gtparser_config.h"
#include "gtparser/cstring_parser.h"
#include "gtparser/parser_base.h"
#include "gtparser/name_scanner.h"

static enum PARSE_CSTRING_ERR _parse_cstring(unsigned *line, const char **current,
	unsigned *back_column, size_t *removed, const char *const end)
{
	const char quote = _src_iter_get_char(*current);
	while (_src_iter_next(current, end)) {
		char c = _src_iter_get_char(*current);
_switch_c:
		if (quote == c)
			return PARSE_CSTRING_OK; /* it points to the last quote */
		if ('\n' == c || '\r' == c)
			return PARSE_CSTRING_UNESCAPED_NEWLINE; /* unescaped line-feed or carridge-return */
		if ('\\' == c) {
			if (!_src_iter_next(current, end))
				break; /* error: unterminated string */
			(*removed)++; /* '\' must be removed */
			c = _src_iter_get_char(*current);
			if ('\r' == c) {
				if (!_src_iter_next(current, end))
					break; /* error: unterminated string */
				c = _src_iter_get_char(*current);
				if ('\n' != c)
					return PARSE_CSTRING_EXPECTING_LINE_FEED; /* expecting line-feed after carridge-return */
				(*removed) += 2; /* line continuation (split) must be removed */
			}
			else if ('\n' == c)
				(*removed)++; /* line continuation (split) must be removed */
			else if ('x' == c) {
				/* hexadecimal constant */
				if (!_src_iter_next(current, end))
					break; /* error: unterminated string */
				c = _src_iter_get_char(*current);
				{
					unsigned n = _hex_char_value(c);
					if (n > 15)
						return PARSE_CSTRING_EXPECTING_HEX_DIGIT; /* expecting hexadecimal digit in hex escape sequence after \x */
					if (!_src_iter_next(current, end))
						break; /* error: unterminated string */
					c = _src_iter_get_char(*current);
					{
						unsigned m = _hex_char_value(c);
						if (m <= 15 && n + m) {
							(*removed) += 2; /* xf in "\xff" */
							continue;
						}
					}
					if (n) {
						(*removed)++; /* x in "\xf" */
						goto _switch_c;
					}
					(*current)--; /* points to 0 in "\x0?" */
					c = '\0'; /* error: null inside string */
				}
			}
			else {
				unsigned n = digit_value(c);
				if (n <= 7) {
					/* octal constant */
					if (!_src_iter_next(current, end))
						break; /* error: unterminated string */
					c = _src_iter_get_char(*current);
					{
						unsigned m = digit_value(c);
						if (m <= 7) {
							if (!_src_iter_next(current, end))
								break; /* error: unterminated string */
							n = n*8 + m;
							c = _src_iter_get_char(*current);
							m = digit_value(c);
							if (m <= 7) {
								if (n*8 + m > 255) {
									(*current) -= 2; /* points to 777 in "\777" */
									return PARSE_CSTRING_TOO_BIG_OCTAL; /* too big octal character value > 255 in string */
								}
								if (n + m) {
									(*removed) += 2; /* 12 in "\123" */
									continue;
								}
							}
							else if (n) {
								(*removed)++; /* 1 in "\12" */
								goto _switch_c;
							}
							(*current)--; /* error: null inside string */
						}
						else if (n)
							goto _switch_c;
					}
					(*current)--; /* points to first 0 in "\000" or in "\00" or in "\0" */
					c = '\0'; /* error: null inside string */
				}
			}
		}
		if ('\0' == c)
			return PARSE_CSTRING_NULL_INSIDE_CSTRING; /* null character (with zero value) inside string is not allowed */
		_src_iter_check(line, back_column, *current, GTPARSER_TAB_SIZE);
	}
	return PARSE_CSTRING_UNTERMINATED; /* unterminated string */
}

GTPARSER_EXPORTS enum PARSE_CSTRING_ERR parse_cstring(struct src_iter *it, size_t *removed/*out*/)
{
	const char *current = it->current;
	size_t _removed = 0;
	enum PARSE_CSTRING_ERR r = _parse_cstring(&it->line, &current, &it->back_column, &_removed, it->end);
	it->current = current;
	*removed = _removed;
	return r;
}

GTPARSER_EXPORTS void copy_cstring(char dst[]/*out*/, const char *begin, const char *end, size_t removed)
{
	/* copy char-by-char unescaping escape sequences */
	while (removed) {
		char c = *begin++;
		ASSERT(begin < end); /* otherwise invalid string was parsed */
		if ('\\' == c) {
			c = *begin++;
			removed--;
			switch (c) {
				case '\r':
					ASSERT(removed > 1); /* otherwise invalid string was parsed */
					removed--;
					/* fall through */
				case '\n':
					ASSERT(removed); /* otherwise invalid string was parsed */
					removed--;
					continue; /* skip line continuation (split) */
				case 'a': c = '\a'; break;
				case 'b': c = '\b'; break;
				case 't': c = '\t'; break;
				case 'n': c = '\n'; break;
				case 'v': c = '\v'; break;
				case 'f': c = '\f'; break;
				case 'r': c = '\r'; break;
				case 'x':
					ASSERT(begin < end && removed); /* otherwise invalid string was parsed */
					{
						unsigned n = _hex_char_value(*begin++);
						ASSERT(n <= 15); /* otherwise invalid string was parsed */
						if (--removed) { /* x in "\xF" */
							ASSERT(begin < end); /* otherwise invalid string was parsed */
							{
								unsigned m = _hex_char_value(*begin);
								if (m <= 15) {
									begin++;
									n = n*16 + m;
									ASSERT(n < 256);
									removed--; /* A in "\xAB" */
								}
							}
						}
						c = (char)n; /* < 256 */
					}
					break;
				case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7': {
					unsigned n = digit_value(c);
					ASSERT(n <= 7); /* otherwise invalid string was parsed */
					if (removed) {
						ASSERT(begin < end); /* otherwise invalid string was parsed */
						{
							unsigned m = digit_value(*begin);
							if (m <= 7) {
								begin++;
								n = n*8 + m;
								ASSERT(n < 64);
								if (--removed) { /* 1 in "\12" */
									ASSERT(begin < end); /* otherwise invalid string was parsed */
									m = digit_value(*begin);
									if (m <= 7) {
										begin++;
										n = n*8 + m;
										ASSERT(n < 256); /* otherwise invalid string was parsed */
										removed--; /* 2 in "\123" */
									}
								}
							}
						}
					}
					c = (char)n; /* < 256 */
					break;
				}
			}
		}
		ASSERT(c); /* zero character inside string is not allowed */
		*dst++ = c;
	}
	MEMCPY(dst, begin, (size_t)(end - begin));
}
