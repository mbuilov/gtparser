/*******************************************************************************
* gtparser tests
* Copyright (C) 2008-2017 Michael M. Builov, https://github.com/mbuilov/gtparser
* Licensed under GPL version 3 or any later version, see COPYING.GPL3
*******************************************************************************/

/* cstring_parser_test.c */

#include <string.h>
#include <stdio.h>
#include "gtparser/cstring_parser.h"
#include "gtparser/parser_base.h"

static int test1(void)
{
	const char src[] = "\"\"";
	struct src_iter it;
	src_iter_init(&it, src, sizeof(src) - 1);
	{
		size_t removed = 0;
		enum PARSE_CSTRING_ERR r = gt_parse_cstring(&it, &removed);
		if (PARSE_CSTRING_OK != r) {
			fprintf(stderr, "failed to parse test string \"%s\": err = %d\n", src, (int)r);
			return 0;
		}
		if (removed) {
			fprintf(stderr, "expecting zero removed chars in test string \"%s\"\n", src);
			return 0;
		}
		if (src + sizeof(src) - 2 != it.current) {
			fprintf(stderr, "wrong parsed length of test string \"%s\"\n", src);
			return 0;
		}
	}
	return 1;
}

static int test2(void)
{
	const char src[] = "\"\\\"\"";
	struct src_iter it;
	src_iter_init(&it, src, sizeof(src) - 1);
	{
		size_t removed = 0;
		enum PARSE_CSTRING_ERR r = gt_parse_cstring(&it, &removed);
		if (PARSE_CSTRING_OK != r) {
			fprintf(stderr, "failed to parse test string \"%s\": err = %d\n", src, (int)r);
			return 0;
		}
		if (removed != 1) {
			fprintf(stderr, "must unescape double quote in test string \"%s\"\n", src);
			return 0;
		}
		if (src + sizeof(src) - 2 != it.current) {
			fprintf(stderr, "wrong parsed length of test string \"%s\"\n", src);
			return 0;
		}
		{
			unsigned len = (unsigned)(((size_t)(it.current - src) - 1 - removed) & ~0u);
			if (1 != len) {
				fprintf(stderr, "bad parsed test string length \"%s\" -> %u\n", src, len);
				return 0;
			}
			{
				char dst[2];
				gt_copy_cstring(dst, src + 1, it.current, removed);
				dst[len] = '\0';
				if (dst[0] != '"') {
					fprintf(stderr, "bad parsed test string \"%s\" -> \"%s\" {%u}\n", src, dst, (unsigned char)dst[0]);
					return 0;
				}
			}
		}
	}
	return 1;
}

static int test3(void)
{
	const char src[] = "\"\\a\\\n1\"";
	struct src_iter it;
	src_iter_init(&it, src, sizeof(src) - 1);
	{
		size_t removed = 0;
		enum PARSE_CSTRING_ERR r = gt_parse_cstring(&it, &removed);
		if (PARSE_CSTRING_OK != r) {
			fprintf(stderr, "failed to parse test string \"%s\": err = %d\n", src, (int)r);
			return 0;
		}
		if (removed != 3) {
			fprintf(stderr, "wrong count of removed characters in test string \"%s\" -> %u\n", src, 0u + (unsigned)(removed & ~0u));
			return 0;
		}
		if (src + sizeof(src) - 2 != it.current) {
			fprintf(stderr, "wrong parsed length of test string \"%s\"\n", src);
			return 0;
		}
		{
			unsigned len = (unsigned)(((size_t)(it.current - src) - 1 - removed) & ~0u);
			if (2 != len) {
				fprintf(stderr, "bad parsed test string length \"%s\" -> %u\n", src, len);
				return 0;
			}
			{
				char dst[3];
				gt_copy_cstring(dst, src + 1, it.current, removed);
				dst[len] = '\0';
				if (dst[0] != '\a' || dst[1] != '1') {
					fprintf(stderr, "bad parsed test string \"%s\" -> \"%s\" {%u,%u}\n",
						src, dst, (unsigned char)dst[0], (unsigned char)dst[1]);
					return 0;
				}
			}
		}
	}
	return 1;
}

static int test4(void)
{
	const char src[] = "\"\\3761\"";
	struct src_iter it;
	src_iter_init(&it, src, sizeof(src) - 1);
	{
		size_t removed = 0;
		enum PARSE_CSTRING_ERR r = gt_parse_cstring(&it, &removed);
		if (PARSE_CSTRING_OK != r) {
			fprintf(stderr, "failed to parse test string \"%s\": err = %d\n", src, (int)r);
			return 0;
		}
		if (removed != 3) {
			fprintf(stderr, "wrong count of removed characters in test string \"%s\" -> %u\n", src, 0u + (unsigned)(removed & ~0u));
			return 0;
		}
		if (src + sizeof(src) - 2 != it.current) {
			fprintf(stderr, "wrong parsed length of test string \"%s\"\n", src);
			return 0;
		}
		{
			unsigned len = ((size_t)(it.current - src) - 1 - removed) & ~0u;
			if (2 != len) {
				fprintf(stderr, "bad parsed test string length \"%s\" -> %u\n", src, len);
				return 0;
			}
			{
				char dst[3];
				gt_copy_cstring(dst, src + 1, it.current, removed);
				dst[len] = '\0';
				if (dst[0] != '\376' || dst[1] != '1') {
					fprintf(stderr, "bad parsed test string \"%s\" -> \"%s\" {%u,%u}\n",
						src, dst, (unsigned char)dst[0], (unsigned char)dst[1]);
					return 0;
				}
			}
		}
	}
	return 1;
}

static int test5(void)
{
	const char src[] = "\"\\x1c3\"";
	struct src_iter it;
	src_iter_init(&it, src, sizeof(src) - 1);
	{
		size_t removed = 0;
		enum PARSE_CSTRING_ERR r = gt_parse_cstring(&it, &removed);
		if (PARSE_CSTRING_OK != r) {
			fprintf(stderr, "failed to parse test string \"%s\": err = %d\n", src, (int)r);
			return 0;
		}
		if (removed != 3) {
			fprintf(stderr, "wrong count of removed characters in test string \"%s\" -> %u\n", src, 0u + (unsigned)(removed & ~0u));
			return 0;
		}
		if (src + sizeof(src) - 2 != it.current) {
			fprintf(stderr, "wrong parsed length of test string \"%s\"\n", src);
			return 0;
		}
		{
			unsigned len = ((size_t)(it.current - src) - 1 - removed) & ~0u;
			if (2 != len) {
				fprintf(stderr, "bad parsed test string length \"%s\" -> %u\n", src, len);
				return 0;
			}
			{
				char dst[3];
				gt_copy_cstring(dst, src + 1, it.current, removed);
				dst[len] = '\0';
				if (dst[0] != '\x1c' || dst[1] != '3') {
					fprintf(stderr, "bad parsed test string \"%s\" -> \"%s\" {%u,%u}\n", src, dst, (unsigned char)dst[0], (unsigned char)dst[1]);
					return 0;
				}
			}
		}
	}
	return 1;
}

static int test6(void)
{
	const char src[] = "\"\\001\\01\\1\\x1\\x0F\"";
	struct src_iter it;
	src_iter_init(&it, src, sizeof(src) - 1);
	{
		size_t removed = 0;
		enum PARSE_CSTRING_ERR r = gt_parse_cstring(&it, &removed);
		if (PARSE_CSTRING_OK != r) {
			fprintf(stderr, "failed to parse test string \"%s\": err = %d\n", src, (int)r);
			return 0;
		}
		if (removed != 11) {
			fprintf(stderr, "wrong count of removed characters in test string \"%s\" -> %u\n", src, 0u + (unsigned)(removed & ~0u));
			return 0;
		}
		if (src + sizeof(src) - 2 != it.current) {
			fprintf(stderr, "wrong parsed length of test string \"%s\"\n", src);
			return 0;
		}
		{
			unsigned len = ((size_t)(it.current - src) - 1 - removed) & ~0u;
			if (5 != len) {
				fprintf(stderr, "bad parsed test string length \"%s\" -> %u\n", src, len);
				return 0;
			}
			{
				char dst[6];
				gt_copy_cstring(dst, src + 1, it.current, removed);
				dst[len] = '\0';
				if (dst[0] != '\1' || dst[1] != '\1' || dst[2] != '\1' || dst[3] != '\1' || dst[4] != '\x0F') {
					fprintf(stderr, "bad parsed test string \"%s\" -> \"%s\" {%u,%u,%u,%u,%u}\n", src, dst,
						(unsigned char)dst[0], (unsigned char)dst[1], (unsigned char)dst[2], (unsigned char)dst[3], (unsigned char)dst[4]);
					return 0;
				}
			}
		}
	}
	return 1;
}

static int test7(void)
{
	const char src[] = "\"\\771\"";
	struct src_iter it;
	src_iter_init(&it, src, sizeof(src) - 1);
	{
		size_t removed = 0;
		enum PARSE_CSTRING_ERR r = gt_parse_cstring(&it, &removed);
		if (PARSE_CSTRING_TOO_BIG_OCTAL != r) {
			fprintf(stderr, "expecting PARSE_CSTRING_TOO_BIG_OCTAL error for test string \"%s\", but err = %d\n", src, (int)r);
			return 0;
		}
	}
	return 1;
}

static int test8(void)
{
	const char src[] = "\"\\0001\"";
	struct src_iter it;
	src_iter_init(&it, src, sizeof(src) - 1);
	{
		size_t removed = 0;
		enum PARSE_CSTRING_ERR r = gt_parse_cstring(&it, &removed);
		if (PARSE_CSTRING_NULL_INSIDE_CSTRING != r) {
			fprintf(stderr, "expecting PARSE_CSTRING_NULL_INSIDE_CSTRING error for test string \"%s\", but err = %d\n", src, (int)r);
			return 0;
		}
	}
	return 1;
}

static int test9(void)
{
	const char src[] = "\"\\x00f\"";
	struct src_iter it;
	src_iter_init(&it, src, sizeof(src) - 1);
	{
		size_t removed = 0;
		enum PARSE_CSTRING_ERR r = gt_parse_cstring(&it, &removed);
		if (PARSE_CSTRING_NULL_INSIDE_CSTRING != r) {
			fprintf(stderr, "expecting PARSE_CSTRING_NULL_INSIDE_CSTRING error for test string \"%s\", but err = %d\n", src, (int)r);
			return 0;
		}
	}
	return 1;
}

static int test10(void)
{
	const char src[] = "\"\\xg\"";
	struct src_iter it;
	src_iter_init(&it, src, sizeof(src) - 1);
	{
		size_t removed = 0;
		enum PARSE_CSTRING_ERR r = gt_parse_cstring(&it, &removed);
		if (PARSE_CSTRING_EXPECTING_HEX_DIGIT != r) {
			fprintf(stderr, "expecting PARSE_CSTRING_EXPECTING_HEX_DIGIT error for test string \"%s\", but err = %d\n", src, (int)r);
			return 0;
		}
	}
	return 1;
}

static int test11(void)
{
	const char src[] = "\"\\g\\\"";
	struct src_iter it;
	src_iter_init(&it, src, sizeof(src) - 1);
	{
		size_t removed = 0;
		enum PARSE_CSTRING_ERR r = gt_parse_cstring(&it, &removed);
		if (PARSE_CSTRING_UNTERMINATED != r) {
			fprintf(stderr, "expecting PARSE_CSTRING_UNTERMINATED error for test string \"%s\", but err = %d\n", src, (int)r);
			return 0;
		}
	}
	return 1;
}

int main(int argc, char *argv[])
{
	if (!test1())
		return 1;
	if (!test2())
		return 1;
	if (!test3())
		return 1;
	if (!test4())
		return 1;
	if (!test5())
		return 1;
	if (!test6())
		return 1;
	if (!test7())
		return 1;
	if (!test8())
		return 1;
	if (!test9())
		return 1;
	if (!test10())
		return 1;
	if (!test11())
		return 1;
	(void)argc, (void)argv;
	printf("ok\n");
	return 0;
}
