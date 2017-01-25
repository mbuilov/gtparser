#ifndef NAME_SCANNER_H_INCLUDED
#define NAME_SCANNER_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2017 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* name_scanner.h */

#include "gtparser/gtparser.h"
#include "gtparser/char_func.h"

#ifdef __cplusplus
extern "C" {
#endif

GTPARSER_EXPORTS extern const char _is_next_name_lookup_table[1u + (unsigned char)~(unsigned char)0u];

static inline int is_first_name(char c)
{
	return _is_next_name_lookup_table[(unsigned char)c] >= 20;
}

static inline int is_next_name(char c)
{
	return _is_next_name_lookup_table[(unsigned char)c];
}

/* returns hex char value or >15 if non-hex char */
static inline unsigned hex_char_value(char c)
{
	unsigned x = (unsigned char)_is_next_name_lookup_table[(unsigned char)c];
#ifdef _DEBUG
	if (x < 10u)
		x += (~0u - 10u) + 1u;
	else
#endif
		x -= 10u;
	return x;
}

/* input:  s points to [_a-zA-Z] */
/* output: s points to non-[_a-zA-Z0-9], may be to end */
GTPARSER_EXPORTS const char *_scan_name(const char *s/*<end*/, const char *const end)
#ifdef __GNUC__
__attribute__ ((pure))
#endif
;

#ifdef __cplusplus
}
#endif

#endif /* NAME_SCANNER_H_INCLUDED */
