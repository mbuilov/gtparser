#ifndef NAME_PARSER_H_INCLUDED
#define NAME_PARSER_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2017 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* name_parser.h */

#include "gtparser/parser_base.h"
#include "gtparser/name_scanner.h"

#ifdef __cplusplus
extern "C" {
#endif

/* assume (*current) points to first name character,
  returns scanned name */
/* NOTE: after return it->current points to non-[_a-zA-Z0-9], may be to end */
static inline const char *_read_name(const char **current, const char *end)
{
	const char *name = *current;
	*current = gt_scan_name(*current, end);
	return name;
}

/* assume it->current points to first name character,
  returns scanned name */
/* NOTE: after return it->current points to non-[_a-zA-Z0-9], may be to end */
static inline const char *read_name(struct src_iter *it)
{
	return _read_name(&it->current, it->end);
}

#ifdef __cplusplus
}
#endif

#endif /* NAME_PARSER_H_INCLUDED */
