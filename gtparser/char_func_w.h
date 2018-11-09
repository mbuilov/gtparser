#ifndef CHAR_FUNC_W_H_INCLUDED
#define CHAR_FUNC_W_H_INCLUDED

/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2018 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* char_func_w.h */

#ifdef __cplusplus
extern "C" {
#endif

/* check basic execution character set: values of digits and latin letters must increase monotonically */

typedef int gt_bad_digits_w_[1-2*(
	L'0' + 1 != L'1' ||
	L'1' + 1 != L'2' ||
	L'2' + 1 != L'3' ||
	L'3' + 1 != L'4' ||
	L'4' + 1 != L'5' ||
	L'5' + 1 != L'6' ||
	L'6' + 1 != L'7' ||
	L'7' + 1 != L'8' ||
	L'8' + 1 != L'9')];

typedef int gt_bad_latin_w_[1-2*(
	L'a' + 1 != L'b' ||
	L'b' + 1 != L'c' ||
	L'c' + 1 != L'd' ||
	L'd' + 1 != L'e' ||
	L'e' + 1 != L'f' ||
	L'f' + 1 != L'g' ||
	L'g' + 1 != L'h' ||
	L'h' + 1 != L'i' ||
	L'i' + 1 != L'j' ||
	L'j' + 1 != L'k' ||
	L'k' + 1 != L'l' ||
	L'l' + 1 != L'm' ||
	L'm' + 1 != L'n' ||
	L'n' + 1 != L'o' ||
	L'o' + 1 != L'p' ||
	L'p' + 1 != L'q' ||
	L'q' + 1 != L'r' ||
	L'r' + 1 != L's' ||
	L's' + 1 != L't' ||
	L't' + 1 != L'u' ||
	L'u' + 1 != L'v' ||
	L'v' + 1 != L'w' ||
	L'w' + 1 != L'x' ||
	L'x' + 1 != L'y' ||
	L'y' + 1 != L'z')];

typedef int gt_bad_LATIN_w_[1-2*(
	L'A' + 1 != L'B' ||
	L'B' + 1 != L'C' ||
	L'C' + 1 != L'D' ||
	L'D' + 1 != L'E' ||
	L'E' + 1 != L'F' ||
	L'F' + 1 != L'G' ||
	L'G' + 1 != L'H' ||
	L'H' + 1 != L'I' ||
	L'I' + 1 != L'J' ||
	L'J' + 1 != L'K' ||
	L'K' + 1 != L'L' ||
	L'L' + 1 != L'M' ||
	L'M' + 1 != L'N' ||
	L'N' + 1 != L'O' ||
	L'O' + 1 != L'P' ||
	L'P' + 1 != L'Q' ||
	L'Q' + 1 != L'R' ||
	L'R' + 1 != L'S' ||
	L'S' + 1 != L'T' ||
	L'T' + 1 != L'U' ||
	L'U' + 1 != L'V' ||
	L'V' + 1 != L'W' ||
	L'W' + 1 != L'X' ||
	L'X' + 1 != L'Y' ||
	L'Y' + 1 != L'Z')];

/* check that wchar_t fits in unsigned int */
typedef int gt_too_wide_wchar_t_[1-2*(sizeof(unsigned) < sizeof(wchar_t))];

/* needed for is_first_name_w_() and hex_char_value_w_() */
typedef int gt_bad_a_A_diff_w_[1-2*(L'a' - L'A' != 32 || L'_' != 95)];

static inline int is_latin_letter_w_(wchar_t c)
{
	unsigned x = (unsigned)c;
#ifdef UBSAN_UNSIGNED_OVERFLOW
	if (x < L'A')
		x += ((unsigned)-1 - L'A') + 1u;
	else
#endif
		x -= L'A';
	return (x & ~32u) <= L'Z' - L'A';
}

static inline int is_latin_upper_letter_w_(wchar_t c)
{
	unsigned x = (unsigned)c;
#ifdef UBSAN_UNSIGNED_OVERFLOW
	if (x < L'A')
		x += ((unsigned)-1 - L'A') + 1u;
	else
#endif
		x -= L'A';
	return x <= L'Z' - L'A';
}

static inline int is_latin_lower_letter_w_(wchar_t c)
{
	unsigned x = (unsigned)c;
#ifdef UBSAN_UNSIGNED_OVERFLOW
	if (x < L'a')
		x += ((unsigned)-1 - L'a') + 1u;
	else
#endif
		x -= L'a';
	return x <= L'z' - L'a';
}

/* convert [A-Z] -> [a-z] */
static inline wchar_t latin_letter_to_lower_w(wchar_t c)
{
#ifdef ASSERT
	ASSERT(is_latin_letter_w_(c));
#endif
	{
		unsigned x = (unsigned)c;
		return (wchar_t)(x | 32u);
	}
}

/* convert [a-z] -> [A-Z] */
static inline wchar_t latin_letter_to_upper_w(wchar_t c)
{
#ifdef ASSERT
	ASSERT(is_latin_letter_w_(c));
#endif
	{
		unsigned x = (unsigned)c;
		return (wchar_t)(x & ~32u);
	}
}

static inline wchar_t latin_to_lower_w(wchar_t c)
{
	unsigned x = 32u | (unsigned)c;
	return L'a' <= x && x <= L'z' ? (wchar_t)x : c;
}

static inline wchar_t latin_to_upper_w(wchar_t c)
{
	unsigned x = ~32u & (unsigned)c;
	return L'A' <= x && x <= L'Z' ? (wchar_t)x : c;
}

/* name must be started with a latin letter or '_' */
static inline int is_first_name_w_(wchar_t c)
{
	return is_latin_letter_w_(c) || c == L'_';
}

/* returns decimal digit value or >9 if non-decimal digit char */
static inline unsigned digit_value_w(wchar_t c)
{
	unsigned x = (unsigned)c;
#ifdef UBSAN_UNSIGNED_OVERFLOW
	if (x < L'0')
		x += ((unsigned)-1 - L'0') + 1u;
	else
#endif
		x -= L'0';
	return x;
}

/* returns non-zero if c is a decimal digit */
static inline int is_digit_w(wchar_t c)
{
	return digit_value_w(c) <= 9;
}

/* name may be continued by a letter, digit or '_' */
static inline int is_next_name_w_(wchar_t c)
{
	return is_first_name_w_(c) || is_digit_w(c);
}

/* needed for hex_char_value_w_() */
typedef int gt_bad_A_0_diff_w_[1-2*(L'A' - L'0' <= 0)];

/* returns hex char value or >15 if non-hex char */
static inline unsigned hex_char_value_w_(wchar_t c)
{
	unsigned x = digit_value_w(c);
	if (x > 9) {
		const unsigned d = L'A' - L'0';
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

#endif /* CHAR_FUNC_W_H_INCLUDED */
