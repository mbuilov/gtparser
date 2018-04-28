#ifndef PARSER_BASE_H_INCLUDED
#define PARSER_BASE_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2018 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* parser_base.h */

#include "gtparser/gtparser.h"
#include "gtparser/parser_common.h"

#ifdef __cplusplus
extern "C" {
#endif

struct src_iter {
	const char *current;
	const char *end;
#ifndef GTPARSER_FLAT_MEMORY_MODEL
	const char *line_ptr;
#endif
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
	inline void skip_comment();
	inline char read_non_space_skip_comments(char comment/*#*/);
	inline char read_non_space_stop_eol();
#endif /* __cplusplus */
};

static inline struct src_iter *src_iter_init_(struct src_iter *it, const char *input)
{
	it->current = input;
	it->end = input;
#ifdef GTPARSER_FLAT_MEMORY_MODEL
	src_iter_get_back_column_(input, &it->back_column);
#else
	src_iter_get_back_column_(input, &it->line_ptr, &it->back_column);
#endif
	it->line = 1;
	return it;
}

/* allow 64-bit size type */
#define src_iter_init(it, input, size) ((void)(src_iter_init_(it, input)->end += (size)))

/* input:  'it' points to checked char */
/* output: 'it' points to unchecked char, may be to 'eof' */
static inline void src_iter_step(struct src_iter *it)
{
	src_iter_step_(&it->current);
}

/* returns non-zero if 'it' points to 'eof' */
static inline int src_iter_eof_(const char *current, const char *end)
{
	return current == end;
}

/* returns non-zero if 'it' points to 'eof' */
static inline int src_iter_eof(const struct src_iter *it)
{
	return src_iter_eof_(it->current, it->end);
}

/* input:  'it' points to checked char */
/* output: 'it' points to unchecked char, may be to 'eof' */
/* returns zero if 'it' points to 'eof' */
static inline int src_iter_next_(const char **current, const char *end)
{
	src_iter_step_(current);
	return !src_iter_eof_(*current, end);
}

/* input:  'it' points to checked char */
/* output: 'it' points to unchecked char, may be to 'eof' */
/* returns zero if 'it' points to 'eof' */
static inline int src_iter_next(struct src_iter *it)
{
	return src_iter_next_(&it->current, it->end);
}

static inline void src_iter_process_tab(struct src_iter *it)
{
#ifdef GTPARSER_FLAT_MEMORY_MODEL
	src_iter_process_tab_(&it->back_column, it->current, GTPARSER_TAB_SIZE(it));
#else
	src_iter_process_tab_(it->line_ptr, &it->back_column, it->current, GTPARSER_TAB_SIZE(it));
#endif
}

static inline void src_iter_check_tab(struct src_iter *it)
{
#ifdef GTPARSER_FLAT_MEMORY_MODEL
	src_iter_check_tab_(&it->back_column, it->current, GTPARSER_TAB_SIZE(it));
#else
	src_iter_check_tab_(it->line_ptr, &it->back_column, it->current, GTPARSER_TAB_SIZE(it));
#endif
}

static inline void src_iter_inc_line(struct src_iter *it)
{
#ifdef GTPARSER_FLAT_MEMORY_MODEL
	src_iter_inc_line_(&it->line, &it->back_column, it->current);
#else
	src_iter_inc_line_(&it->line, &it->line_ptr, &it->back_column, it->current);
#endif
}

/* check current char */
static inline void src_iter_check(struct src_iter *it)
{
#ifdef GTPARSER_FLAT_MEMORY_MODEL
	src_iter_check_(&it->line, &it->back_column, it->current, GTPARSER_TAB_SIZE(it));
#else
	src_iter_check_(&it->line, &it->line_ptr, &it->back_column, it->current, GTPARSER_TAB_SIZE(it));
#endif
}

/* get current char the 'it' points to ('it' must not point to 'eof') */
static inline char src_iter_current_char(const struct src_iter *it)
{
	return src_iter_current_char_(it->current);
}

/* get current char the 'it' points to, '\0' if 'it' points to 'eof' */
static inline char src_iter_char_or_eof_(const char *current, const char *end)
{
	return src_iter_eof_(current, end) ? '\0' : *current;
}

/* get current char the 'it' points to, '\0' if 'it' points to 'eof' */
static inline char src_iter_char_or_eof(const struct src_iter *it)
{
	return src_iter_char_or_eof_(it->current, it->end);
}

/* get column from start of the line */
static inline unsigned src_iter_get_column(const struct src_iter *it)
{
#ifdef GTPARSER_FLAT_MEMORY_MODEL
	return src_iter_get_column_(it->current, it->back_column);
#else
	return src_iter_get_column_(it->current, it->line_ptr, it->back_column);
#endif
}

static inline void src_iter_get_pos(const struct src_iter *it, struct src_pos *pos/*out*/)
{
#ifdef GTPARSER_FLAT_MEMORY_MODEL
	src_iter_get_pos_(it->line, it->current, it->back_column, pos);
#else
	src_iter_get_pos_(it->line, it->current, it->line_ptr, it->back_column, pos);
#endif
}

static inline struct src_pos src_iter_return_pos(const struct src_iter *it)
{
#ifdef GTPARSER_FLAT_MEMORY_MODEL
	return src_iter_return_pos_(it->line, it->current, it->back_column);
#else
	return src_iter_return_pos_(it->line, it->current, it->line_ptr, it->back_column);
#endif
}

static inline void src_iter_save_pos(const struct src_iter *it, struct src_save_pos *save_pos/*out*/)
{
#ifdef GTPARSER_FLAT_MEMORY_MODEL
	src_iter_save_pos_(it->line, it->current, it->back_column, save_pos);
#else
	src_iter_save_pos_(it->line, it->current, it->line_ptr, it->back_column, save_pos);
#endif
}

static inline struct src_save_pos src_iter_return_save_pos(const struct src_iter *it)
{
#ifdef GTPARSER_FLAT_MEMORY_MODEL
	return src_iter_return_save_pos_(it->line, it->current, it->back_column);
#else
	return src_iter_return_save_pos_(it->line, it->current, it->line_ptr, it->back_column);
#endif
}

static inline void src_iter_restore_pos(struct src_iter *it, const struct src_save_pos *save_pos/*in*/)
{
#ifdef GTPARSER_FLAT_MEMORY_MODEL
	src_iter_restore_pos_(&it->line, &it->current, &it->back_column, save_pos);
#else
	src_iter_restore_pos_(&it->line, &it->current, &it->line_ptr, &it->back_column, save_pos);
#endif
}

/* input:  'it' points to checked char (like comment beginning) */
/* output: 'it' points to next unchecked char after new line, may be to 'eof' */
GTPARSER_EXPORTS void gt_skip_rest_of_line(struct src_iter *it);
#define src_iter_skip_comment(it) gt_skip_rest_of_line(it)

/* input:  'it' points to unchecked char or to 'eof' */
/* output: if returns != '\0', 'it' points to non-space and non-'eof' */
/* returns current char or '\0' on 'eof' */
GTPARSER_EXPORTS char gt_read_non_space_skip_comments(struct src_iter *it, char comment/*'#'*/);
#define src_iter_read_non_space_skip_comments(it, comment) gt_read_non_space_skip_comments(it, comment)

/* input:  'it' points to unchecked char or to eof */
/* output: if returns != '\0', 'it' points to '\n' or to non-space and non-'eof' */
/* returns current char or '\0' on 'eof' */
GTPARSER_EXPORTS char gt_read_non_space_stop_eol(struct src_iter *it);
#define src_iter_read_non_space_stop_eol(it) gt_read_non_space_stop_eol(it)

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

inline void src_iter::save_pos(struct src_save_pos &save_pos/*out*/) const
{
	src_iter_save_pos(this, &save_pos/*out*/);
}

inline struct src_save_pos src_iter::save_pos() const
{
	return src_iter_return_save_pos(this);
}

inline void src_iter::restore_pos(const struct src_save_pos &save_pos)
{
	src_iter_restore_pos(this, &save_pos/*in*/);
}

inline void src_iter::skip_comment()
{
	src_iter_skip_comment(this);
}

inline char src_iter::read_non_space_skip_comments(char comment/*#*/)
{
	return src_iter_read_non_space_skip_comments(this, comment);
}

inline char src_iter::read_non_space_stop_eol()
{
	return src_iter_read_non_space_stop_eol(this);
}

#endif /* __cplusplus */

#ifdef __cplusplus
}
#endif

#endif /* PARSER_BASE_H_INCLUDED */
