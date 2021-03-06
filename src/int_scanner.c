/*******************************************************************************
* gtparser - Generic Text parsing functions library
* Copyright (C) 2008-2018 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under LGPL version 2.1 or any later version, see COPYING
*******************************************************************************/

/* int_scanner.c */

#include "gtparser/name_scanner.h"
#include "gtparser/int_scanner.h"

/* s points to [0-9] */
GTPARSER_EXPORTS const char *gt_scan_uint(const char *s/*<end*/, const char *const end, unsigned *number/*out*/)
{
	unsigned n = digit_value(*s);
	while (++s != end) {
		unsigned x = digit_value(*s);
		if (x > 9)
			break;
		if (n > ~0u/10)
			return (const char*)0; /* integer overflow */
		n *= 10;
#ifdef GTPARSER_NO_UINT_OVERFLOW
		if (n > ~0u - x)
			return (const char*)0; /* integer overflow */
#endif
		n += x;
#ifndef GTPARSER_NO_UINT_OVERFLOW
		if (n < x)
			return (const char*)0; /* integer overflow */
#endif
	}
	*number = n;
	return s; /* s points to non-[0-9], may be to end */
}

/* s points to [0-9] */
GTPARSER_EXPORTS const char *gt_scan_uint64(const char *s/*<end*/, const char *const end, unsigned INT64_TYPE *number/*out*/)
{
	unsigned INT64_TYPE n = digit_value(*s);
	while (++s != end) {
		unsigned x = digit_value(*s);
		if (x > 9)
			break;
		if (n > (unsigned INT64_TYPE)~(unsigned INT64_TYPE)0/10)
			return (const char*)0; /* integer overflow */
		n *= 10;
#ifdef GTPARSER_NO_UINT_OVERFLOW
		if (n > (unsigned INT64_TYPE)~(unsigned INT64_TYPE)0 - x)
			return (const char*)0; /* integer overflow */
#endif
		n += x;
#ifndef GTPARSER_NO_UINT_OVERFLOW
		if (n < x)
			return (const char*)0; /* integer overflow */
#endif
	}
	*number = n;
	return s; /* s points to non-[0-9], may be to end */
}

/* s points to [0-9a-fA-F] */
GTPARSER_EXPORTS const char *gt_scan_hex(const char *s/*<end*/, const char *const end, unsigned *number/*out*/)
{
	unsigned n = hex_char_value(*s);
	while (++s != end) {
		unsigned x = hex_char_value(*s);
		if (x > 15)
			break;
		if (n > (~0u >> 4))
			return (const char*)0; /* integer overflow */
		n = (n << 4) + x;
	}
	*number = n;
	return s; /* s points to non-[0-9a-fA-F], may be to end */
}

/* s points to [0-9a-fA-F] */
GTPARSER_EXPORTS const char *gt_scan_hex64(const char *s/*<end*/, const char *const end, unsigned INT64_TYPE *number/*out*/)
{
	unsigned INT64_TYPE n = hex_char_value(*s);
	while (++s != end) {
		unsigned x = hex_char_value(*s);
		if (x > 15)
			break;
		if (n > ((unsigned INT64_TYPE)~(unsigned INT64_TYPE)0 >> 4))
			return (const char*)0; /* integer overflow */
		n = (n << 4) + x;
	}
	*number = n;
	return s; /* s points to non-[0-9a-fA-F], may be to end */
}

/* s points to [0-9] */
GTPARSER_EXPORTS const char *gt_scan_uint_z(const char *s/*'\0'-terminated*/, unsigned *number/*out*/)
{
	unsigned n = digit_value(*s);
	for (;;) {
		unsigned x = digit_value(*++s);
		if (x > 9)
			break;
		if (n > ~0u/10)
			return (const char*)0; /* integer overflow */
		n *= 10;
#ifdef GTPARSER_NO_UINT_OVERFLOW
		if (n > ~0u - x)
			return (const char*)0; /* integer overflow */
#endif
		n += x;
#ifndef GTPARSER_NO_UINT_OVERFLOW
		if (n < x)
			return (const char*)0; /* integer overflow */
#endif
	}
	*number = n;
	return s; /* s points to non-[0-9], may be to '\0' */
}

/* s points to [0-9] */
GTPARSER_EXPORTS const char *gt_scan_uint64_z(const char *s/*'\0'-terminated*/, unsigned INT64_TYPE *number/*out*/)
{
	unsigned INT64_TYPE n = digit_value(*s);
	for (;;) {
		unsigned x = digit_value(*++s);
		if (x > 9)
			break;
		if (n > (unsigned INT64_TYPE)~(unsigned INT64_TYPE)0/10)
			return (const char*)0; /* integer overflow */
		n *= 10;
#ifdef GTPARSER_NO_UINT_OVERFLOW
		if (n > (unsigned INT64_TYPE)~(unsigned INT64_TYPE)0 - x)
			return (const char*)0; /* integer overflow */
#endif
		n += x;
#ifndef GTPARSER_NO_UINT_OVERFLOW
		if (n < x)
			return (const char*)0; /* integer overflow */
#endif
	}
	*number = n;
	return s; /* s points to non-[0-9], may be to '\0' */
}

/* s points to [0-9a-fA-F] */
GTPARSER_EXPORTS const char *gt_scan_hex_z(const char *s/*'\0'-terminated*/, unsigned *number/*out*/)
{
	unsigned n = hex_char_value(*s);
	for (;;) {
		unsigned x = hex_char_value(*++s);
		if (x > 15)
			break;
		if (n > (~0u >> 4))
			return (const char*)0; /* integer overflow */
		n = (n << 4) + x;
	}
	*number = n;
	return s; /* s points to non-[0-9a-fA-F], may be to '\0' */
}

/* s points to [0-9a-fA-F] */
GTPARSER_EXPORTS const char *gt_scan_hex64_z(const char *s/*'\0'-terminated*/, unsigned INT64_TYPE *number/*out*/)
{
	unsigned INT64_TYPE n = hex_char_value(*s);
	for (;;) {
		unsigned x = hex_char_value(*++s);
		if (x > 15)
			break;
		if (n > ((unsigned INT64_TYPE)~(unsigned INT64_TYPE)0 >> 4))
			return (const char*)0; /* integer overflow */
		n = (n << 4) + x;
	}
	*number = n;
	return s; /* s points to non-[0-9a-fA-F], may be to '\0' */
}
