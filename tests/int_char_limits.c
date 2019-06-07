#include <stdio.h>
#include "../gtparser/int_char.h"

static void test_ge(void)
{
	unsigned t = 0;
	for (; t <= 255; t++) {
		unsigned i = 0;
		for (; i <= 65535; i++) {
			char tt = (char)(unsigned char)t;
			unsigned short ii = (unsigned short)i;
			int x =
				(i & 255) >= t &&
				((i >> 8) & 255) >= t;
			int y;
			GT_UINT_ALL_GE_(char, unsigned short, tt, ii, y);
			if (x != y) {
				if (t <= GT_TYPE_TOP_BIT(unsigned short, char)) {
					printf("ge unexpected fail: t=%u (%x), i=%u (%.4x), (x=%d, y=%d)\n", t, t, i, i, x, y);
					return;
				}
				break; /* expected fail */
			}
		}
		if (!(t & 15))
			printf("ge ok: t=%u\n", t);
	}
}

static void test_range(void)
{
	unsigned l = 0;
	for (; l <= 255; l++) {
		unsigned u = l;
		for (; u <= 255; u++) {
			unsigned i = 0;
			for (; i <= 65535; i++) {
				char ll = (char)(unsigned char)l;
				char uu = (char)(unsigned char)u;
				unsigned short ii = (unsigned short)i;
				int x =
					l <= (i & 255) && (i & 255) <= u &&
					l <= ((i >> 8) & 255) && ((i >> 8) & 255) <= u;
				int y;
				GT_IS_UINT_CHARS_IN_RANGE_(char, unsigned short, ll, uu, ii, y);
				if (x != y) {
					if (u - l < GT_TYPE_TOP_BIT(unsigned short, char)) {
						printf("r unexpected fail: l=%u (%x), u=%u (%x), i=%u (%.4x), (x=%d, y=%d)\n", l, l, u, u, i, i, x, y);
						return;
					}
					break; /* expected fail */
				}
			}
		}
		if (!(l & 31))
			printf("r ok: l=%u\n", l);
	}
}

#define WSTEP 50000

static void test_ge_w(void)
{
	unsigned long long i = 0;
	unsigned t = 0;
	for (; t <= 65535; t++) {
		for (; i <= (unsigned)-1; i += WSTEP) {
			short tt = (short)(unsigned short)t;
			unsigned ii = (unsigned)i;
			int x =
				(i & 65535) >= t &&
				((i >> 16) & 65535) >= t;
			int y;
			GT_UINT_ALL_GE_(short, unsigned, tt, ii, y);
			if (x != y) {
				if (t <= GT_TYPE_TOP_BIT(unsigned, short)) {
					printf("ge_w unexpected fail: t=%u (%x), i=%llu (%.8llx), (x=%d, y=%d)\n", t, t, i, i, x, y);
					return;
				}
				break; /* expected fail */
			}
		}
		if (i > (unsigned)-1 && !(t & 1023))
			printf("ge_w ok: t=%u\n", t);
		i &= (unsigned)-1;
	}
}

#define RSTEP 500000
#define LSTEP 15
#define USTEP 20

static void test_range_w(void)
{
	unsigned long long i = 0;
	unsigned l = 0;
	for (; l <= 65535; l += LSTEP) {
		unsigned u = l;
		for (; u <= 65535; u += USTEP) {
			for (; i <= (unsigned)-1; i += RSTEP) {
				short ll = (short)(unsigned short)l;
				short uu = (short)(unsigned short)u;
				unsigned ii = (unsigned)i;
				int x =
					l <= (i & 65535) && (i & 65535) <= u &&
					l <= ((i >> 16) & 65535) && ((i >> 16) & 65535) <= u;
				int y;
				GT_IS_UINT_CHARS_IN_RANGE_(short, unsigned, ll, uu, ii, y);
				if (x != y) {
					if (u - l < GT_TYPE_TOP_BIT(unsigned, short)) {
						printf("r unexpected fail: l=%u (%x), u=%u (%x), i=%llu (%.8llx), (x=%d, y=%d)\n", l, l, u, u, i, i, x, y);
						return;
					}
					break; /* expected fail */
				}
			}
			i &= (unsigned)-1;
		}
		if (!(l & 63))
			printf("r_w ok: l=%u\n", l);
	}
}

int main(int argc, char *argv[])
{
	test_ge();
	test_range();
	test_ge_w();
	test_range_w();
	return 0;
}
