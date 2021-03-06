#ifndef PARSER_BASE_H_INCLUDED
#define PARSER_BASE_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2017 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* parser_base.h */

#include "gtparser/gtparser.h"

#ifndef GTPARSER_TAB_SIZE
#define GTPARSER_TAB_SIZE 4 /* needed to correctly specify parsing error column in error messages */
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

struct src_iter {
	const char *current;
	const char *end;
	unsigned back_column;
	unsigned line;
#ifdef __cplusplus
	inline void init(const char *input, size_t size);
	inline void step();
	inline bool eof() const;
	inline bool next();
	inline void process_tab();
	inline void check_tab();
	inline void inc_line();
	inline void check();
	inline char current_char() const;
	inline char char_or_eof() const;
	inline unsigned get_column() const;
	inline void get_pos(struct src_pos &pos/*out*/) const;
	inline struct src_pos get_pos() const;
	inline void save_pos(struct src_save_pos &save_pos/*out*/) const;
	inline struct src_save_pos save_pos() const;
	inline void restore_pos(const struct src_save_pos &save_pos);
#endif /* __cplusplus */
};

static inline struct src_iter *_src_iter_init(struct src_iter *it, const char *input)
{
	it->current = input;
	it->end = input;
	it->back_column = (unsigned)((unsigned long long)(input - (const char*)1) & ~0u);
	it->line = 1;
	return it;
}

/* allow 64-bit size type */
#define src_iter_init(it, input, size) ((void)(_src_iter_init(it, input)->end += (size)))

/* input:  it points to checked char */
/* output: it points to unchecked char, may be to eof */
static inline void _src_iter_step(const char **current)
{
	(*current)++;
}

/* input:  it points to checked char */
/* output: it points to unchecked char, may be to eof */
static inline void src_iter_step(struct src_iter *it)
{
	_src_iter_step(&it->current);
}

/* returns non-zero if it points to eof */
static inline int _src_iter_eof(const char *current, const char *end)
{
	return current == end;
}

/* returns non-zero if it points to eof */
static inline int src_iter_eof(const struct src_iter *it)
{
	return _src_iter_eof(it->current, it->end);
}

/* input:  it points to checked char */
/* output: it points to unchecked char, may be to eof */
/* returns zero if it points to eof */
static inline int _src_iter_next(const char **current, const char *end)
{
	_src_iter_step(current);
	return !_src_iter_eof(*current, end);
}

/* input:  it points to checked char */
/* output: it points to unchecked char, may be to eof */
/* returns zero if it points to eof */
static inline int src_iter_next(struct src_iter *it)
{
	return _src_iter_next(&it->current, it->end);
}

static inline void _src_iter_process_tab(unsigned *back_column, const char *current, unsigned tab_size)
{
	unsigned d = (unsigned)((unsigned long long)(current - (const char*)0) & ~0u);
	d = ~0u - (d - *back_column - 1); /* (*back_column - d) */
	(*back_column) -= d % tab_size;
}

static inline void src_iter_process_tab(struct src_iter *it)
{
	_src_iter_process_tab(&it->back_column, it->current, GTPARSER_TAB_SIZE);
}

static inline void _src_iter_check_tab(unsigned *back_column, const char *current, unsigned tab_size)
{
	if ('\t' == *current)
		_src_iter_process_tab(back_column, current, tab_size);
}

static inline void src_iter_check_tab(struct src_iter *it)
{
	_src_iter_check_tab(&it->back_column, it->current, GTPARSER_TAB_SIZE);
}

static inline void _src_iter_inc_line(unsigned *line, unsigned *back_column, const char *current)
{
	(*line)++;
	*back_column = (unsigned)((unsigned long long)(current - (const char*)0) & ~0u);
}

static inline void src_iter_inc_line(struct src_iter *it)
{
	_src_iter_inc_line(&it->line, &it->back_column, it->current);
}

/* check current char */
static inline void _src_iter_check(unsigned *line, unsigned *back_column, const char *current, unsigned tab_size)
{
	if ('\n' == *current)
		_src_iter_inc_line(line, back_column, current);
	else
		_src_iter_check_tab(back_column, current, tab_size);
}

/* check current char */
static inline void src_iter_check(struct src_iter *it)
{
	_src_iter_check(&it->line, &it->back_column, it->current, GTPARSER_TAB_SIZE);
}

/* get current char the it points to (it must not point to eof) */
static inline char _src_iter_current_char(const char *current)
{
	return *current;
}

/* get current char the it points to (it must not point to eof) */
static inline char src_iter_current_char(const struct src_iter *it)
{
	return _src_iter_current_char(it->current);
}

/* get current char the it points to, '\0' if it points to eof */
static inline char _src_iter_char_or_eof(const char *current, const char *end)
{
	return _src_iter_eof(current, end) ? '\0' : *current;
}

/* get current char the it points to, '\0' if it points to eof */
static inline char src_iter_char_or_eof(const struct src_iter *it)
{
	return _src_iter_char_or_eof(it->current, it->end);
}

/* get column from start of the line */
static inline unsigned _src_iter_get_column(const char *current, unsigned back_column)
{
	return (unsigned)((unsigned long long)(current - (const char*)0) & ~0u) - back_column;
}

/* get column from start of the line */
static inline unsigned src_iter_get_column(const struct src_iter *it)
{
	return _src_iter_get_column(it->current, it->back_column);
}

static inline void _src_iter_get_pos(unsigned line, const char *current, unsigned back_column, struct src_pos *pos/*out*/)
{
	pos->line = line;
	pos->column = _src_iter_get_column(current, back_column);
}

static inline void src_iter_get_pos(const struct src_iter *it, struct src_pos *pos/*out*/)
{
	_src_iter_get_pos(it->line, it->current, it->back_column, pos);
}

static inline struct src_pos _src_iter_return_pos(unsigned line, const char *current, unsigned back_column)
{
	struct src_pos pos;
	_src_iter_get_pos(line, current, back_column, &pos);
	return pos;
}

static inline struct src_pos src_iter_return_pos(const struct src_iter *it)
{
	return _src_iter_return_pos(it->line, it->current, it->back_column);
}

static inline void _src_iter_save_pos(unsigned line, const char *current, unsigned back_column, struct src_save_pos *save_pos/*out*/)
{
	save_pos->line = line;
	save_pos->current = current;
	save_pos->back_column = back_column;
}

static inline void src_iter_save_pos(const struct src_iter *it, struct src_save_pos *save_pos/*out*/)
{
	_src_iter_save_pos(it->line, it->current, it->back_column, save_pos);
}

static inline struct src_save_pos _src_iter_return_save_pos(unsigned line, const char *current, unsigned back_column)
{
	struct src_save_pos save_pos;
	_src_iter_save_pos(line, current, back_column, &save_pos);
	return save_pos;
}

static inline struct src_save_pos src_iter_return_save_pos(const struct src_iter *it)
{
	return _src_iter_return_save_pos(it->line, it->current, it->back_column);
}

static inline void _src_iter_restore_pos(unsigned *line, const char **current,
	unsigned *back_column, const struct src_save_pos *save_pos/*in*/)
{
	*line = save_pos->line;
	*current = save_pos->current;
	*back_column = save_pos->back_column;
}

static inline void src_iter_restore_pos(struct src_iter *it, const struct src_save_pos *save_pos/*in*/)
{
	_src_iter_restore_pos(&it->line, &it->current, &it->back_column, save_pos);
}

static inline int is_space(char c)
{
	return (unsigned char)c <= ' ';
}

/* input:  it points to checked char (like comment beginning) */
/* output: it points to next unchecked char after new line, may be to eof */
GTPARSER_EXPORTS void gt_skip_rest_of_line(struct src_iter *it);

/* input:  it points to comment beginning (like '#') */
/* output: it points to next unchecked char after new line, may be to eof */
static inline void _skip_comment(struct src_iter *it)
{
	gt_skip_rest_of_line(it);
}

/* input:  it points to unchecked char or to eof */
/* output: if returns != '\0', it points to non-space and non-eof */
/* returns current char or '\0' on eof */
GTPARSER_EXPORTS char read_non_space_skip_comments(struct src_iter *it, char comment/*'#'*/);

/* input:  it points to unchecked char or to eof */
/* output: if returns != '\0', it points to '\n' or to non-space and non-eof */
/* returns current char or '\0' on eof */
GTPARSER_EXPORTS char read_non_space_stop_eol(struct src_iter *it);

#ifdef __cplusplus

inline void src_iter::init(const char *input, size_t size)
{
	src_iter_init(this, input, size);
}

inline void src_iter::step()
{
	src_iter_step(this);
}

inline bool src_iter::eof() const
{
	return 0 != src_iter_eof(this);
}

inline bool src_iter::next()
{
	return 0 != src_iter_next(this);
}

inline void src_iter::process_tab()
{
	src_iter_process_tab(this);
}

inline void src_iter::check_tab()
{
	src_iter_check_tab(this);
}

inline void src_iter::inc_line()
{
	src_iter_inc_line(this);
}

inline void src_iter::check()
{
	src_iter_check(this);
}

inline char src_iter::current_char() const
{
	return src_iter_current_char(this);
}

inline char src_iter::char_or_eof() const
{
	return src_iter_char_or_eof(this);
}

inline unsigned src_iter::get_column() const
{
	return src_iter_get_column(this);
}

inline void src_iter::get_pos(struct src_pos &pos/*out*/) const
{
	src_iter_get_pos(this, &pos/*out*/);
}

inline struct src_pos src_iter::get_pos() const
{
	return src_iter_return_pos(this);
}

inline void src_iter::save_pos(struct src_save_pos &_save_pos/*out*/) const
{
	src_iter_save_pos(this, &_save_pos/*out*/);
}

inline struct src_save_pos src_iter::save_pos() const
{
	return src_iter_return_save_pos(this);
}

inline void src_iter::restore_pos(const struct src_save_pos &_save_pos)
{
	src_iter_restore_pos(this, &_save_pos/*in*/);
}

#endif /* __cplusplus */

#ifdef __cplusplus
}
#endif

#endif /* PARSER_BASE_H_INCLUDED */
