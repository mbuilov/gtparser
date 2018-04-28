/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2018 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* parser_base.c */

#include "gtparser/gtparser_config.h"
#include "gtparser/parser_base.h"

/* it points to checked char, likely '#' */
GTPARSER_EXPORTS void gt_skip_rest_of_line(struct src_iter *it)
{
	const char *s = it->current;
	const char *const e = it->end;
	while (src_iter_next_(&s, e)) {
#ifdef GTPARSER_FLAT_MEMORY_MODEL
		src_iter_check_(&it->line, &it->back_column, s, GTPARSER_TAB_SIZE(it));
#else
		src_iter_check_(&it->line, &it->line_ptr, &it->back_column, s, GTPARSER_TAB_SIZE(it));
#endif
		if ('\n' == src_iter_current_char_(s)) {
			src_iter_step_(&s);
			break;
		}
	}
	it->current = s; /* it points to char after '\n', may be to eof */
}

/* it points to unchecked char or to eof */
GTPARSER_EXPORTS char gt_read_non_space_skip_comments(struct src_iter *it, char comment)
{
	while (!src_iter_eof(it)) {
		char c = src_iter_current_char(it);
		if (comment == c) {
			src_iter_skip_comment(it);
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
GTPARSER_EXPORTS char gt_read_non_space_stop_eol(struct src_iter *it)
{
	while (!src_iter_eof(it)) {
		char c = src_iter_current_char(it);
		if ('\n' == c || !is_space(c))
			return c;
		src_iter_check_tab(it);
		src_iter_step(it);
	}
	return '\0'; /* failed to read non-space, it points to eof */
}
