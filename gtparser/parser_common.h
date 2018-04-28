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
#ifndef GTPARSER_FLAT_MEMORY_MODEL
	const char *line_ptr;
#endif
	unsigned back_column;
	unsigned line;
};

static inline int is_space(char c)
{
	return (unsigned char)c <= ' ';
}

/* get initial value of 'back_column' */
#ifdef GTPARSER_FLAT_MEMORY_MODEL
static inline void src_iter_get_back_column_(
	const char *input/*in*/,
	unsigned *back_column/*out*/)
{
	/* compute difference with a pointer outside of allocated region, this is UB according to C standard... */
	*back_column = (unsigned)((unsigned long long)(input - (const char*)1) & ~0u);
}
#else
static inline void src_iter_get_back_column_(
	const char *input/*in*/,
	const char **line_ptr/*out*/,
	unsigned *back_column/*out*/)
{
	*line_ptr = input;
	*back_column = ~0u;
}
#endif

/* input:  'it' points to checked char */
/* output: 'it' points to unchecked char, may be to 'eof' */
static inline void src_iter_step_(const char **current/*in,out*/)
{
	(*current)++;
}

#ifdef GTPARSER_FLAT_MEMORY_MODEL
static inline void src_iter_process_tab_(
	unsigned *back_column/*in,out*/,
	const char *current/*in*/,
	unsigned tab_size)
{
	/* compute difference with a pointer outside of allocated region, this is UB according to C standard... */
	unsigned d = (unsigned)((unsigned long long)(current - (const char*)0) & ~0u);
	(*back_column) -= ((*back_column) - d) % tab_size;
}
#else
static inline void src_iter_process_tab_(
	const char *line_ptr/*in*/,
	unsigned *back_column/*in,out*/,
	const char *current/*in*/,
	unsigned tab_size)
{
	unsigned d = (unsigned)((unsigned long long)(current - line_ptr) & ~0u);
	(*back_column) -= ((*back_column) - d) % tab_size;
}
#endif

#ifdef GTPARSER_FLAT_MEMORY_MODEL
static inline void src_iter_check_tab_(
	unsigned *back_column/*in,out*/,
	const char *current/*in*/,
	unsigned tab_size)
{
	if ('\t' == *current)
		src_iter_process_tab_(back_column, current, tab_size);
}
#else
static inline void src_iter_check_tab_(
	const char *line_ptr/*in*/,
	unsigned *back_column/*in,out*/,
	const char *current/*in*/,
	unsigned tab_size)
{
	if ('\t' == *current)
		src_iter_process_tab_(line_ptr, back_column, current, tab_size);
}
#endif

#ifdef GTPARSER_FLAT_MEMORY_MODEL
static inline void src_iter_inc_line_(
	unsigned *line/*in,out*/,
	unsigned *back_column/*out*/,
	const char *current/*in*/)
{
	(*line)++;
	*back_column = (unsigned)((unsigned long long)(current - (const char*)0) & ~0u);
}
#else
static inline void src_iter_inc_line_(
	unsigned *line/*in,out*/,
	const char **line_ptr/*out*/,
	unsigned *back_column/*out*/,
	const char *current/*in*/)
{
	(*line)++;
	*line_ptr = current;
	*back_column = 0;
}
#endif

/* check current char */
#ifdef GTPARSER_FLAT_MEMORY_MODEL
static inline void src_iter_check_(
	unsigned *line/*in,out*/,
	unsigned *back_column/*in,out*/,
	const char *current/*in*/,
	unsigned tab_size)
{
	if ('\n' == *current)
		src_iter_inc_line_(line, back_column, current);
	else
		src_iter_check_tab_(back_column, current, tab_size);
}
#else
static inline void src_iter_check_(
	unsigned *line/*in,out*/,
	const char **line_ptr/*in,out*/,
	unsigned *back_column/*in,out*/,
	const char *current/*in*/,
	unsigned tab_size)
{
	if ('\n' == *current)
		src_iter_inc_line_(line, line_ptr, back_column, current);
	else
		src_iter_check_tab_(*line_ptr, back_column, current, tab_size);
}
#endif

/* get current char the 'it' points to ('it' must not point to 'eof') */
static inline char src_iter_current_char_(const char *current)
{
	return *current;
}

/* get column from start of the line */
#ifdef GTPARSER_FLAT_MEMORY_MODEL
static inline unsigned src_iter_get_column_(
	const char *current, unsigned back_column)
{
	/* compute difference with a pointer outside of allocated region, this is UB according to C standard... */
	return (unsigned)((unsigned long long)(current - (const char*)0) & ~0u) - back_column;
}
#else
static inline unsigned src_iter_get_column_(
	const char *current, const char *line_ptr, unsigned back_column)
{
	return (unsigned)((unsigned long long)(current - line_ptr) & ~0u) - back_column;
}
#endif

#ifdef GTPARSER_FLAT_MEMORY_MODEL
static inline void src_iter_get_pos_(unsigned line, const char *current,
	unsigned back_column, struct src_pos *pos/*out*/)
{
	pos->line = line;
	pos->column = src_iter_get_column_(current, back_column);
}
#else
static inline void src_iter_get_pos_(unsigned line, const char *current,
	const char *line_ptr, unsigned back_column, struct src_pos *pos/*out*/)
{
	pos->line = line;
	pos->column = src_iter_get_column_(current, line_ptr, back_column);
}
#endif

#ifdef GTPARSER_FLAT_MEMORY_MODEL
static inline struct src_pos src_iter_return_pos_(
	unsigned line, const char *current, unsigned back_column)
{
	struct src_pos pos;
	src_iter_get_pos_(line, current, back_column, &pos);
	return pos;
}
#else
static inline struct src_pos src_iter_return_pos_(
	unsigned line, const char *current, const char *line_ptr, unsigned back_column)
{
	struct src_pos pos;
	src_iter_get_pos_(line, current, line_ptr, back_column, &pos);
	return pos;
}
#endif

#ifdef GTPARSER_FLAT_MEMORY_MODEL
static inline void src_iter_save_pos_(unsigned line, const char *current,
	unsigned back_column, struct src_save_pos *save_pos/*out*/)
{
	save_pos->line = line;
	save_pos->current = current;
	save_pos->back_column = back_column;
}
#else
static inline void src_iter_save_pos_(unsigned line, const char *current,
	const char *line_ptr, unsigned back_column, struct src_save_pos *save_pos/*out*/)
{
	save_pos->line = line;
	save_pos->current = current;
	save_pos->line_ptr = line_ptr;
	save_pos->back_column = back_column;
}
#endif

#ifdef GTPARSER_FLAT_MEMORY_MODEL
static inline struct src_save_pos src_iter_return_save_pos_(
	unsigned line, const char *current, unsigned back_column)
{
	struct src_save_pos save_pos;
	src_iter_save_pos_(line, current, back_column, &save_pos);
	return save_pos;
}
#else
static inline struct src_save_pos src_iter_return_save_pos_(
	unsigned line, const char *current, const char *line_ptr, unsigned back_column)
{
	struct src_save_pos save_pos;
	src_iter_save_pos_(line, current, line_ptr, back_column, &save_pos);
	return save_pos;
}
#endif

#ifdef GTPARSER_FLAT_MEMORY_MODEL
static inline void src_iter_restore_pos_(unsigned *line/*out*/, const char **current/*out*/,
	unsigned *back_column/*out*/, const struct src_save_pos *save_pos/*in*/)
{
	*line = save_pos->line;
	*current = save_pos->current;
	*back_column = save_pos->back_column;
}
#else
static inline void src_iter_restore_pos_(unsigned *line/*out*/, const char **current/*out*/,
	const char **line_ptr/*out*/, unsigned *back_column/*out*/, const struct src_save_pos *save_pos/*in*/)
{
	*line = save_pos->line;
	*current = save_pos->current;
	*line_ptr = save_pos->line_ptr;
	*back_column = save_pos->back_column;
}
#endif

#ifdef __cplusplus
}
#endif

#endif /* PARSER_COMMON_H_INCLUDED */
