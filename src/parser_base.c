/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2017 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* parser_base.c */

#include "gtparser/parser_base.h"

/* it points to checked char */
GTPARSER_EXPORTS void _skip_rest_of_line(struct src_iter *it)
{
	const char *s = it->current;
	while (_src_iter_next(&s, it->end)) {
		_src_iter_check(&it->line, &it->back_column, s, GTPARSER_TAB_SIZE);
		if ('\n' == _src_iter_current(s)) {
			_src_iter_step(&s);
			break;
		}
	}
	it->current = s; /* it points to char after '\n', may be to eof */
}

/* it points to unchecked char or to eof */
GTPARSER_EXPORTS char read_non_space_skip_comments(struct src_iter *it, char comment)
{
	while (!src_iter_eof(it)) {
		char c = src_iter_current(it);
		if (comment == c) {
			_skip_comment(it);
			continue;
		}
		if (!is_space(c))
			return c;
		src_iter_check(it);
		src_iter_step(it);
	}
	return '\0'; /* failed to read non-space, it points to eof */
}

/* it points to unchecked char or to eof */
GTPARSER_EXPORTS char read_non_space_stop_eol(struct src_iter *it)
{
	while (!src_iter_eof(it)) {
		char c = src_iter_current(it);
		if ('\n' == c || !is_space(c))
			return c;
		src_iter_check_tab(it);
		src_iter_step(it);
	}
	return '\0'; /* failed to read non-space, it points to eof */
}
