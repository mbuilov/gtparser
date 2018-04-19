#ifndef PARSER_COMMON_H_INCLUDED
#define PARSER_COMMON_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2018 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* parser_common.h */

/* GTPARSER_TAB_SIZE may be defined as a function, e.g.:
extern unsigned source_tab_size(const struct src_iter *iter);
#define GTPARSER_TAB_SIZE(iter) source_tab_size(iter)
*/
#ifndef GTPARSER_TAB_SIZE
#define GTPARSER_TAB_SIZE(iter) 4 /* needed to correctly specify parsing error column in error messages */
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct src_pos {
	unsigned column;
	unsigned line;
};

struct src_save_pos {
	const char *current;
	unsigned back_column;
	unsigned line;
};

static inline int is_space(char c)
{
	return (unsigned char)c <= ' ';
}

/* input:  'it' points to checked char */
/* output: 'it' points to unchecked char, may be to 'eof' */
static inline void src_iter_step_(const char **current)
{
	(*current)++;
}

static inline void src_iter_process_tab_(unsigned *back_column, const char *current, unsigned tab_size)
{
	unsigned d = (unsigned)((unsigned long long)(current - (const char*)0) & ~0u);
	d = ~0u - (d - *back_column - 1); /* (*back_column - d) */
	(*back_column) -= d % tab_size;
}

static inline void src_iter_check_tab_(unsigned *back_column, const char *current, unsigned tab_size)
{
	if ('\t' == *current)
		src_iter_process_tab_(back_column, current, tab_size);
}

static inline void src_iter_inc_line_(unsigned *line, unsigned *back_column, const char *current)
{
	(*line)++;
	*back_column = (unsigned)((unsigned long long)(current - (const char*)0) & ~0u);
}

/* check current char */
static inline void src_iter_check_(unsigned *line, unsigned *back_column, const char *current, unsigned tab_size)
{
	if ('\n' == *current)
		src_iter_inc_line_(line, back_column, current);
	else
		src_iter_check_tab_(back_column, current, tab_size);
}

/* get current char the 'it' points to ('it' must not point to 'eof') */
static inline char src_iter_current_char_(const char *current)
{
	return *current;
}

/* get column from start of the line */
static inline unsigned src_iter_get_column_(const char *current, unsigned back_column)
{
	return (unsigned)((unsigned long long)(current - (const char*)0) & ~0u) - back_column;
}

static inline void src_iter_get_pos_(unsigned line, const char *current, unsigned back_column, struct src_pos *pos/*out*/)
{
	pos->line = line;
	pos->column = src_iter_get_column_(current, back_column);
}

static inline struct src_pos src_iter_return_pos_(unsigned line, const char *current, unsigned back_column)
{
	struct src_pos pos;
	src_iter_get_pos_(line, current, back_column, &pos);
	return pos;
}

static inline void src_iter_save_pos_(unsigned line, const char *current, unsigned back_column, struct src_save_pos *save_pos/*out*/)
{
	save_pos->line = line;
	save_pos->current = current;
	save_pos->back_column = back_column;
}

static inline struct src_save_pos src_iter_return_save_pos_(unsigned line, const char *current, unsigned back_column)
{
	struct src_save_pos save_pos;
	src_iter_save_pos_(line, current, back_column, &save_pos);
	return save_pos;
}

static inline void src_iter_restore_pos_(unsigned *line, const char **current,
	unsigned *back_column, const struct src_save_pos *save_pos/*in*/)
{
	*line = save_pos->line;
	*current = save_pos->current;
	*back_column = save_pos->back_column;
}

#ifdef __cplusplus
}
#endif

#endif /* PARSER_COMMON_H_INCLUDED */
