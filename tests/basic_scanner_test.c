/*******************************************************************************
* Generic Text parsing functions tests
* Copyright (C) 2008-2017 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under GPL version 3 or any later version, see COPYING
*******************************************************************************/

/* basic_scanner_test.c */

#include <stdio.h>
#include "name_scanner.h"
#include "int_scanner.h"

static int check_first_name_chars(int t)
{
	static const char first_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz";
	unsigned char c = 0;
	unsigned p = 0;
	for (;;) {
		if (!t ? _is_first_name((char)c) : is_first_name((char)c)) {
			if (p == sizeof(first_chars) - 1 || first_chars[p++] != c) {
				printf("bad first name char: %d\n", (char)c);
				return 1;
			}
		}
		if (c == (unsigned char)~(unsigned char)0)
			break;
		c++;
	}
	if (p != sizeof(first_chars) - 1) {
		printf("not all chars are recognized as first name\n");
		return 1;
	}
	return 0;
}

static int check_next_name_chars(int t)
{
	static const char next_chars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz";
	unsigned char c = 0;
	unsigned p = 0;
	for (;;) {
		if (!t ? _is_next_name((char)c) : is_next_name((char)c)) {
			if (p == sizeof(next_chars) - 1 || next_chars[p++] != c) {
				printf("bad next name char: %d\n", (char)c);
				return 1;
			}
		}
		if (c == (unsigned char)~(unsigned char)0)
			break;
		c++;
	}
	if (p != sizeof(next_chars) - 1) {
		printf("not all chars are recognized as next name\n");
		return 1;
	}
	return 0;
}

static int check_hex_chars(int t)
{
	static const char hex_chars[] = "0123456789ABCDEFabcdef";
	unsigned char c = 0;
	unsigned p = 0;
	for (;;) {
		if ((!t ? _hex_char_value((char)c) : hex_char_value((char)c)) <= 15) {
			if (p == sizeof(hex_chars) - 1 || hex_chars[p++] != c) {
				printf("bad hex char: %d\n", (char)c);
				return 1;
			}
		}
		if (c == (unsigned char)~(unsigned char)0)
			break;
		c++;
	}
	if (p != sizeof(hex_chars) - 1) {
		printf("not all chars are recognized as hex\n");
		return 1;
	}
	return 0;
}

static int test_scan_name(void)
{
	{
		static const char test_name1[] = "a0974htuhf_.34";
		const char *s = test_name1;
		const char *const end = test_name1 + sizeof(test_name1) - 1;
		s = _scan_name(s, end);
		if ((unsigned)(s - test_name1) != 11) {
			printf("_scan_name(%s) failed\n", test_name1);
			return 1;
		}
	}
	{
		static const char test_name2[] = "a0974htuhf_34";
		const char *s = test_name2;
		const char *const end = test_name2 + sizeof(test_name2) - 1;
		s = _scan_name(s, end);
		if ((unsigned)(s - test_name2) != 13) {
			printf("_scan_name(%s) failed\n", test_name2);
			return 1;
		}
	}
	{
		static const char test_name3[] = "a";
		const char *s = test_name3;
		const char *const end = test_name3 + sizeof(test_name3) - 1;
		s = _scan_name(s, end);
		if ((unsigned)(s - test_name3) != 1) {
			printf("_scan_name(%s) failed\n", test_name3);
			return 1;
		}
	}
	{
		static const char test_name4[] = "abc\xcc";
		const char *s = test_name4;
		const char *const end = test_name4 + sizeof(test_name4) - 1;
		s = _scan_name(s, end);
		if ((unsigned)(s - test_name4) != 3) {
			printf("_scan_name(%s) failed\n", test_name4);
			return 1;
		}
	}
	return 0;
}

static int test_scan_uint(void)
{
	{
		static const char test_uint1[] = "0";
		const char *s = test_uint1;
		const char *const end = test_uint1 + sizeof(test_uint1) - 1;
		unsigned n = 1;
		s = _scan_uint(s, end, &n);
		if (!s || n != 0) {
			printf("_scan_uint(%s) failed\n", test_uint1);
			return 1;
		}
	}
	{
		static const char test_uint2[] = "1";
		const char *s = test_uint2;
		const char *const end = test_uint2 + sizeof(test_uint2) - 1;
		unsigned n = 3;
		s = _scan_uint(s, end, &n);
		if (!s || n != 1) {
			printf("_scan_uint(%s) failed\n", test_uint2);
			return 1;
		}
	}
	{
		static const char test_uint3[] = "4294967295";
		const char *s = test_uint3;
		const char *const end = test_uint3 + sizeof(test_uint3) - 1;
		unsigned n = 4;
		s = _scan_uint(s, end, &n);
		if (!s || n != 4294967295) {
			printf("_scan_uint(%s) failed\n", test_uint3);
			return 1;
		}
	}
	{
		static const char test_uint4[] = "4294967296";
		const char *s = test_uint4;
		const char *const end = test_uint4 + sizeof(test_uint4) - 1;
		unsigned n = 5;
		s = _scan_uint(s, end, &n);
		if (s) {
			printf("_scan_uint(%s) failed\n", test_uint4);
			return 1;
		}
	}
	{
		static const char test_uint5[] = "24326963190";
		const char *s = test_uint5;
		const char *const end = test_uint5 + sizeof(test_uint5) - 1;
		unsigned n = 6;
		s = _scan_uint(s, end, &n);
		if (s) {
			printf("_scan_uint(%s) failed\n", test_uint5);
			return 1;
		}
	}
	return 0;
}

static int test_scan_hex(void)
{
	{
		static const char test_hex1[] = "0";
		const char *s = test_hex1;
		const char *const end = test_hex1 + sizeof(test_hex1) - 1;
		unsigned n = 1;
		s = _scan_hex(s, end, &n);
		if (!s || n != 0) {
			printf("_scan_hex(%s) failed\n", test_hex1);
			return 1;
		}
	}
	{
		static const char test_hex2[] = "1";
		const char *s = test_hex2;
		const char *const end = test_hex2 + sizeof(test_hex2) - 1;
		unsigned n = 2;
		s = _scan_hex(s, end, &n);
		if (!s || n != 1) {
			printf("_scan_hex(%s) failed\n", test_hex2);
			return 1;
		}
	}
	{
		static const char test_hex3[] = "abC1";
		const char *s = test_hex3;
		const char *const end = test_hex3 + sizeof(test_hex3) - 1;
		unsigned n = 3;
		s = _scan_hex(s, end, &n);
		if (!s || n != 0xabc1) {
			printf("_scan_hex(%s) failed\n", test_hex3);
			return 1;
		}
	}
	{
		static const char test_hex4[] = "ffFFffFF";
		const char *s = test_hex4;
		const char *const end = test_hex4 + sizeof(test_hex4) - 1;
		unsigned n = 4;
		s = _scan_hex(s, end, &n);
		if (!s || n != 0xFFFFFFFF) {
			printf("_scan_hex(%s) failed\n", test_hex4);
			return 1;
		}
	}
	{
		static const char test_hex5[] = "ffFFffFF0";
		const char *s = test_hex5;
		const char *const end = test_hex5 + sizeof(test_hex5) - 1;
		unsigned n = 5;
		s = _scan_hex(s, end, &n);
		if (s) {
			printf("_scan_hex(%s) failed\n", test_hex5);
			return 1;
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{
	if (check_first_name_chars(0))
		return 1;
	if (check_next_name_chars(0))
		return 1;
	if (check_hex_chars(0))
		return 1;
	if (check_first_name_chars(1))
		return 1;
	if (check_next_name_chars(1))
		return 1;
	if (check_hex_chars(1))
		return 1;
	if (test_scan_name())
		return 1;
	if (test_scan_uint())
		return 1;
	if (test_scan_hex())
		return 1;
	(void)argc, (void)argv;
	return 0;
}
