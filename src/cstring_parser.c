/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2018 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* cstring_parser.c */

#include "gtparser/gtparser_config.h"
#include "gtparser/cstring_parser.h"
#include "gtparser/parser_base.h"
#include "gtparser/parser_z_base.h"
//#include "gtparser/name_scanner.h"
#include "gtparser/char_func.h"

#define ENDPARAM           , const char *const end
#define ITER_NEXT(current) src_iter_next_(current, end)
#include "cstring_parser.inl"
#undef ENDPARAM
#undef ITER_NEXT

GTPARSER_EXPORTS enum GT_PARSE_CSTRING_ERR gt_parse_cstring(struct src_iter *it, size_t *removed/*out*/)
{
	const char *current = it->current;
	size_t removed_ = 0;
#ifdef GTPARSER_FLAT_MEMORY_MODEL
	enum GT_PARSE_CSTRING_ERR r = parse_cstring(&it->line, &current,
		&it->back_column, &removed_, GTPARSER_TAB_SIZE(it), it->end);
#else
	enum GT_PARSE_CSTRING_ERR r = parse_cstring(&it->line, &current,
		&it->line_ptr, &it->back_column, &removed_, GTPARSER_TAB_SIZE(it), it->end);
#endif
	it->current = current;
	*removed = removed_;
	return r;
}

#define ENDPARAM
#define ITER_NEXT(current) src_iter_z_next_(current)
#define parse_cstring parse_cstring_z
#include "cstring_parser.inl"
#undef ENDPARAM
#undef ITER_NEXT

GTPARSER_EXPORTS enum GT_PARSE_CSTRING_ERR gt_parse_cstring_z(struct src_iter_z *it, size_t *removed/*out*/)
{
	const char *current = it->current;
	size_t removed_ = 0;
#ifdef GTPARSER_FLAT_MEMORY_MODEL
	enum GT_PARSE_CSTRING_ERR r = parse_cstring_z(&it->line, &current,
		&it->back_column, &removed_, GTPARSER_TAB_SIZE(it));
#else
	enum GT_PARSE_CSTRING_ERR r = parse_cstring_z(&it->line, &current,
		&it->line_ptr, &it->back_column, &removed_, GTPARSER_TAB_SIZE(it));
#endif
	it->current = current;
	*removed = removed_;
	return r;
}

GTPARSER_EXPORTS void gt_copy_cstring(char dst[]/*out*/, const char *begin, const char *end, size_t removed)
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
						unsigned n = hex_char_value_(*begin++);
						ASSERT(n <= 15); /* otherwise invalid string was parsed */
						if (--removed) { /* x in "\xF" */
							ASSERT(begin < end); /* otherwise invalid string was parsed */
							{
								unsigned m = hex_char_value_(*begin);
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
