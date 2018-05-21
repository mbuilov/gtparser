/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2018 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* int_scanner_w.c */

#include <wchar.h>
#include "gtparser/char_func_w.h"
#include "gtparser/int_scanner_w.h"

/* s points to [0-9] */
GTPARSER_EXPORTS const wchar_t *gt_scan_uint_w(const wchar_t *s/*<end*/, const wchar_t *const end, unsigned *number/*out*/)
{
	unsigned n = digit_value_w(*s);
	while (++s != end) {
		unsigned x = digit_value_w(*s);
		if (x > 9)
			break;
		if (n > ~0u/10)
			return (const wchar_t*)0; /* integer overflow */
		n *= 10;
#ifdef UBSAN_UNSIGNED_OVERFLOW
		if (n > ~0u - x)
			return (const wchar_t*)0; /* integer overflow */
#endif
		n += x;
#ifndef UBSAN_UNSIGNED_OVERFLOW
		if (n < x)
			return (const wchar_t*)0; /* integer overflow */
#endif
	}
	*number = n;
	return s; /* s points to non-[0-9], may be to end */
}

/* s points to [0-9] */
GTPARSER_EXPORTS const wchar_t *gt_scan_uint64_w(const wchar_t *s/*<end*/, const wchar_t *const end, unsigned INT64_TYPE *number/*out*/)
{
	unsigned INT64_TYPE n = digit_value_w(*s);
	while (++s != end) {
		unsigned x = digit_value_w(*s);
		if (x > 9)
			break;
		if (n > (unsigned INT64_TYPE)-1/10)
			return (const wchar_t*)0; /* integer overflow */
		n *= 10;
#ifdef UBSAN_UNSIGNED_OVERFLOW
		if (n > (unsigned INT64_TYPE)-1 - x)
			return (const wchar_t*)0; /* integer overflow */
#endif
		n += x;
#ifndef UBSAN_UNSIGNED_OVERFLOW
		if (n < x)
			return (const wchar_t*)0; /* integer overflow */
#endif
	}
	*number = n;
	return s; /* s points to non-[0-9], may be to end */
}

/* s points to [0-9a-fA-F] */
GTPARSER_EXPORTS const wchar_t *gt_scan_hex_w(const wchar_t *s/*<end*/, const wchar_t *const end, unsigned *number/*out*/)
{
	unsigned n = hex_char_value_w_(*s);
	while (++s != end) {
		unsigned x = hex_char_value_w_(*s);
		if (x > 15)
			break;
		if (n > (~0u >> 4))
			return (const wchar_t*)0; /* integer overflow */
		n = (n << 4) + x;
	}
	*number = n;
	return s; /* s points to non-[0-9a-fA-F], may be to end */
}

/* s points to [0-9a-fA-F] */
GTPARSER_EXPORTS const wchar_t *gt_scan_hex64_w(const wchar_t *s/*<end*/, const wchar_t *const end, unsigned INT64_TYPE *number/*out*/)
{
	unsigned INT64_TYPE n = hex_char_value_w_(*s);
	while (++s != end) {
		unsigned x = hex_char_value_w_(*s);
		if (x > 15)
			break;
		if (n > ((unsigned INT64_TYPE)-1 >> 4))
			return (const wchar_t*)0; /* integer overflow */
		n = (n << 4) + x;
	}
	*number = n;
	return s; /* s points to non-[0-9a-fA-F], may be to end */
}

/* s points to [0-9] */
GTPARSER_EXPORTS const wchar_t *gt_scan_uint_w_z(const wchar_t *s/*'\0'-terminated*/, unsigned *number/*out*/)
{
	unsigned n = digit_value_w(*s);
	for (;;) {
		unsigned x = digit_value_w(*++s);
		if (x > 9)
			break;
		if (n > ~0u/10)
			return (const wchar_t*)0; /* integer overflow */
		n *= 10;
#ifdef UBSAN_UNSIGNED_OVERFLOW
		if (n > ~0u - x)
			return (const wchar_t*)0; /* integer overflow */
#endif
		n += x;
#ifndef UBSAN_UNSIGNED_OVERFLOW
		if (n < x)
			return (const wchar_t*)0; /* integer overflow */
#endif
	}
	*number = n;
	return s; /* s points to non-[0-9], may be to '\0' */
}

/* s points to [0-9] */
GTPARSER_EXPORTS const wchar_t *gt_scan_uint64_w_z(const wchar_t *s/*'\0'-terminated*/, unsigned INT64_TYPE *number/*out*/)
{
	unsigned INT64_TYPE n = digit_value_w(*s);
	for (;;) {
		unsigned x = digit_value_w(*++s);
		if (x > 9)
			break;
		if (n > (unsigned INT64_TYPE)-1/10)
			return (const wchar_t*)0; /* integer overflow */
		n *= 10;
#ifdef UBSAN_UNSIGNED_OVERFLOW
		if (n > (unsigned INT64_TYPE)-1 - x)
			return (const wchar_t*)0; /* integer overflow */
#endif
		n += x;
#ifndef UBSAN_UNSIGNED_OVERFLOW
		if (n < x)
			return (const wchar_t*)0; /* integer overflow */
#endif
	}
	*number = n;
	return s; /* s points to non-[0-9], may be to '\0' */
}

/* s points to [0-9a-fA-F] */
GTPARSER_EXPORTS const wchar_t *gt_scan_hex_w_z(const wchar_t *s/*'\0'-terminated*/, unsigned *number/*out*/)
{
	unsigned n = hex_char_value_w_(*s);
	for (;;) {
		unsigned x = hex_char_value_w_(*++s);
		if (x > 15)
			break;
		if (n > (~0u >> 4))
			return (const wchar_t*)0; /* integer overflow */
		n = (n << 4) + x;
	}
	*number = n;
	return s; /* s points to non-[0-9a-fA-F], may be to '\0' */
}

/* s points to [0-9a-fA-F] */
GTPARSER_EXPORTS const wchar_t *gt_scan_hex64_w_z(const wchar_t *s/*'\0'-terminated*/, unsigned INT64_TYPE *number/*out*/)
{
	unsigned INT64_TYPE n = hex_char_value_w_(*s);
	for (;;) {
		unsigned x = hex_char_value_w_(*++s);
		if (x > 15)
			break;
		if (n > ((unsigned INT64_TYPE)-1 >> 4))
			return (const wchar_t*)0; /* integer overflow */
		n = (n << 4) + x;
	}
	*number = n;
	return s; /* s points to non-[0-9a-fA-F], may be to '\0' */
}
