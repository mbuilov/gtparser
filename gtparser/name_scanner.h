#ifndef NAME_SCANNER_H_INCLUDED
#define NAME_SCANNER_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2018 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* name_scanner.h */

#include "gtparser/gtparser.h"
#include "gtparser/char_func.h"

#ifdef __cplusplus
extern "C" {
#endif

GTPARSER_EXPORTS
extern const char gt_is_next_name_lookup_table[1u + (unsigned char)-1];

/* check if c is in [_a-zA-Z] */
static inline int is_first_name(char c)
{
	return gt_is_next_name_lookup_table[(unsigned char)c] >= 20;
}

/* check if c is in [_a-zA-Z0-9] */
static inline int is_next_name(char c)
{
	return gt_is_next_name_lookup_table[(unsigned char)c];
}

/* returns hex char value or >15 if non-hex char */
static inline unsigned hex_char_value(char c)
{
	unsigned x = (unsigned char)gt_is_next_name_lookup_table[(unsigned char)c];
#ifdef UBSAN_UNSIGNED_OVERFLOW
	if (x < 10u)
		x += ((unsigned)-1 - 10u) + 1u;
	else
#endif
		x -= 10u;
	return x;
}

/* input:  s points to [_a-zA-Z] */
/* output: s points to non-[_a-zA-Z0-9], may be to end */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Ret_notnull
A_Nonnull_all_args
A_At(s, A_In_reads_to_ptr(end))
A_At(end, A_Notnull)
#endif
GTPARSER_EXPORTS const char *gt_scan_name(const char *s/*<end*/, const char *const end)
#ifdef __GNUC__
__attribute__ ((pure))
#endif
;

/* input:  s points to [_a-zA-Z] */
/* output: s points to non-[_a-zA-Z0-9], may be to '\0' */
#ifdef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
A_Ret_notnull
A_Nonnull_all_args
A_At(s, A_In_z)
#endif
GTPARSER_EXPORTS const char *gt_scan_name_z(const char *s/*'\0'-terminated*/)
#ifdef __GNUC__
__attribute__ ((pure))
#endif
;

#ifdef __cplusplus
}
#endif

#endif /* NAME_SCANNER_H_INCLUDED */
