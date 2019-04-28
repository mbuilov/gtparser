#ifndef CHAR_FUNC_H_INCLUDED
#define CHAR_FUNC_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2019 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* char_func.h */

#ifdef __cplusplus
extern "C" {
#endif

/* check basic execution character set: values of digits and latin letters must increase monotonically */

typedef int gt_bad_digits_[1-2*(
	'0' + 1 != '1' ||
	'1' + 1 != '2' ||
	'2' + 1 != '3' ||
	'3' + 1 != '4' ||
	'4' + 1 != '5' ||
	'5' + 1 != '6' ||
	'6' + 1 != '7' ||
	'7' + 1 != '8' ||
	'8' + 1 != '9')];

typedef int gt_bad_latin_[1-2*(
	'a' + 1 != 'b' ||
	'b' + 1 != 'c' ||
	'c' + 1 != 'd' ||
	'd' + 1 != 'e' ||
	'e' + 1 != 'f' ||
	'f' + 1 != 'g' ||
	'g' + 1 != 'h' ||
	'h' + 1 != 'i' ||
	'i' + 1 != 'j' ||
	'j' + 1 != 'k' ||
	'k' + 1 != 'l' ||
	'l' + 1 != 'm' ||
	'm' + 1 != 'n' ||
	'n' + 1 != 'o' ||
	'o' + 1 != 'p' ||
	'p' + 1 != 'q' ||
	'q' + 1 != 'r' ||
	'r' + 1 != 's' ||
	's' + 1 != 't' ||
	't' + 1 != 'u' ||
	'u' + 1 != 'v' ||
	'v' + 1 != 'w' ||
	'w' + 1 != 'x' ||
	'x' + 1 != 'y' ||
	'y' + 1 != 'z')];

typedef int gt_bad_LATIN_[1-2*(
	'A' + 1 != 'B' ||
	'B' + 1 != 'C' ||
	'C' + 1 != 'D' ||
	'D' + 1 != 'E' ||
	'E' + 1 != 'F' ||
	'F' + 1 != 'G' ||
	'G' + 1 != 'H' ||
	'H' + 1 != 'I' ||
	'I' + 1 != 'J' ||
	'J' + 1 != 'K' ||
	'K' + 1 != 'L' ||
	'L' + 1 != 'M' ||
	'M' + 1 != 'N' ||
	'N' + 1 != 'O' ||
	'O' + 1 != 'P' ||
	'P' + 1 != 'Q' ||
	'Q' + 1 != 'R' ||
	'R' + 1 != 'S' ||
	'S' + 1 != 'T' ||
	'T' + 1 != 'U' ||
	'U' + 1 != 'V' ||
	'V' + 1 != 'W' ||
	'W' + 1 != 'X' ||
	'X' + 1 != 'Y' ||
	'Y' + 1 != 'Z')];

/* needed for is_first_name_() and hex_char_value_() */
typedef int gt_bad_a_A_diff_[1-2*('a' - 'A' != 32 || '_' != 95)];

static inline int is_latin_letter_(const char c)
{
	unsigned x = (unsigned char)c;
#ifdef UBSAN_UNSIGNED_OVERFLOW
	if (x < 'A')
		x += ((unsigned)-1 - 'A') + 1u;
	else
#endif
		x -= 'A';
	return (x & ~32u) <= 'Z' - 'A';
}

static inline int is_latin_upper_letter_(const char c)
{
	unsigned x = (unsigned char)c;
#ifdef UBSAN_UNSIGNED_OVERFLOW
	if (x < 'A')
		x += ((unsigned)-1 - 'A') + 1u;
	else
#endif
		x -= 'A';
	return x <= 'Z' - 'A';
}

static inline int is_latin_lower_letter_(const char c)
{
	unsigned x = (unsigned char)c;
#ifdef UBSAN_UNSIGNED_OVERFLOW
	if (x < 'a')
		x += ((unsigned)-1 - 'a') + 1u;
	else
#endif
		x -= 'a';
	return x <= 'z' - 'a';
}

/* convert [A-Z] -> [a-z] */
static inline char latin_letter_to_lower(const char c)
{
#ifdef ASSERT
	ASSERT(is_latin_letter_(c));
#endif
	{
		const unsigned x = (unsigned char)c;
		return (char)(unsigned char)(x | 32u);
	}
}

/* convert [a-z] -> [A-Z] */
static inline char latin_letter_to_upper(const char c)
{
#ifdef ASSERT
	ASSERT(is_latin_letter_(c));
#endif
	{
		const unsigned x = (unsigned char)c;
		return (char)(unsigned char)(x & ~32u);
	}
}

static inline char latin_to_lower(const char c)
{
	const unsigned x = 32u | (unsigned char)c;
	return ('a' <= x && x <= 'z') ? (char)(unsigned char)x : c;
}

static inline char latin_to_upper(const char c)
{
	const unsigned x = ~32u & (unsigned char)c;
	return ('A' <= x && x <= 'Z') ? (char)(unsigned char)x : c;
}

/* name must be started with a latin letter or '_' */
static inline int is_first_name_(const char c)
{
	return is_latin_letter_(c) || c == '_';
}

/* returns decimal digit value or >9 if non-decimal digit char */
static inline unsigned digit_value(const char c)
{
	unsigned x = (unsigned char)c;
#ifdef UBSAN_UNSIGNED_OVERFLOW
	if (x < '0')
		x += ((unsigned)-1 - '0') + 1u;
	else
#endif
		x -= '0';
	return x;
}

/* returns non-zero if c is a decimal digit */
static inline int is_digit(const char c)
{
	return digit_value(c) <= 9;
}

/* name may be continued by a letter, digit or '_' */
static inline int is_next_name_(const char c)
{
	return is_first_name_(c) || is_digit(c);
}

/* needed for hex_char_value_() */
typedef int gt_bad_A_0_diff_[1-2*('A' - '0' <= 0)];

/* returns hex char value or >15 if non-hex char */
static inline unsigned hex_char_value_(const char c)
{
	unsigned x = digit_value(c);
	if (x > 9) {
		const unsigned d = 'A' - '0';
#ifdef UBSAN_UNSIGNED_OVERFLOW
		if (x < d)
			x += ((unsigned)-1 - d) + 1u;
		else
#endif
			x -= d;
		x &= ~32u;
		x += 10; /* cannot overflow because 6-th bit was reset by the previous &= ~32u */
	}
	return x;
}

#ifdef __cplusplus
}
#endif

#endif /* CHAR_FUNC_H_INCLUDED */
