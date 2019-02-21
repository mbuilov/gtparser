/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2018-2019 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* int_scanner_w.c */

#include <wchar.h>
#include "gtparser/char_func_w.h"
#include "gtparser/int_scanner_w.h"

#ifndef NULL
#define NULL ((const wchar_t*)0)
#endif

#ifndef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
#define A_Use_decl_annotations
#endif

/* s points to [0-9] */
A_Use_decl_annotations
GTPARSER_EXPORTS const wchar_t *gt_scan_uint_w(
	const wchar_t *s/*<end*/,
	const wchar_t *const end,
	unsigned *const number/*out*/)
{
	unsigned n = digit_value_w(*s);
	while (++s < end) {
		const unsigned x = digit_value_w(*s);
		if (x > 9)
			break;
		if (n > (unsigned)-1/10)
			return NULL; /* integer overflow */
		n *= 10;
		/* gcc optimizes well __builtin_mul_overflow() starting with version 5,
		   gcc optimizes well __builtin_add_overflow() starting with version 6,
		   clang optimizes well __builtin_mul_overflow(), starting with version 6 */
#if defined(__GNUC__) && !defined(__INTEL_COMPILER) && __GNUC__ >= 6
		if (__builtin_add_overflow(n, x, &n))
			return NULL; /* integer overflow */
#else
#ifdef UBSAN_UNSIGNED_OVERFLOW
		if (n > (unsigned)-1 - x)
			return NULL; /* integer overflow */
#endif
		n += x;
#ifndef UBSAN_UNSIGNED_OVERFLOW
		if (n < x)
			return NULL; /* integer overflow */
#endif
#endif
	}
	*number = n;
	return s; /* s points to non-[0-9], may be to end */
}

/* s points to [0-9] */
A_Use_decl_annotations
GTPARSER_EXPORTS const wchar_t *gt_scan_uint64_w(
	const wchar_t *s/*<end*/,
	const wchar_t *const end,
	unsigned INT64_TYPE *const number/*out*/)
{
	unsigned INT64_TYPE n = digit_value_w(*s);
	while (++s < end) {
		const unsigned x = digit_value_w(*s);
		if (x > 9)
			break;
		if (n > (unsigned INT64_TYPE)-1/10)
			return NULL; /* integer overflow */
		n *= 10;
		/* gcc optimizes well __builtin_mul_overflow() starting with version 5,
		   gcc optimizes well __builtin_add_overflow() starting with version 6,
		   clang optimizes well __builtin_mul_overflow(), starting with version 6 */
#if defined(__GNUC__) && !defined(__INTEL_COMPILER) && __GNUC__ >= 6
		if (__builtin_add_overflow(n, x, &n))
			return NULL; /* integer overflow */
#else
#ifdef UBSAN_UNSIGNED_OVERFLOW
		if (n > (unsigned INT64_TYPE)-1 - x)
			return NULL; /* integer overflow */
#endif
		n += x;
#ifndef UBSAN_UNSIGNED_OVERFLOW
		if (n < x)
			return NULL; /* integer overflow */
#endif
#endif
	}
	*number = n;
	return s; /* s points to non-[0-9], may be to end */
}

/* s points to [0-9a-fA-F] */
A_Use_decl_annotations
GTPARSER_EXPORTS const wchar_t *gt_scan_hex_w(
	const wchar_t *s/*<end*/,
	const wchar_t *const end,
	unsigned *const number/*out*/)
{
	unsigned n = hex_char_value_w_(*s);
	while (++s < end) {
		const unsigned x = hex_char_value_w_(*s);
		if (x > 15)
			break;
		if (n > ((unsigned)-1 >> 4))
			return NULL; /* integer overflow */
		n = (n << 4) + x;
	}
	*number = n;
	return s; /* s points to non-[0-9a-fA-F], may be to end */
}

/* s points to [0-9a-fA-F] */
A_Use_decl_annotations
GTPARSER_EXPORTS const wchar_t *gt_scan_hex64_w(
	const wchar_t *s/*<end*/,
	const wchar_t *const end,
	unsigned INT64_TYPE *const number/*out*/)
{
	unsigned INT64_TYPE n = hex_char_value_w_(*s);
	while (++s < end) {
		const unsigned x = hex_char_value_w_(*s);
		if (x > 15)
			break;
		if (n > ((unsigned INT64_TYPE)-1 >> 4))
			return NULL; /* integer overflow */
		n = (n << 4) + x;
	}
	*number = n;
	return s; /* s points to non-[0-9a-fA-F], may be to end */
}

/* s points to [0-9] */
A_Use_decl_annotations
GTPARSER_EXPORTS const wchar_t *gt_scan_uint_w_z(
	const wchar_t *s/*'\0'-terminated*/,
	unsigned *const number/*out*/)
{
	unsigned n = digit_value_w(*s);
	for (;;) {
		const unsigned x = digit_value_w(*++s);
		if (x > 9)
			break;
		if (n > (unsigned)-1/10)
			return NULL; /* integer overflow */
		n *= 10;
		/* gcc optimizes well __builtin_mul_overflow() starting with version 5,
		   gcc optimizes well __builtin_add_overflow() starting with version 6,
		   clang optimizes well __builtin_mul_overflow(), starting with version 6 */
#if defined(__GNUC__) && !defined(__INTEL_COMPILER) && __GNUC__ >= 6
		if (__builtin_add_overflow(n, x, &n))
			return NULL; /* integer overflow */
#else
#ifdef UBSAN_UNSIGNED_OVERFLOW
		if (n > (unsigned)-1 - x)
			return NULL; /* integer overflow */
#endif
		n += x;
#ifndef UBSAN_UNSIGNED_OVERFLOW
		if (n < x)
			return NULL; /* integer overflow */
#endif
#endif
	}
	*number = n;
	return s; /* s points to non-[0-9], may be to '\0' */
}

/* s points to [0-9] */
A_Use_decl_annotations
GTPARSER_EXPORTS const wchar_t *gt_scan_uint64_w_z(
	const wchar_t *s/*'\0'-terminated*/,
	unsigned INT64_TYPE *const number/*out*/)
{
	unsigned INT64_TYPE n = digit_value_w(*s);
	for (;;) {
		const unsigned x = digit_value_w(*++s);
		if (x > 9)
			break;
		if (n > (unsigned INT64_TYPE)-1/10)
			return NULL; /* integer overflow */
		n *= 10;
		/* gcc optimizes well __builtin_mul_overflow() starting with version 5,
		   gcc optimizes well __builtin_add_overflow() starting with version 6,
		   clang optimizes well __builtin_mul_overflow(), starting with version 6 */
#if defined(__GNUC__) && !defined(__INTEL_COMPILER) && __GNUC__ >= 6
		if (__builtin_add_overflow(n, x, &n))
			return NULL; /* integer overflow */
#else
#ifdef UBSAN_UNSIGNED_OVERFLOW
		if (n > (unsigned INT64_TYPE)-1 - x)
			return NULL; /* integer overflow */
#endif
		n += x;
#ifndef UBSAN_UNSIGNED_OVERFLOW
		if (n < x)
			return NULL; /* integer overflow */
#endif
#endif
	}
	*number = n;
	return s; /* s points to non-[0-9], may be to '\0' */
}

/* s points to [0-9a-fA-F] */
A_Use_decl_annotations
GTPARSER_EXPORTS const wchar_t *gt_scan_hex_w_z(
	const wchar_t *s/*'\0'-terminated*/,
	unsigned *const number/*out*/)
{
	unsigned n = hex_char_value_w_(*s);
	for (;;) {
		const unsigned x = hex_char_value_w_(*++s);
		if (x > 15)
			break;
		if (n > ((unsigned)-1 >> 4))
			return NULL; /* integer overflow */
		n = (n << 4) + x;
	}
	*number = n;
	return s; /* s points to non-[0-9a-fA-F], may be to '\0' */
}

/* s points to [0-9a-fA-F] */
A_Use_decl_annotations
GTPARSER_EXPORTS const wchar_t *gt_scan_hex64_w_z(
	const wchar_t *s/*'\0'-terminated*/,
	unsigned INT64_TYPE *const number/*out*/)
{
	unsigned INT64_TYPE n = hex_char_value_w_(*s);
	for (;;) {
		const unsigned x = hex_char_value_w_(*++s);
		if (x > 15)
			break;
		if (n > ((unsigned INT64_TYPE)-1 >> 4))
			return NULL; /* integer overflow */
		n = (n << 4) + x;
	}
	*number = n;
	return s; /* s points to non-[0-9a-fA-F], may be to '\0' */
}
