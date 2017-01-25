#ifndef CHAR_FUNC_H_INCLUDED
#define CHAR_FUNC_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2017 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* char_func.h */

#ifdef __cplusplus
extern "C" {
#endif

/* needed for _is_first_name() and _hex_char_value() */
typedef int _bad_a_A_diff_[1-2*('a' - 'A' != 32 || '_' != 95)];

/* name must be started with a letter or '_' */
static inline int _is_first_name(char c)
{
	unsigned x = (unsigned char)c;
#ifdef _DEBUG
	if (x < 'A')
		x += (~0u - 'A') + 1u;
	else
#endif
		x -= 'A';
	return (x & ~32u) <= 'Z' - 'A' || c == '_';
}

/* needed for digit_value() */
typedef int _bad_9_0_diff_[1-2*('9' - '0' != 9)];

/* returns decimal digit value or >9 if non-decimal digit char */
static inline unsigned digit_value(char c)
{
	unsigned x = (unsigned char)c;
#ifdef _DEBUG
	if (x < '0')
		x += (~0u - '0') + 1u;
	else
#endif
		x -= '0';
	return x;
}

static inline int is_digit(char c)
{
	return digit_value(c) <= 9;
}

static inline int _is_next_name(char c)
{
	return _is_first_name(c) || is_digit(c);
}

/* needed for _hex_char_value() */
typedef int _bad_A_0_diff_[1-2*('A' - '0' <= 0)];

/* returns hex char value or >15 if non-hex char */
static inline unsigned _hex_char_value(char c)
{
	unsigned x = digit_value(c);
	if (x > 9) {
		const unsigned d = 'A' - '0';
#ifdef _DEBUG
		if (x < d)
			x += (~0u - d) + 1u;
		else
#endif
			x -= d;
		x &= (~0u >> 1) & ~32u; /* also clear high-order bit to not overflow in next line */
		x += 10;
	}
	return x;
}

#ifdef __cplusplus
}
#endif

#endif /* CHAR_FUNC_H_INCLUDED */
