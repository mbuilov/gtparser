#ifndef INT_PARSER_H_INCLUDED
#define INT_PARSER_H_INCLUDED

/*******************************************************************************
* Generic Text parsing functions
* Copyright (C) 2008-2017 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* int_parser.h */

#include "parser_base.h"
#include "int_scanner.h"

#ifdef __cplusplus
extern "C" {
#endif

/* input:  it->current points to [0-9] */
/* output: it->current points to non-[0-9], may be to end */
/* returns 0 on integer overflow, it->current - not changed */
static inline int read_uint(struct src_iter *it, unsigned *number/*out*/)
{
	const char *s = _scan_uint(it->current, it->end, number/*out*/);
	if (!s)
		return 0; /* integer overlow */
	it->current = s;
	return 1;
}
static inline int read_uint64(struct src_iter *it, unsigned INT64_TYPE *number/*out*/)
{
	const char *s = _scan_uint64(it->current, it->end, number/*out*/);
	if (!s)
		return 0; /* integer overlow */
	it->current = s;
	return 1;
}

/* input:  it->current points to [0-9a-fA-F] */
/* output: it->current points to non-[0-9a-fA-F], may be to end */
/* returns 0 on integer overflow, it->current - not changed */
static inline int read_hex(struct src_iter *it, unsigned *number/*out*/)
{
	const char *s = _scan_hex(it->current, it->end, number/*out*/);
	if (!s)
		return 0; /* integer overlow */
	it->current = s;
	return 1;
}
static inline int read_hex64(struct src_iter *it, unsigned INT64_TYPE *number/*out*/)
{
	const char *s = _scan_hex64(it->current, it->end, number/*out*/);
	if (!s)
		return 0; /* integer overlow */
	it->current = s;
	return 1;
}

#ifdef __cplusplus
}
#endif

#endif /* INT_PARSER_H_INCLUDED */
