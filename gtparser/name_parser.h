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

/* assume (*current) pointts to first name character,
  returns scanned name */
static inline const char *_read_name(const char **current, const char *end)
{
	const char *name = *current;
	*current = _scan_name(*current, end);
	return name;
}

/* assume it->current pointts to first name character,
  returns scanned name */
static inline const char *read_name(struct src_iter *it)
{
	return _read_name(&it->current, it->end);
}

#ifdef __cplusplus
}
#endif

#endif /* NAME_PARSER_H_INCLUDED */
