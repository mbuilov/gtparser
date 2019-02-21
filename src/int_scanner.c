/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2019 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* int_scanner.c */

#include "gtparser/name_scanner.h"
#include "gtparser/int_scanner.h"

#ifndef NULL
#define NULL ((const char*)0)
#endif

#ifndef SAL_DEFS_H_INCLUDED /* include "sal_defs.h" for the annotations */
#define A_Use_decl_annotations
#endif

/* s points to [0-9] */
A_Use_decl_annotations
GTPARSER_EXPORTS const char *gt_scan_uint(
	const char *s/*<end*/,
	const char *const end,
	unsigned *const number/*out*/)
{
	unsigned n = digit_value(*s);
	while (++s != end) {
		const unsigned x = digit_value(*s);
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
GTPARSER_EXPORTS const char *gt_scan_uint64(
	const char *s/*<end*/,
	const char *const end,
	unsigned INT64_TYPE *const number/*out*/)
{
	unsigned INT64_TYPE n = digit_value(*s);
	while (++s != end) {
		const unsigned x = digit_value(*s);
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
GTPARSER_EXPORTS const char *gt_scan_hex(
	const char *s/*<end*/,
	const char *const end,
	unsigned *const number/*out*/)
{
	unsigned n = hex_char_value(*s);
	while (++s != end) {
		const unsigned x = hex_char_value(*s);
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
GTPARSER_EXPORTS const char *gt_scan_hex64(
	const char *s/*<end*/,
	const char *const end,
	unsigned INT64_TYPE *const number/*out*/)
{
	unsigned INT64_TYPE n = hex_char_value(*s);
	while (++s != end) {
		const unsigned x = hex_char_value(*s);
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
GTPARSER_EXPORTS const char *gt_scan_uint_z(
	const char *s/*'\0'-terminated*/,
	unsigned *const number/*out*/)
{
	unsigned n = digit_value(*s);
	for (;;) {
		const unsigned x = digit_value(*++s);
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
GTPARSER_EXPORTS const char *gt_scan_uint64_z(
	const char *s/*'\0'-terminated*/,
	unsigned INT64_TYPE *const number/*out*/)
{
	unsigned INT64_TYPE n = digit_value(*s);
	for (;;) {
		const unsigned x = digit_value(*++s);
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
GTPARSER_EXPORTS const char *gt_scan_hex_z(
	const char *s/*'\0'-terminated*/,
	unsigned *const number/*out*/)
{
	unsigned n = hex_char_value(*s);
	for (;;) {
		const unsigned x = hex_char_value(*++s);
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
GTPARSER_EXPORTS const char *gt_scan_hex64_z(
	const char *s/*'\0'-terminated*/,
	unsigned INT64_TYPE *const number/*out*/)
{
	unsigned INT64_TYPE n = hex_char_value(*s);
	for (;;) {
		const unsigned x = hex_char_value(*++s);
		if (x > 15)
			break;
		if (n > ((unsigned INT64_TYPE)-1 >> 4))
			return NULL; /* integer overflow */
		n = (n << 4) + x;
	}
	*number = n;
	return s; /* s points to non-[0-9a-fA-F], may be to '\0' */
}
