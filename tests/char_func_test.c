#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <wchar.h>

/* compile with:
  gcc char_func_test.c
 or
  cl char_func_test.c /utf-8
*/

typedef int source_character_set_is_not_utf8[1-2*(0x044B != L'ы')];

#ifndef _MSC_VER
#define INT64_TYPE long long
#else
#define INT64_TYPE __int64
#endif

#include "../gtparser/char_func.h"
#include "../gtparser/char_func_w.h"

#define TR(r) printf("t%u: %s (line %d)\n", t++, (r) ? "ok" : ((rr = 1), "fail"), __LINE__)

/* n - minimum required number of chars for the test */
#define TF(n, s, fn) do {                  \
	if (sizeof(x) >= n*sizeof(*s)) {       \
		memcpy(&x, s, sizeof(x));          \
		fn;                                \
	}                                      \
	else                                   \
		printf("t%u: skip (line %d)\n", (k++, t++), __LINE__); \
} while (0)
#define TF64(n, s, fn) do {                \
	if (sizeof(x64) >= n*sizeof(*s)) {     \
		memcpy(&x64, s, sizeof(x64));      \
		fn;                                \
	}                                      \
	else                                   \
		printf("t%u: skip (line %d)\n", (k++, t++), __LINE__); \
} while (0)
#define TFW(n, s, fn) do {                 \
	if (sizeof(x) >= n*sizeof(*s)) {       \
		memcpy(&x, s, sizeof(x));          \
		fn;                                \
	}                                      \
	else                                   \
		printf("t%u: skip (line %d)\n", (k++, t++), __LINE__); \
} while (0)
#define TF64W(n, s, fn) do {               \
	if (sizeof(x64) >= n*sizeof(*s)) {     \
		memcpy(&x64, s, sizeof(x64));      \
		fn;                                \
	}                                      \
	else                                   \
		printf("t%u: skip (line %d)\n", (k++, t++), __LINE__); \
} while (0)

int main(int argc, char *argv[])
{
	int rr = 0;
	unsigned t = 0;
	unsigned k = 0;
	unsigned x;
	unsigned INT64_TYPE x64;
	(void)argc;
	(void)argv;
	/* */
	TR(is_latin_upper_letter_('A'));
	TR(is_latin_upper_letter_('Z'));
	TR(!is_latin_upper_letter_('a'));
	TR(!is_latin_upper_letter_('z'));
	TR(!is_latin_upper_letter_('0'));
	TR(!is_latin_upper_letter_('9'));
	TR(!is_latin_upper_letter_(' '));
	TR(!is_latin_upper_letter_('\x88'));
	TR(!is_latin_upper_letter_('0'));
	TR(!is_latin_upper_letter_('\xFF'));
	/* */
	TR(!is_latin_lower_letter_('A'));
	TR(!is_latin_lower_letter_('Z'));
	TR(is_latin_lower_letter_('a'));
	TR(is_latin_lower_letter_('z'));
	TR(!is_latin_lower_letter_('0'));
	TR(!is_latin_lower_letter_('9'));
	TR(!is_latin_lower_letter_(' '));
	TR(!is_latin_lower_letter_('\x88'));
	TR(!is_latin_lower_letter_('\0'));
	TR(!is_latin_lower_letter_('\xFF'));
	/* */
	TR(is_latin_letter_('A'));
	TR(is_latin_letter_('Z'));
	TR(is_latin_letter_('a'));
	TR(is_latin_letter_('z'));
	TR(!is_latin_letter_('0'));
	TR(!is_latin_letter_('9'));
	TR(!is_latin_letter_(' '));
	TR(!is_latin_letter_('\x88'));
	TR(!is_latin_letter_('\0'));
	TR(!is_latin_letter_('\xFF'));
	/* */
	TR('a' == latin_letter_to_lower('A'));
	TR('z' == latin_letter_to_lower('Z'));
	TR('a' == latin_letter_to_lower('a'));
	TR('z' == latin_letter_to_lower('z'));
	/* */
	TR('A' == latin_letter_to_upper('A'));
	TR('Z' == latin_letter_to_upper('Z'));
	TR('A' == latin_letter_to_upper('a'));
	TR('Z' == latin_letter_to_upper('z'));
	/* */
	TR('a' == latin_to_lower('A'));
	TR('z' == latin_to_lower('Z'));
	TR('a' == latin_to_lower('a'));
	TR('z' == latin_to_lower('z'));
	TR('0' == latin_to_lower('0'));
	TR('9' == latin_to_lower('9'));
	TR('\x88' == latin_to_lower('\x88'));
	TR('\0' == latin_to_lower('\0'));
	TR('\xFF' == latin_to_lower('\xFF'));
	/* */
	TR('A' == latin_to_upper('A'));
	TR('Z' == latin_to_upper('Z'));
	TR('A' == latin_to_upper('a'));
	TR('Z' == latin_to_upper('z'));
	TR('0' == latin_to_upper('0'));
	TR('9' == latin_to_upper('9'));
	TR('\x88' == latin_to_upper('\x88'));
	TR('\0' == latin_to_upper('\0'));
	TR('\xFF' == latin_to_upper('\xFF'));
	/* */
	TR(is_first_name_('A'));
	TR(is_first_name_('Z'));
	TR(is_first_name_('a'));
	TR(is_first_name_('z'));
	TR(!is_first_name_('0'));
	TR(!is_first_name_('9'));
	TR(!is_first_name_('\x88'));
	TR(!is_first_name_('\0'));
	TR(!is_first_name_('\xFF'));
	TR(is_first_name_('_'));
	/* */
	TR(is_next_name_('A'));
	TR(is_next_name_('Z'));
	TR(is_next_name_('a'));
	TR(is_next_name_('z'));
	TR(is_next_name_('0'));
	TR(is_next_name_('9'));
	TR(!is_next_name_('\x88'));
	TR(!is_next_name_('\0'));
	TR(!is_next_name_('\xFF'));
	TR(is_next_name_('_'));
	/* */
	TR(0 == digit_value('0'));
	TR(9 == digit_value('9'));
	/* */
	TR(!is_digit('A'));
	TR(!is_digit('Z'));
	TR(!is_digit('a'));
	TR(!is_digit('z'));
	TR(is_digit('0'));
	TR(is_digit('9'));
	TR(!is_digit('\x88'));
	TR(!is_digit('\0'));
	TR(!is_digit('\xFF'));
	TR(!is_digit('_'));
	/* */
	TR(10 == hex_char_value_('A'));
	TR(15 == hex_char_value_('F'));
	TR(hex_char_value_('Z') > 15);
	TR(10 == hex_char_value_('a'));
	TR(15 == hex_char_value_('f'));
	TR(hex_char_value_('z') > 15);
	TR(0 == hex_char_value_('0'));
	TR(9 == hex_char_value_('9'));
	TR(hex_char_value_('\x88') > 15);
	TR(hex_char_value_('\0') > 15);
	TR(hex_char_value_('\xFF') > 15);
	TR(hex_char_value_('_') > 15);
	/* */
	TF(1, "ABCDEFGH", TR(is_latin_upper_letters_uint_(x)));
	TF(4, "ABCdEFGH", TR(!is_latin_upper_letters_uint_(x)));
	TF(3, "ABcDEFGH", TR(!is_latin_upper_letters_uint_(x)));
	TF(3, "ABcdEFGH", TR(!is_latin_upper_letters_uint_(x)));
	TF(2, "AbCDEFGH", TR(!is_latin_upper_letters_uint_(x)));
	TF(2, "AbCdEFGH", TR(!is_latin_upper_letters_uint_(x)));
	TF(2, "AbcDEFGH", TR(!is_latin_upper_letters_uint_(x)));
	TF(2, "AbcdEFGH", TR(!is_latin_upper_letters_uint_(x)));
	TF(1, "aBCDEFGH", TR(!is_latin_upper_letters_uint_(x)));
	TF(1, "aBCdEFGH", TR(!is_latin_upper_letters_uint_(x)));
	TF(1, "aBcDEFGH", TR(!is_latin_upper_letters_uint_(x)));
	TF(1, "aBcdEFGH", TR(!is_latin_upper_letters_uint_(x)));
	TF(1, "abCDEFGH", TR(!is_latin_upper_letters_uint_(x)));
	TF(1, "abCdEFGH", TR(!is_latin_upper_letters_uint_(x)));
	TF(1, "abcDEFGH", TR(!is_latin_upper_letters_uint_(x)));
	TF(1, "abcdEFGH", TR(!is_latin_upper_letters_uint_(x)));
	TF(1, "1BCDEFGH", TR(!is_latin_upper_letters_uint_(x)));
	TF(1, "\x88TCDEFGH", TR(!is_latin_upper_letters_uint_(x)));
	TF(2, "A1CDEFGH", TR(!is_latin_upper_letters_uint_(x)));
	TF(2, "A\x88TDEFGH", TR(!is_latin_upper_letters_uint_(x)));
	TF(3, "AB1DEFGH", TR(!is_latin_upper_letters_uint_(x)));
	TF(3, "AB\x88TEFGH", TR(!is_latin_upper_letters_uint_(x)));
	TF(4, "ABC1EFGH", TR(!is_latin_upper_letters_uint_(x)));
	TF(4, "ABC\x88TFGH", TR(!is_latin_upper_letters_uint_(x)));
	/* */
	TF(1, "1bcdefgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(1, "\x88tcdefgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(2, "a1cdefgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(2, "a\x88tdefgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(3, "ab1defgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(3, "ab\x88tefgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(4, "abc1efgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(4, "abc\x88tfgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(1, "ABCDefgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(1, "ABCdefgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(1, "ABcDefgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(1, "ABcdefgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(1, "AbCDefgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(1, "AbCdefgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(1, "AbcDefgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(1, "Abcdefgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(2, "aBCDefgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(2, "aBCdefgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(2, "aBcDefgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(2, "aBcdefgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(3, "abCDefgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(3, "abCdefgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(4, "abcDefgh", TR(!is_latin_lower_letters_uint_(x)));
	TF(1, "abcdefgh", TR(is_latin_lower_letters_uint_(x)));
	/* */
	TF(1, "ABCDefgh", TR(is_latin_letters_uint_(x)));
	TF(1, "ABCdefgh", TR(is_latin_letters_uint_(x)));
	TF(1, "ABcDefgh", TR(is_latin_letters_uint_(x)));
	TF(1, "ABcdefgh", TR(is_latin_letters_uint_(x)));
	TF(1, "AbCDefgh", TR(is_latin_letters_uint_(x)));
	TF(1, "AbCdefgh", TR(is_latin_letters_uint_(x)));
	TF(1, "AbcDefgh", TR(is_latin_letters_uint_(x)));
	TF(1, "Abcdefgh", TR(is_latin_letters_uint_(x)));
	TF(1, "aBCDefgh", TR(is_latin_letters_uint_(x)));
	TF(1, "aBCdefgh", TR(is_latin_letters_uint_(x)));
	TF(1, "aBcDefgh", TR(is_latin_letters_uint_(x)));
	TF(1, "aBcdefgh", TR(is_latin_letters_uint_(x)));
	TF(1, "abCDefgh", TR(is_latin_letters_uint_(x)));
	TF(1, "abCdefgh", TR(is_latin_letters_uint_(x)));
	TF(1, "abcDefgh", TR(is_latin_letters_uint_(x)));
	TF(1, "abcdefgh", TR(is_latin_letters_uint_(x)));
	TF(1, "1bcdefgh", TR(!is_latin_letters_uint_(x)));
	TF(1, "\x88tcdefgh", TR(!is_latin_letters_uint_(x)));
	TF(2, "a1cdefgh", TR(!is_latin_letters_uint_(x)));
	TF(2, "a\x88tdefgh", TR(!is_latin_letters_uint_(x)));
	TF(3, "ab1defgh", TR(!is_latin_letters_uint_(x)));
	TF(3, "ab\x88tefgh", TR(!is_latin_letters_uint_(x)));
	TF(4, "abc1efgh", TR(!is_latin_letters_uint_(x)));
	TF(4, "abc\x88tfgh", TR(!is_latin_letters_uint_(x)));
	TF(1, "12cdefgh", TR(!is_latin_letters_uint_(x)));
	TF(1, "\x88tcdefgh", TR(!is_latin_letters_uint_(x)));
	TF(1, "1b2defgh", TR(!is_latin_letters_uint_(x)));
	TF(1, "\x88t2defgh", TR(!is_latin_letters_uint_(x)));
	TF(1, "1bc2efgh", TR(!is_latin_letters_uint_(x)));
	TF(1, "\x88tc2efgh", TR(!is_latin_letters_uint_(x)));
	TF(1, "123defgh", TR(!is_latin_letters_uint_(x)));
	TF(1, "\x88t3defgh", TR(!is_latin_letters_uint_(x)));
	TF(1, "12c3efgh", TR(!is_latin_letters_uint_(x)));
	TF(1, "\x88tc3efgh", TR(!is_latin_letters_uint_(x)));
	TF(1, "1234efgh", TR(!is_latin_letters_uint_(x)));
	TF(1, "\x88t34efgh", TR(!is_latin_letters_uint_(x)));
	/* */
	TF(1, "ABCDEFGH", x = latin_letters_to_lower_uint(x); TR(is_latin_lower_letters_uint_(x)));
	TF(1, "ABCdEFGH", x = latin_letters_to_lower_uint(x); TR(is_latin_lower_letters_uint_(x)));
	TF(1, "ABcDEFGH", x = latin_letters_to_lower_uint(x); TR(is_latin_lower_letters_uint_(x)));
	TF(1, "ABcdEFGH", x = latin_letters_to_lower_uint(x); TR(is_latin_lower_letters_uint_(x)));
	TF(1, "AbCDEFGH", x = latin_letters_to_lower_uint(x); TR(is_latin_lower_letters_uint_(x)));
	TF(1, "AbCdEFGH", x = latin_letters_to_lower_uint(x); TR(is_latin_lower_letters_uint_(x)));
	TF(1, "AbcDEFGH", x = latin_letters_to_lower_uint(x); TR(is_latin_lower_letters_uint_(x)));
	TF(1, "AbcdEFGH", x = latin_letters_to_lower_uint(x); TR(is_latin_lower_letters_uint_(x)));
	TF(1, "aBCDEFGH", x = latin_letters_to_lower_uint(x); TR(is_latin_lower_letters_uint_(x)));
	TF(1, "aBCdEFGH", x = latin_letters_to_lower_uint(x); TR(is_latin_lower_letters_uint_(x)));
	TF(1, "aBcDEFGH", x = latin_letters_to_lower_uint(x); TR(is_latin_lower_letters_uint_(x)));
	TF(1, "aBcdEFGH", x = latin_letters_to_lower_uint(x); TR(is_latin_lower_letters_uint_(x)));
	TF(1, "abCDEFGH", x = latin_letters_to_lower_uint(x); TR(is_latin_lower_letters_uint_(x)));
	TF(1, "abCdEFGH", x = latin_letters_to_lower_uint(x); TR(is_latin_lower_letters_uint_(x)));
	TF(1, "abcDEFGH", x = latin_letters_to_lower_uint(x); TR(is_latin_lower_letters_uint_(x)));
	TF(1, "abcdEFGH", x = latin_letters_to_lower_uint(x); TR(is_latin_lower_letters_uint_(x)));
	/* */
	TF(1, "ABCDEFGH", x = latin_letters_to_upper_uint(x); TR(is_latin_upper_letters_uint_(x)));
	TF(1, "ABCdEFGH", x = latin_letters_to_upper_uint(x); TR(is_latin_upper_letters_uint_(x)));
	TF(1, "ABcDEFGH", x = latin_letters_to_upper_uint(x); TR(is_latin_upper_letters_uint_(x)));
	TF(1, "ABcdEFGH", x = latin_letters_to_upper_uint(x); TR(is_latin_upper_letters_uint_(x)));
	TF(1, "AbCDEFGH", x = latin_letters_to_upper_uint(x); TR(is_latin_upper_letters_uint_(x)));
	TF(1, "AbCdEFGH", x = latin_letters_to_upper_uint(x); TR(is_latin_upper_letters_uint_(x)));
	TF(1, "AbcDEFGH", x = latin_letters_to_upper_uint(x); TR(is_latin_upper_letters_uint_(x)));
	TF(1, "AbcdEFGH", x = latin_letters_to_upper_uint(x); TR(is_latin_upper_letters_uint_(x)));
	TF(1, "aBCDEFGH", x = latin_letters_to_upper_uint(x); TR(is_latin_upper_letters_uint_(x)));
	TF(1, "aBCdEFGH", x = latin_letters_to_upper_uint(x); TR(is_latin_upper_letters_uint_(x)));
	TF(1, "aBcDEFGH", x = latin_letters_to_upper_uint(x); TR(is_latin_upper_letters_uint_(x)));
	TF(1, "aBcdEFGH", x = latin_letters_to_upper_uint(x); TR(is_latin_upper_letters_uint_(x)));
	TF(1, "abCDEFGH", x = latin_letters_to_upper_uint(x); TR(is_latin_upper_letters_uint_(x)));
	TF(1, "abCdEFGH", x = latin_letters_to_upper_uint(x); TR(is_latin_upper_letters_uint_(x)));
	TF(1, "abcDEFGH", x = latin_letters_to_upper_uint(x); TR(is_latin_upper_letters_uint_(x)));
	TF(1, "abcdEFGH", x = latin_letters_to_upper_uint(x); TR(is_latin_upper_letters_uint_(x)));
	/* */
	TF64(1, "ABCDEFGH", TR(is_latin_upper_letters_uint64_(x64)));
	TF64(4, "ABCdEFGH", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(3, "ABcDEFGH", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(3, "ABcdEFGH", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(2, "AbCDEFGH", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(2, "AbCdEFGH", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(2, "AbcDEFGH", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(2, "AbcdEFGH", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(1, "aBCDEFGH", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(1, "aBCdEFGH", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(1, "aBcDEFGH", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(1, "aBcdEFGH", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(1, "abCDEFGH", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(1, "abCdEFGH", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(1, "abcDEFGH", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(1, "abcdEFGH", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(1, "abcdefgh", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(8, "EFGHABCd", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(7, "EFGHABcD", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(7, "EFGHABcd", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(6, "EFGHAbCD", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(6, "EFGHAbCd", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(6, "EFGHAbcD", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(6, "EFGHAbcd", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(5, "EFGHaBCD", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(5, "EFGHaBCd", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(5, "EFGHaBcD", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(5, "EFGHaBcd", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(5, "EFGHabCD", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(5, "EFGHabCd", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(5, "EFGHabcD", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(5, "EFGHabcd", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(1, "1FGHABCD", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(1, "\x88TGHABCD", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(2, "E1GHABCD", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(2, "E\x88THABCD", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(3, "EF1HABCD", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(3, "EF\x88TABCD", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(4, "EFG1ABCD", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(4, "EFG\x88TBCD", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(5, "EFGH1BCD", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(5, "EFGH\x88TCD", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(6, "EFGHA1CD", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(6, "EFGHA\x88TD", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(7, "EFGHAB1D", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(7, "EFGHAB\x88T", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(8, "EFGHABC1", TR(!is_latin_upper_letters_uint64_(x64)));
	TF64(8, "EFGHABC\x88", TR(!is_latin_upper_letters_uint64_(x64)));
	/* */
	TF64(1, "1bcdefgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(1, "\x88tcdefgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(2, "a1cdefgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(2, "a\x88tdefgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(3, "ab1defgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(3, "ab\x88tefgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(4, "abc1efgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(4, "abc\x88tfgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(5, "abcd1fgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(5, "abcd\x88tgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(6, "abcde1gh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(6, "abcde\x88th", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(7, "abcdef1h", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(7, "abcdef\x88t", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(8, "abcdefg1", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(8, "abcdefg\x88", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(1, "ABCDEFGH", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(1, "ABCDefgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(1, "ABCdefgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(1, "ABcDefgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(1, "ABcdefgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(1, "AbCDefgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(1, "AbCdefgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(1, "AbcDefgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(1, "Abcdefgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(2, "aBCDefgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(2, "aBCdefgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(2, "aBcDefgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(2, "aBcdefgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(3, "abCDefgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(3, "abCdefgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(4, "abcDefgh", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(1, "abcdefgh", TR(is_latin_lower_letters_uint64_(x64)));
	TF64(5, "efghABCD", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(5, "efghABCd", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(5, "efghABcD", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(5, "efghABcd", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(5, "efghAbCD", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(5, "efghAbCd", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(5, "efghAbcD", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(5, "efghAbcd", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(6, "efghaBCD", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(6, "efghaBCd", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(6, "efghaBcD", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(6, "efghaBcd", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(7, "efghabCD", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(7, "efghabCd", TR(!is_latin_lower_letters_uint64_(x64)));
	TF64(8, "efghabcD", TR(!is_latin_lower_letters_uint64_(x64)));
	/* */
	TF64(1, "ABCDefgh", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "ABCdefgh", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "ABcDefgh", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "ABcdefgh", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "AbCDefgh", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "AbCdefgh", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "AbcDefgh", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "Abcdefgh", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "aBCDefgh", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "aBCdefgh", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "aBcDefgh", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "aBcdefgh", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "abCDefgh", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "abCdefgh", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "abcDefgh", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "abcdefgh", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "1bcdefgh", TR(!is_latin_letters_uint64_(x64)));
	TF64(1, "\x88tcdefgh", TR(!is_latin_letters_uint64_(x64)));
	TF64(2, "a1cdefgh", TR(!is_latin_letters_uint64_(x64)));
	TF64(2, "a\x88tdefgh", TR(!is_latin_letters_uint64_(x64)));
	TF64(3, "ab1defgh", TR(!is_latin_letters_uint64_(x64)));
	TF64(3, "ab\x88tefgh", TR(!is_latin_letters_uint64_(x64)));
	TF64(4, "abc1efgh", TR(!is_latin_letters_uint64_(x64)));
	TF64(4, "abc\x88tfgh", TR(!is_latin_letters_uint64_(x64)));
	TF64(1, "12cdefgh", TR(!is_latin_letters_uint64_(x64)));
	TF64(1, "\x88tcdefgh", TR(!is_latin_letters_uint64_(x64)));
	TF64(1, "1b2defgh", TR(!is_latin_letters_uint64_(x64)));
	TF64(1, "\x88t2defgh", TR(!is_latin_letters_uint64_(x64)));
	TF64(1, "1bc2efgh", TR(!is_latin_letters_uint64_(x64)));
	TF64(1, "\x88tc2efgh", TR(!is_latin_letters_uint64_(x64)));
	TF64(1, "123defgh", TR(!is_latin_letters_uint64_(x64)));
	TF64(1, "\x88t3defgh", TR(!is_latin_letters_uint64_(x64)));
	TF64(1, "12c3efgh", TR(!is_latin_letters_uint64_(x64)));
	TF64(1, "\x88tc3efgh", TR(!is_latin_letters_uint64_(x64)));
	TF64(1, "1234efgh", TR(!is_latin_letters_uint64_(x64)));
	TF64(1, "\x88t34efgh", TR(!is_latin_letters_uint64_(x64)));
	TF64(1, "efghABCD", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "efghABCd", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "efghABcD", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "efghABcd", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "efghAbCD", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "efghAbCd", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "efghAbcD", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "efghAbcd", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "efghaBCD", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "efghaBCd", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "efghaBcD", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "efghaBcd", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "efghabCD", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "efghabCd", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "efghabcD", TR(is_latin_letters_uint64_(x64)));
	TF64(1, "efghabcd", TR(is_latin_letters_uint64_(x64)));
	TF64(5, "efgh1bcd", TR(!is_latin_letters_uint64_(x64)));
	TF64(5, "efgh\x88tcd", TR(!is_latin_letters_uint64_(x64)));
	TF64(6, "efgha1cd", TR(!is_latin_letters_uint64_(x64)));
	TF64(6, "efgha\x88td", TR(!is_latin_letters_uint64_(x64)));
	TF64(7, "efghab1d", TR(!is_latin_letters_uint64_(x64)));
	TF64(7, "efghab\x88t", TR(!is_latin_letters_uint64_(x64)));
	TF64(8, "efghabc1", TR(!is_latin_letters_uint64_(x64)));
	TF64(8, "efghabc\x88", TR(!is_latin_letters_uint64_(x64)));
	TF64(5, "efgh12cd", TR(!is_latin_letters_uint64_(x64)));
	TF64(5, "efgh\x88tcd", TR(!is_latin_letters_uint64_(x64)));
	TF64(5, "efgh1b2d", TR(!is_latin_letters_uint64_(x64)));
	TF64(5, "efgh\x88t2d", TR(!is_latin_letters_uint64_(x64)));
	TF64(5, "efgh1bc2", TR(!is_latin_letters_uint64_(x64)));
	TF64(5, "efgh\x88tc2", TR(!is_latin_letters_uint64_(x64)));
	TF64(5, "efgh123d", TR(!is_latin_letters_uint64_(x64)));
	TF64(5, "efgh\x88t3d", TR(!is_latin_letters_uint64_(x64)));
	TF64(5, "efgh12c3", TR(!is_latin_letters_uint64_(x64)));
	TF64(5, "efgh\x88tc3", TR(!is_latin_letters_uint64_(x64)));
	TF64(5, "efgh1234", TR(!is_latin_letters_uint64_(x64)));
	TF64(5, "efgh\x88t34", TR(!is_latin_letters_uint64_(x64)));
	/* */
	TF64(1, "ABCDEFGH", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "ABCdEFGH", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "ABcDEFGH", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "ABcdEFGH", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "AbCDEFGH", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "AbCdEFGH", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "AbcDEFGH", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "AbcdEFGH", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "aBCDEFGH", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "aBCdEFGH", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "aBcDEFGH", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "aBcdEFGH", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "abCDEFGH", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "abCdEFGH", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "abcDEFGH", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "abcdEFGH", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "abcdefgh", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "EFGHABCd", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "EFGHABcD", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "EFGHABcd", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "EFGHAbCD", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "EFGHAbCd", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "EFGHAbcD", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "EFGHAbcd", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "EFGHaBCD", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "EFGHaBCd", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "EFGHaBcD", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "EFGHaBcd", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "EFGHabCD", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "EFGHabCd", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "EFGHabcD", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	TF64(1, "EFGHabcd", x64 = latin_letters_to_lower_uint64(x64); TR(is_latin_lower_letters_uint64_(x64)));
	/* */
	TF64(1, "ABCDEFGH", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "ABCdEFGH", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "ABcDEFGH", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "ABcdEFGH", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "AbCDEFGH", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "AbCdEFGH", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "AbcDEFGH", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "AbcdEFGH", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "aBCDEFGH", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "aBCdEFGH", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "aBcDEFGH", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "aBcdEFGH", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "abCDEFGH", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "abCdEFGH", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "abcDEFGH", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "abcdEFGH", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "abcdefgh", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "EFGHABCd", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "EFGHABcD", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "EFGHABcd", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "EFGHAbCD", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "EFGHAbCd", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "EFGHAbcD", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "EFGHAbcd", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "EFGHaBCD", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "EFGHaBCd", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "EFGHaBcD", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "EFGHaBcd", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "EFGHabCD", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "EFGHabCd", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "EFGHabcD", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	TF64(1, "EFGHabcd", x64 = latin_letters_to_upper_uint64(x64); TR(is_latin_upper_letters_uint64_(x64)));
	/* */
	TR(is_latin_upper_letter_w_(L'A'));
	TR(is_latin_upper_letter_w_(L'Z'));
	TR(!is_latin_upper_letter_w_(L'a'));
	TR(!is_latin_upper_letter_w_(L'z'));
	TR(!is_latin_upper_letter_w_(L'0'));
	TR(!is_latin_upper_letter_w_(L'9'));
	TR(!is_latin_upper_letter_w_(L' '));
	TR(!is_latin_upper_letter_w_(L'ы'));
	TR(!is_latin_upper_letter_w_(L'\0'));
	TR(!is_latin_upper_letter_w_(L'\xFF'));
	/* */
	TR(!is_latin_lower_letter_w_(L'A'));
	TR(!is_latin_lower_letter_w_(L'Z'));
	TR(is_latin_lower_letter_w_(L'a'));
	TR(is_latin_lower_letter_w_(L'z'));
	TR(!is_latin_lower_letter_w_(L'0'));
	TR(!is_latin_lower_letter_w_(L'9'));
	TR(!is_latin_lower_letter_w_(L' '));
	TR(!is_latin_lower_letter_w_(L'ы'));
	TR(!is_latin_lower_letter_w_(L'\0'));
	TR(!is_latin_lower_letter_w_(L'\xFF'));
	/* */
	TR(is_latin_letter_w_(L'A'));
	TR(is_latin_letter_w_(L'Z'));
	TR(is_latin_letter_w_(L'a'));
	TR(is_latin_letter_w_(L'z'));
	TR(!is_latin_letter_w_(L'0'));
	TR(!is_latin_letter_w_(L'9'));
	TR(!is_latin_letter_w_(L' '));
	TR(!is_latin_letter_w_(L'ы'));
	TR(!is_latin_letter_w_(L'\0'));
	TR(!is_latin_letter_w_(L'\xFF'));
	/* */
	TR(L'a' == latin_letter_to_lower_w(L'A'));
	TR(L'z' == latin_letter_to_lower_w(L'Z'));
	TR(L'a' == latin_letter_to_lower_w(L'a'));
	TR(L'z' == latin_letter_to_lower_w(L'z'));
	/* */
	TR(L'A' == latin_letter_to_upper_w(L'A'));
	TR(L'Z' == latin_letter_to_upper_w(L'Z'));
	TR(L'A' == latin_letter_to_upper_w(L'a'));
	TR(L'Z' == latin_letter_to_upper_w(L'z'));
	/* */
	TR(L'a' == latin_to_lower_w(L'A'));
	TR(L'z' == latin_to_lower_w(L'Z'));
	TR(L'a' == latin_to_lower_w(L'a'));
	TR(L'z' == latin_to_lower_w(L'z'));
	TR(L'0' == latin_to_lower_w(L'0'));
	TR(L'9' == latin_to_lower_w(L'9'));
	TR(L'ы' == latin_to_lower_w(L'ы'));
	TR(L'\0' == latin_to_lower_w(L'\0'));
	TR(L'\xFF' == latin_to_lower_w(L'\xFF'));
	/* */
	TR(L'A' == latin_to_upper_w(L'A'));
	TR(L'Z' == latin_to_upper_w(L'Z'));
	TR(L'A' == latin_to_upper_w(L'a'));
	TR(L'Z' == latin_to_upper_w(L'z'));
	TR(L'0' == latin_to_upper_w(L'0'));
	TR(L'9' == latin_to_upper_w(L'9'));
	TR(L'ы' == latin_to_upper_w(L'ы'));
	TR(L'\0' == latin_to_upper_w(L'\0'));
	TR(L'\xFF' == latin_to_upper_w(L'\xFF'));
	/* */
	TR(is_first_name_w_(L'A'));
	TR(is_first_name_w_(L'Z'));
	TR(is_first_name_w_(L'a'));
	TR(is_first_name_w_(L'z'));
	TR(!is_first_name_w_(L'0'));
	TR(!is_first_name_w_(L'9'));
	TR(!is_first_name_w_(L'ы'));
	TR(!is_first_name_w_(L'\0'));
	TR(!is_first_name_w_(L'\xFF'));
	TR(is_first_name_w_(L'_'));
	/* */
	TR(is_next_name_w_(L'A'));
	TR(is_next_name_w_(L'Z'));
	TR(is_next_name_w_(L'a'));
	TR(is_next_name_w_(L'z'));
	TR(is_next_name_w_(L'0'));
	TR(is_next_name_w_(L'9'));
	TR(!is_next_name_w_(L'ы'));
	TR(!is_next_name_w_(L'\0'));
	TR(!is_next_name_w_(L'\xFF'));
	TR(is_next_name_w_(L'_'));
	/* */
	TR(0 == digit_value_w(L'0'));
	TR(9 == digit_value_w(L'9'));
	/* */
	TR(!is_digit_w(L'A'));
	TR(!is_digit_w(L'Z'));
	TR(!is_digit_w(L'a'));
	TR(!is_digit_w(L'z'));
	TR(is_digit_w(L'0'));
	TR(is_digit_w(L'9'));
	TR(!is_digit_w(L'ы'));
	TR(!is_digit_w(L'\0'));
	TR(!is_digit_w(L'\xFF'));
	TR(!is_digit_w(L'_'));
	/* */
	TR(10 == hex_char_value_w_(L'A'));
	TR(15 == hex_char_value_w_(L'F'));
	TR(hex_char_value_w_(L'Z') > 15);
	TR(10 == hex_char_value_w_(L'a'));
	TR(15 == hex_char_value_w_(L'f'));
	TR(hex_char_value_w_(L'z') > 15);
	TR(0 == hex_char_value_w_(L'0'));
	TR(9 == hex_char_value_w_(L'9'));
	TR(hex_char_value_w_(L'ы') > 15);
	TR(hex_char_value_w_(L'\0') > 15);
	TR(hex_char_value_w_(L'\xFF') > 15);
	TR(hex_char_value_w_(L'_') > 15);
	/* */
	TFW(1, L"ABCDEFGH", TR(is_latin_upper_letters_uint_w_(x)));
	TFW(4, L"ABCdEFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	TFW(3, L"ABcDEFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	TFW(3, L"ABcdEFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	TFW(2, L"AbCDEFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	TFW(2, L"AbCdEFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	TFW(2, L"AbcDEFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	TFW(2, L"AbcdEFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"aBCDEFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"aBCdEFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"aBcDEFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"aBcdEFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"abCDEFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"abCdEFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"abcDEFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"abcdEFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"1BCDEFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"ыBCDEFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	TFW(2, L"A1CDEFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	TFW(2, L"AыCDEFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	TFW(3, L"AB1DEFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	TFW(3, L"ABыDEFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	TFW(4, L"ABC1EFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	TFW(4, L"ABCыEFGH", TR(!is_latin_upper_letters_uint_w_(x)));
	/* */
	TFW(1, L"1bcdefgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"ыbcdefgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(2, L"a1cdefgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(2, L"aыcdefgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(3, L"ab1defgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(3, L"abыdefgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(4, L"abc1efgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(4, L"abcыefgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"ABCDefgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"ABCdefgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"ABcDefgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"ABcdefgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"AbCDefgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"AbCdefgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"AbcDefgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"Abcdefgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(2, L"aBCDefgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(2, L"aBCdefgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(2, L"aBcDefgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(2, L"aBcdefgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(3, L"abCDefgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(3, L"abCdefgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(4, L"abcDefgh", TR(!is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"abcdefgh", TR(is_latin_lower_letters_uint_w_(x)));
	/* */
	TFW(1, L"ABCDefgh", TR(is_latin_letters_uint_w_(x)));
	TFW(1, L"ABCdefgh", TR(is_latin_letters_uint_w_(x)));
	TFW(1, L"ABcDefgh", TR(is_latin_letters_uint_w_(x)));
	TFW(1, L"ABcdefgh", TR(is_latin_letters_uint_w_(x)));
	TFW(1, L"AbCDefgh", TR(is_latin_letters_uint_w_(x)));
	TFW(1, L"AbCdefgh", TR(is_latin_letters_uint_w_(x)));
	TFW(1, L"AbcDefgh", TR(is_latin_letters_uint_w_(x)));
	TFW(1, L"Abcdefgh", TR(is_latin_letters_uint_w_(x)));
	TFW(1, L"aBCDefgh", TR(is_latin_letters_uint_w_(x)));
	TFW(1, L"aBCdefgh", TR(is_latin_letters_uint_w_(x)));
	TFW(1, L"aBcDefgh", TR(is_latin_letters_uint_w_(x)));
	TFW(1, L"aBcdefgh", TR(is_latin_letters_uint_w_(x)));
	TFW(1, L"abCDefgh", TR(is_latin_letters_uint_w_(x)));
	TFW(1, L"abCdefgh", TR(is_latin_letters_uint_w_(x)));
	TFW(1, L"abcDefgh", TR(is_latin_letters_uint_w_(x)));
	TFW(1, L"abcdefgh", TR(is_latin_letters_uint_w_(x)));
	TFW(1, L"1bcdefgh", TR(!is_latin_letters_uint_w_(x)));
	TFW(1, L"ыbcdefgh", TR(!is_latin_letters_uint_w_(x)));
	TFW(2, L"a1cdefgh", TR(!is_latin_letters_uint_w_(x)));
	TFW(2, L"aыcdefgh", TR(!is_latin_letters_uint_w_(x)));
	TFW(3, L"ab1defgh", TR(!is_latin_letters_uint_w_(x)));
	TFW(3, L"abыdefgh", TR(!is_latin_letters_uint_w_(x)));
	TFW(4, L"abc1efgh", TR(!is_latin_letters_uint_w_(x)));
	TFW(4, L"abcыefgh", TR(!is_latin_letters_uint_w_(x)));
	TFW(1, L"12cdefgh", TR(!is_latin_letters_uint_w_(x)));
	TFW(1, L"ы2cdefgh", TR(!is_latin_letters_uint_w_(x)));
	TFW(1, L"1b2defgh", TR(!is_latin_letters_uint_w_(x)));
	TFW(1, L"ыb2defgh", TR(!is_latin_letters_uint_w_(x)));
	TFW(1, L"1bc2efgh", TR(!is_latin_letters_uint_w_(x)));
	TFW(1, L"ыbc2efgh", TR(!is_latin_letters_uint_w_(x)));
	TFW(1, L"123defgh", TR(!is_latin_letters_uint_w_(x)));
	TFW(1, L"ы23defgh", TR(!is_latin_letters_uint_w_(x)));
	TFW(1, L"12c3efgh", TR(!is_latin_letters_uint_w_(x)));
	TFW(1, L"ы2c3efgh", TR(!is_latin_letters_uint_w_(x)));
	TFW(1, L"1234efgh", TR(!is_latin_letters_uint_w_(x)));
	TFW(1, L"ы234efgh", TR(!is_latin_letters_uint_w_(x)));
	/* */
	TFW(1, L"ABCDEFGH", x = latin_letters_to_lower_uint_w(x); TR(is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"ABCdEFGH", x = latin_letters_to_lower_uint_w(x); TR(is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"ABcDEFGH", x = latin_letters_to_lower_uint_w(x); TR(is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"ABcdEFGH", x = latin_letters_to_lower_uint_w(x); TR(is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"AbCDEFGH", x = latin_letters_to_lower_uint_w(x); TR(is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"AbCdEFGH", x = latin_letters_to_lower_uint_w(x); TR(is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"AbcDEFGH", x = latin_letters_to_lower_uint_w(x); TR(is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"AbcdEFGH", x = latin_letters_to_lower_uint_w(x); TR(is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"aBCDEFGH", x = latin_letters_to_lower_uint_w(x); TR(is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"aBCdEFGH", x = latin_letters_to_lower_uint_w(x); TR(is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"aBcDEFGH", x = latin_letters_to_lower_uint_w(x); TR(is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"aBcdEFGH", x = latin_letters_to_lower_uint_w(x); TR(is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"abCDEFGH", x = latin_letters_to_lower_uint_w(x); TR(is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"abCdEFGH", x = latin_letters_to_lower_uint_w(x); TR(is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"abcDEFGH", x = latin_letters_to_lower_uint_w(x); TR(is_latin_lower_letters_uint_w_(x)));
	TFW(1, L"abcdEFGH", x = latin_letters_to_lower_uint_w(x); TR(is_latin_lower_letters_uint_w_(x)));
	/* */
	TFW(1, L"ABCDEFGH", x = latin_letters_to_upper_uint_w(x); TR(is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"ABCdEFGH", x = latin_letters_to_upper_uint_w(x); TR(is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"ABcDEFGH", x = latin_letters_to_upper_uint_w(x); TR(is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"ABcdEFGH", x = latin_letters_to_upper_uint_w(x); TR(is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"AbCDEFGH", x = latin_letters_to_upper_uint_w(x); TR(is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"AbCdEFGH", x = latin_letters_to_upper_uint_w(x); TR(is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"AbcDEFGH", x = latin_letters_to_upper_uint_w(x); TR(is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"AbcdEFGH", x = latin_letters_to_upper_uint_w(x); TR(is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"aBCDEFGH", x = latin_letters_to_upper_uint_w(x); TR(is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"aBCdEFGH", x = latin_letters_to_upper_uint_w(x); TR(is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"aBcDEFGH", x = latin_letters_to_upper_uint_w(x); TR(is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"aBcdEFGH", x = latin_letters_to_upper_uint_w(x); TR(is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"abCDEFGH", x = latin_letters_to_upper_uint_w(x); TR(is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"abCdEFGH", x = latin_letters_to_upper_uint_w(x); TR(is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"abcDEFGH", x = latin_letters_to_upper_uint_w(x); TR(is_latin_upper_letters_uint_w_(x)));
	TFW(1, L"abcdEFGH", x = latin_letters_to_upper_uint_w(x); TR(is_latin_upper_letters_uint_w_(x)));
	/* */
	TF64W(1, L"ABCDEFGH", TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(4, L"ABCdEFGH", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(3, L"ABcDEFGH", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(3, L"ABcdEFGH", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(2, L"AbCDEFGH", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(2, L"AbCdEFGH", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(2, L"AbcDEFGH", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(2, L"AbcdEFGH", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"aBCDEFGH", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"aBCdEFGH", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"aBcDEFGH", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"aBcdEFGH", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"abCDEFGH", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"abCdEFGH", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"abcDEFGH", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"abcdEFGH", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"abcdefgh", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(8, L"EFGHABCd", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(7, L"EFGHABcD", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(7, L"EFGHABcd", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(6, L"EFGHAbCD", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(6, L"EFGHAbCd", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(6, L"EFGHAbcD", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(6, L"EFGHAbcd", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(5, L"EFGHaBCD", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(5, L"EFGHaBCd", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(5, L"EFGHaBcD", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(5, L"EFGHaBcd", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(5, L"EFGHabCD", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(5, L"EFGHabCd", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(5, L"EFGHabcD", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(5, L"EFGHabcd", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"1FGHABCD", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"ыFGHABCD", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(2, L"E1GHABCD", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(2, L"EыGHABCD", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(3, L"EF1HABCD", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(3, L"EFыHABCD", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(4, L"EFG1ABCD", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(4, L"EFGыABCD", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(5, L"EFGH1BCD", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(5, L"EFGHыBCD", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(6, L"EFGHA1CD", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(6, L"EFGHAыCD", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(7, L"EFGHAB1D", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(7, L"EFGHABыD", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(8, L"EFGHABC1", TR(!is_latin_upper_letters_uint64_w_(x64)));
	TF64W(8, L"EFGHABCы", TR(!is_latin_upper_letters_uint64_w_(x64)));
	/* */
	TF64W(1, L"1bcdefgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"ыbcdefgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(2, L"a1cdefgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(2, L"aыcdefgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(3, L"ab1defgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(3, L"abыdefgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(4, L"abc1efgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(4, L"abcыefgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(5, L"abcd1fgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(5, L"abcdыfgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(6, L"abcde1gh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(6, L"abcdeыgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(7, L"abcdef1h", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(7, L"abcdefыh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(8, L"abcdefg1", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(8, L"abcdefgы", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"ABCDEFGH", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"ABCDefgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"ABCdefgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"ABcDefgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"ABcdefgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"AbCDefgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"AbCdefgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"AbcDefgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"Abcdefgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(2, L"aBCDefgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(2, L"aBCdefgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(2, L"aBcDefgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(2, L"aBcdefgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(3, L"abCDefgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(3, L"abCdefgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(4, L"abcDefgh", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"abcdefgh", TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(5, L"efghABCD", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(5, L"efghABCd", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(5, L"efghABcD", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(5, L"efghABcd", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(5, L"efghAbCD", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(5, L"efghAbCd", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(5, L"efghAbcD", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(5, L"efghAbcd", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(6, L"efghaBCD", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(6, L"efghaBCd", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(6, L"efghaBcD", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(6, L"efghaBcd", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(7, L"efghabCD", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(7, L"efghabCd", TR(!is_latin_lower_letters_uint64_w_(x64)));
	TF64W(8, L"efghabcD", TR(!is_latin_lower_letters_uint64_w_(x64)));
	/* */
	TF64W(1, L"ABCDefgh", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"ABCdefgh", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"ABcDefgh", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"ABcdefgh", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"AbCDefgh", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"AbCdefgh", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"AbcDefgh", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"Abcdefgh", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"aBCDefgh", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"aBCdefgh", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"aBcDefgh", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"aBcdefgh", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"abCDefgh", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"abCdefgh", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"abcDefgh", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"abcdefgh", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"1bcdefgh", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"ыbcdefgh", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(2, L"a1cdefgh", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(2, L"aыcdefgh", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(3, L"ab1defgh", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(3, L"abыdefgh", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(4, L"abc1efgh", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(4, L"abcыefgh", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"12cdefgh", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"ы2cdefgh", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"1b2defgh", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"ыb2defgh", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"1bc2efgh", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"ыbc2efgh", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"123defgh", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"ы23defgh", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"12c3efgh", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"ы2c3efgh", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"1234efgh", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"ы234efgh", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"efghABCD", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"efghABCd", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"efghABcD", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"efghABcd", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"efghAbCD", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"efghAbCd", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"efghAbcD", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"efghAbcd", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"efghaBCD", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"efghaBCd", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"efghaBcD", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"efghaBcd", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"efghabCD", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"efghabCd", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"efghabcD", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(1, L"efghabcd", TR(is_latin_letters_uint64_w_(x64)));
	TF64W(5, L"efgh1bcd", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(5, L"efghыbcd", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(6, L"efgha1cd", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(6, L"efghaыcd", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(7, L"efghab1d", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(7, L"efghabыd", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(8, L"efghabc1", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(8, L"efghabcы", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(5, L"efgh12cd", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(5, L"efghы2cd", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(5, L"efgh1b2d", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(5, L"efghыb2d", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(5, L"efgh1bc2", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(5, L"efghыbc2", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(5, L"efgh123d", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(5, L"efghы23d", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(5, L"efgh12c3", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(5, L"efghы2c3", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(5, L"efgh1234", TR(!is_latin_letters_uint64_w_(x64)));
	TF64W(5, L"efghы234", TR(!is_latin_letters_uint64_w_(x64)));
	/* */
	TF64W(1, L"ABCDEFGH", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"ABCdEFGH", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"ABcDEFGH", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"ABcdEFGH", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"AbCDEFGH", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"AbCdEFGH", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"AbcDEFGH", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"AbcdEFGH", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"aBCDEFGH", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"aBCdEFGH", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"aBcDEFGH", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"aBcdEFGH", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"abCDEFGH", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"abCdEFGH", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"abcDEFGH", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"abcdEFGH", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"abcdefgh", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHABCd", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHABcD", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHABcd", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHAbCD", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHAbCd", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHAbcD", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHAbcd", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHaBCD", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHaBCd", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHaBcD", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHaBcd", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHabCD", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHabCd", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHabcD", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHabcd", x64 = latin_letters_to_lower_uint64_w(x64); TR(is_latin_lower_letters_uint64_w_(x64)));
	/* */
	TF64W(1, L"ABCDEFGH", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"ABCdEFGH", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"ABcDEFGH", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"ABcdEFGH", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"AbCDEFGH", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"AbCdEFGH", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"AbcDEFGH", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"AbcdEFGH", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"aBCDEFGH", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"aBCdEFGH", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"aBcDEFGH", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"aBcdEFGH", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"abCDEFGH", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"abCdEFGH", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"abcDEFGH", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"abcdEFGH", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"abcdefgh", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHABCd", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHABcD", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHABcd", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHAbCD", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHAbCd", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHAbcD", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHAbcd", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHaBCD", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHaBCd", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHaBcD", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHaBcd", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHabCD", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHabCd", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHabcD", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	TF64W(1, L"EFGHabcd", x64 = latin_letters_to_upper_uint64_w(x64); TR(is_latin_upper_letters_uint64_w_(x64)));
	/* */
#define GT_UINT_CONTAINS_ZERO(char_type, uint_type, c, r) do {GT_UINT_ALL_NOZERO(char_type, uint_type, c, r); r = !r;} while (0)
	TF(1, "\x88t34", do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned, x, r); TR(!r);} while (0));
	TF(1, "1234", do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned, x, r); TR(!r);} while (0));
	TF(1, "abcd", do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned, x, r); TR(!r);} while (0));
	TF(1, "ABCD", do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned, x, r); TR(!r);} while (0));
	TF(1, "\0\0\0\0", do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned, x, r); TR(r);} while (0));
	TF(1, "\0\0\0z",  do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned, x, r); TR(r);} while (0));
	TF(1, "\0\0z\0",  do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned, x, r); TR(r);} while (0));
	TF(1, "\0\0zz",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned, x, r); TR(r);} while (0));
	TF(1, "\0z\0\0",  do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned, x, r); TR(r);} while (0));
	TF(1, "\0z\0z",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned, x, r); TR(r);} while (0));
	TF(1, "\0zz\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned, x, r); TR(r);} while (0));
	TF(1, "\0zzz",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned, x, r); TR(r);} while (0));
	TF(2, "\x88\0\0\0",  do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned, x, r); TR(r);} while (0));
	TF(2, "\x88\0\0z",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned, x, r); TR(r);} while (0));
	TF(2, "\x88\0z\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned, x, r); TR(r);} while (0));
	TF(2, "\x88\0zz",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned, x, r); TR(r);} while (0));
	TF(3, "\x88z\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned, x, r); TR(r);} while (0));
	TF(3, "\x88z\0z",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned, x, r); TR(r);} while (0));
	TF(4, "\x88zz\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned, x, r); TR(r);} while (0));
	TF(1, "\x88zzz",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned, x, r); TR(!r);} while (0));
	/* */
	TF64(1, "\x88t345678", do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(!r);} while (0));
	TF64(1, "12345678", do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(!r);} while (0));
	TF64(1, "abcdefgh", do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(!r);} while (0));
	TF64(1, "ABCDEFGH", do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(!r);} while (0));
	TF64(1, "\0\0\0\0\0\0\0\0", do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0\0\0\0\0z",  do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0\0\0\0z\0",  do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0\0\0\0zz",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0\0\0z\0\0",  do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0\0\0z\0z",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0\0\0zz\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0\0\0zzz",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0\0t\0\0\0",  do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0\0t\0\0z",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0\0t\0z\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0\0t\0zz",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0\0tz\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0\0tz\0z",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0\0tzz\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0\0tzzz",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0z\0\0\0\0",  do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0z\0\0\0z",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0z\0\0z\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0z\0\0zz",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0z\0z\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0z\0z\0z",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0z\0zz\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0z\0zzz",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0zt\0\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0zt\0\0z",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0zt\0z\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0zt\0zz",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0ztz\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0ztz\0z",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0ztzz\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0\0ztzzz",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0k\0\0\0\0\0",  do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0k\0\0\0\0z",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0k\0\0\0z\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0k\0\0\0zz",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0k\0\0z\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0k\0\0z\0z",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0k\0\0zz\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0k\0\0zzz",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0k\0t\0\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0k\0t\0\0z",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0k\0t\0z\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0k\0t\0zz",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0k\0tz\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0k\0tz\0z",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0k\0tzz\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0k\0tzzz",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0kz\0\0\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0kz\0\0\0z",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0kz\0\0z\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0kz\0\0zz",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0kz\0z\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0kz\0z\0z",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0kz\0zz\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0kz\0zzz",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0kzt\0\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0kzt\0\0z",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0kzt\0z\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0kzt\0zz",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0kztz\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0kztz\0z",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0kztzz\0",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0\0kztzzz",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0\0\0\0\0\0",  do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0\0\0\0\0z",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0\0\0\0z\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0\0\0\0zz",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0\0\0z\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0\0\0z\0z",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0\0\0zz\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0\0\0zzz",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0\0t\0\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0\0t\0\0z",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0\0t\0z\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0\0t\0zz",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0\0tz\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0\0tz\0z",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0\0tzz\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0\0tzzz",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0z\0\0\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0z\0\0\0z",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0z\0\0z\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0z\0\0zz",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0z\0z\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0z\0z\0z",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0z\0zz\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0z\0zzz",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0zt\0\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0zt\0\0z",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0zt\0z\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0zt\0zz",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0ztz\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0ztz\0z",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0ztzz\0",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0m\0ztzzz",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mk\0\0\0\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mk\0\0\0\0z",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mk\0\0\0z\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mk\0\0\0zz",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mk\0\0z\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mk\0\0z\0z",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mk\0\0zz\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mk\0\0zzz",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mk\0t\0\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mk\0t\0\0z",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mk\0t\0z\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mk\0t\0zz",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mk\0tz\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mk\0tz\0z",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mk\0tzz\0",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mk\0tzzz",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mkz\0\0\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mkz\0\0\0z",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mkz\0\0z\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mkz\0\0zz",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mkz\0z\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mkz\0z\0z",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mkz\0zz\0",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mkz\0zzz",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mkzt\0\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mkzt\0\0z",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mkzt\0z\0",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mkzt\0zz",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mkztz\0\0",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mkztz\0z",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mkztzz\0",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\0mkztzzz",        do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0\0\0\0\0\0",  do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0\0\0\0\0z",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0\0\0\0z\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0\0\0\0zz",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0\0\0z\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0\0\0z\0z",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0\0\0zz\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0\0\0zzz",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0\0t\0\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0\0t\0\0z",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0\0t\0z\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0\0t\0zz",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0\0tz\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0\0tz\0z",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0\0tzz\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0\0tzzz",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0z\0\0\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0z\0\0\0z",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0z\0\0z\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0z\0\0zz",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0z\0z\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0z\0z\0z",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0z\0zz\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0z\0zzz",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0zt\0\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0zt\0\0z",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0zt\0z\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0zt\0zz",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0ztz\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0ztz\0z",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0ztzz\0",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0\0ztzzz",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0k\0\0\0\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0k\0\0\0\0z",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0k\0\0\0z\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0k\0\0\0zz",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0k\0\0z\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0k\0\0z\0z",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0k\0\0zz\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0k\0\0zzz",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0k\0t\0\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0k\0t\0\0z",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0k\0t\0z\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0k\0t\0zz",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0k\0tz\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0k\0tz\0z",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0k\0tzz\0",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0k\0tzzz",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0kz\0\0\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0kz\0\0\0z",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0kz\0\0z\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0kz\0\0zz",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0kz\0z\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0kz\0z\0z",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0kz\0zz\0",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0kz\0zzz",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0kzt\0\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0kzt\0\0z",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0kzt\0z\0",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0kzt\0zz",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0kztz\0\0",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0kztz\0z",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0kztzz\0",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(2, "\x88\0kztzzz",        do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0\0\0\0\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0\0\0\0\0z",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0\0\0\0z\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0\0\0\0zz",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0\0\0z\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0\0\0z\0z",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0\0\0zz\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0\0\0zzz",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0\0t\0\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0\0t\0\0z",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0\0t\0z\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0\0t\0zz",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0\0tz\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0\0tz\0z",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0\0tzz\0",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0\0tzzz",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0z\0\0\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0z\0\0\0z",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0z\0\0z\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0z\0\0zz",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0z\0z\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0z\0z\0z",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0z\0zz\0",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0z\0zzz",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0zt\0\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0zt\0\0z",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0zt\0z\0",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0zt\0zz",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0ztz\0\0",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0ztz\0z",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0ztzz\0",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(3, "\x88m\0ztzzz",        do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(4, "\x88mk\0\0\0\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(4, "\x88mk\0\0\0\0z",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(4, "\x88mk\0\0\0z\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(4, "\x88mk\0\0\0zz",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(4, "\x88mk\0\0z\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(4, "\x88mk\0\0z\0z",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(4, "\x88mk\0\0zz\0",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(4, "\x88mk\0\0zzz",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(4, "\x88mk\0t\0\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(4, "\x88mk\0t\0\0z",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(4, "\x88mk\0t\0z\0",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(4, "\x88mk\0t\0zz",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(4, "\x88mk\0tz\0\0",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(4, "\x88mk\0tz\0z",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(4, "\x88mk\0tzz\0",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(4, "\x88mk\0tzzz",        do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(5, "\x88mkz\0\0\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(5, "\x88mkz\0\0\0z",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(5, "\x88mkz\0\0z\0",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(5, "\x88mkz\0\0zz",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(5, "\x88mkz\0z\0\0",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(5, "\x88mkz\0z\0z",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(5, "\x88mkz\0zz\0",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(5, "\x88mkz\0zzz",        do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(6, "\x88mkzt\0\0\0",      do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(6, "\x88mkzt\0\0z",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(6, "\x88mkzt\0z\0",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(6, "\x88mkzt\0zz",        do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(7, "\x88mkztz\0\0",       do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(7, "\x88mkztz\0z",        do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(8, "\x88mkztzz\0",        do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64(1, "\x88mkztzzz",         do {int r; GT_UINT_CONTAINS_ZERO(char, unsigned INT64_TYPE, x64, r); TR(!r);} while (0));
	/* */
	TFW(1, L"ы234", do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned, x, r); TR(!r);} while (0));
	TFW(1, L"1234", do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned, x, r); TR(!r);} while (0));
	TFW(1, L"abcd", do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned, x, r); TR(!r);} while (0));
	TFW(1, L"ABCD", do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned, x, r); TR(!r);} while (0));
	TFW(1, L"\0\0\0\0", do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned, x, r); TR(r);} while (0));
	TFW(1, L"\0\0\0z",  do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned, x, r); TR(r);} while (0));
	TFW(1, L"\0\0z\0",  do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned, x, r); TR(r);} while (0));
	TFW(1, L"\0\0zz",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned, x, r); TR(r);} while (0));
	TFW(1, L"\0z\0\0",  do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned, x, r); TR(r);} while (0));
	TFW(1, L"\0z\0z",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned, x, r); TR(r);} while (0));
	TFW(1, L"\0zz\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned, x, r); TR(r);} while (0));
	TFW(1, L"\0zzz",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned, x, r); TR(r);} while (0));
	TFW(2, L"ы\0\0\0",  do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned, x, r); TR(r);} while (0));
	TFW(2, L"ы\0\0z",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned, x, r); TR(r);} while (0));
	TFW(2, L"ы\0z\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned, x, r); TR(r);} while (0));
	TFW(2, L"ы\0zz",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned, x, r); TR(r);} while (0));
	TFW(3, L"ыz\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned, x, r); TR(r);} while (0));
	TFW(3, L"ыz\0z",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned, x, r); TR(r);} while (0));
	TFW(4, L"ыzz\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned, x, r); TR(r);} while (0));
	TFW(1, L"ыzzz",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned, x, r); TR(!r);} while (0));
	/* */
	TF64W(1, L"ы2345678", do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(!r);} while (0));
	TF64W(1, L"12345678", do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(!r);} while (0));
	TF64W(1, L"abcdefgh", do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(!r);} while (0));
	TF64W(1, L"ABCDEFGH", do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(!r);} while (0));
	TF64W(1, L"\0\0\0\0\0\0\0\0", do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0\0\0\0\0z",  do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0\0\0\0z\0",  do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0\0\0\0zz",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0\0\0z\0\0",  do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0\0\0z\0z",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0\0\0zz\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0\0\0zzz",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0\0t\0\0\0",  do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0\0t\0\0z",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0\0t\0z\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0\0t\0zz",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0\0tz\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0\0tz\0z",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0\0tzz\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0\0tzzz",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0z\0\0\0\0",  do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0z\0\0\0z",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0z\0\0z\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0z\0\0zz",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0z\0z\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0z\0z\0z",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0z\0zz\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0z\0zzz",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0zt\0\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0zt\0\0z",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0zt\0z\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0zt\0zz",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0ztz\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0ztz\0z",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0ztzz\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0\0ztzzz",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0k\0\0\0\0\0",  do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0k\0\0\0\0z",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0k\0\0\0z\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0k\0\0\0zz",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0k\0\0z\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0k\0\0z\0z",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0k\0\0zz\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0k\0\0zzz",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0k\0t\0\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0k\0t\0\0z",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0k\0t\0z\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0k\0t\0zz",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0k\0tz\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0k\0tz\0z",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0k\0tzz\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0k\0tzzz",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0kz\0\0\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0kz\0\0\0z",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0kz\0\0z\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0kz\0\0zz",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0kz\0z\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0kz\0z\0z",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0kz\0zz\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0kz\0zzz",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0kzt\0\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0kzt\0\0z",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0kzt\0z\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0kzt\0zz",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0kztz\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0kztz\0z",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0kztzz\0",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0\0kztzzz",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0\0\0\0\0\0",  do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0\0\0\0\0z",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0\0\0\0z\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0\0\0\0zz",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0\0\0z\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0\0\0z\0z",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0\0\0zz\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0\0\0zzz",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0\0t\0\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0\0t\0\0z",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0\0t\0z\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0\0t\0zz",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0\0tz\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0\0tz\0z",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0\0tzz\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0\0tzzz",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0z\0\0\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0z\0\0\0z",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0z\0\0z\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0z\0\0zz",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0z\0z\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0z\0z\0z",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0z\0zz\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0z\0zzz",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0zt\0\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0zt\0\0z",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0zt\0z\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0zt\0zz",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0ztz\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0ztz\0z",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0ztzz\0",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0m\0ztzzz",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mk\0\0\0\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mk\0\0\0\0z",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mk\0\0\0z\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mk\0\0\0zz",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mk\0\0z\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mk\0\0z\0z",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mk\0\0zz\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mk\0\0zzz",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mk\0t\0\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mk\0t\0\0z",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mk\0t\0z\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mk\0t\0zz",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mk\0tz\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mk\0tz\0z",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mk\0tzz\0",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mk\0tzzz",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mkz\0\0\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mkz\0\0\0z",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mkz\0\0z\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mkz\0\0zz",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mkz\0z\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mkz\0z\0z",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mkz\0zz\0",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mkz\0zzz",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mkzt\0\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mkzt\0\0z",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mkzt\0z\0",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mkzt\0zz",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mkztz\0\0",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mkztz\0z",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mkztzz\0",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"\0mkztzzz",        do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0\0\0\0\0\0",  do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0\0\0\0\0z",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0\0\0\0z\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0\0\0\0zz",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0\0\0z\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0\0\0z\0z",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0\0\0zz\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0\0\0zzz",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0\0t\0\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0\0t\0\0z",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0\0t\0z\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0\0t\0zz",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0\0tz\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0\0tz\0z",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0\0tzz\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0\0tzzz",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0z\0\0\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0z\0\0\0z",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0z\0\0z\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0z\0\0zz",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0z\0z\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0z\0z\0z",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0z\0zz\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0z\0zzz",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0zt\0\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0zt\0\0z",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0zt\0z\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0zt\0zz",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0ztz\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0ztz\0z",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0ztzz\0",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0\0ztzzz",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0k\0\0\0\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0k\0\0\0\0z",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0k\0\0\0z\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0k\0\0\0zz",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0k\0\0z\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0k\0\0z\0z",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0k\0\0zz\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0k\0\0zzz",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0k\0t\0\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0k\0t\0\0z",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0k\0t\0z\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0k\0t\0zz",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0k\0tz\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0k\0tz\0z",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0k\0tzz\0",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0k\0tzzz",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0kz\0\0\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0kz\0\0\0z",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0kz\0\0z\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0kz\0\0zz",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0kz\0z\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0kz\0z\0z",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0kz\0zz\0",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0kz\0zzz",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0kzt\0\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0kzt\0\0z",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0kzt\0z\0",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0kzt\0zz",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0kztz\0\0",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0kztz\0z",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0kztzz\0",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(2, L"ы\0kztzzz",        do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0\0\0\0\0\0",   do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0\0\0\0\0z",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0\0\0\0z\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0\0\0\0zz",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0\0\0z\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0\0\0z\0z",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0\0\0zz\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0\0\0zzz",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0\0t\0\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0\0t\0\0z",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0\0t\0z\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0\0t\0zz",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0\0tz\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0\0tz\0z",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0\0tzz\0",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0\0tzzz",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0z\0\0\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0z\0\0\0z",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0z\0\0z\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0z\0\0zz",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0z\0z\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0z\0z\0z",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0z\0zz\0",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0z\0zzz",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0zt\0\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0zt\0\0z",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0zt\0z\0",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0zt\0zz",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0ztz\0\0",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0ztz\0z",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0ztzz\0",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(3, L"ыm\0ztzzz",        do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(4, L"ыmk\0\0\0\0\0",    do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(4, L"ыmk\0\0\0\0z",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(4, L"ыmk\0\0\0z\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(4, L"ыmk\0\0\0zz",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(4, L"ыmk\0\0z\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(4, L"ыmk\0\0z\0z",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(4, L"ыmk\0\0zz\0",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(4, L"ыmk\0\0zzz",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(4, L"ыmk\0t\0\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(4, L"ыmk\0t\0\0z",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(4, L"ыmk\0t\0z\0",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(4, L"ыmk\0t\0zz",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(4, L"ыmk\0tz\0\0",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(4, L"ыmk\0tz\0z",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(4, L"ыmk\0tzz\0",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(4, L"ыmk\0tzzz",        do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(5, L"ыmkz\0\0\0\0",     do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(5, L"ыmkz\0\0\0z",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(5, L"ыmkz\0\0z\0",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(5, L"ыmkz\0\0zz",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(5, L"ыmkz\0z\0\0",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(5, L"ыmkz\0z\0z",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(5, L"ыmkz\0zz\0",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(5, L"ыmkz\0zzz",        do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(6, L"ыmkzt\0\0\0",      do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(6, L"ыmkzt\0\0z",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(6, L"ыmkzt\0z\0",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(6, L"ыmkzt\0zz",        do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(7, L"ыmkztz\0\0",       do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(7, L"ыmkztz\0z",        do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(8, L"ыmkztzz\0",        do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(r);} while (0));
	TF64W(1, L"ыmkztzzz",         do {int r; GT_UINT_CONTAINS_ZERO(wchar_t, unsigned INT64_TYPE, x64, r); TR(!r);} while (0));
	/* */
	{
		unsigned n = 0;
		unsigned f = 0;
		while (n < 10 || f < 10) {
			int r;
			const char z = (char)((unsigned char)-1 & (unsigned)rand());
			if (GT_CHAR_TO_UINT(char, z) & GT_CHAR_TYPE_TOP_BIT(char))
				continue;
			{
				unsigned q = 0;
				for (; q < sizeof(x); q++)
					((unsigned char*)&x)[q] = (unsigned char)((unsigned char)-1 & (unsigned)rand());
			}
			GT_UINT_ALL_GE_(char, unsigned, z, x, r);
			{
				int r2 = 1; /* assume all chars are >= z */
				unsigned q = 0;
				for (; q < sizeof(x); q++) {
					if ((unsigned char)((const char*)&x)[q] < (unsigned char)z)
						r2 = 0;
				}
				TR(!r == !r2);
			}
			if (r)
				n++;
			else
				f++;
		}
	}
	/* */
	{
		unsigned n = 0;
		unsigned f = 0;
		while (n < 10 || f < 10) {
			int r;
			const char z = (char)((unsigned char)-1 & (unsigned)rand());
			if (GT_CHAR_TO_UINT(char, z) & GT_CHAR_TYPE_TOP_BIT(char))
				continue;
			{
				unsigned q = 0;
				for (; q < sizeof(x64); q++)
					((unsigned char*)&x64)[q] = (unsigned char)((unsigned char)-1 & (unsigned)rand());
			}
			GT_UINT_ALL_GE_(char, unsigned INT64_TYPE, z, x64, r);
			{
				int r2 = 1; /* assume all chars are >= z */
				unsigned q = 0;
				for (; q < sizeof(x64); q++) {
					if ((unsigned char)((const char*)&x64)[q] < (unsigned char)z)
						r2 = 0;
				}
				TR(!r == !r2);
			}
			if (r)
				n++;
			else
				f++;
		}
	}
	/* */
	{
		unsigned n = 0;
		unsigned f = 0;
		while (n < 10 || f < 10) {
			int r;
			wchar_t z;
			{
				unsigned q = 0;
				for (; q < sizeof(z); q++)
					((unsigned char*)&z)[q] = (unsigned char)((unsigned char)-1 & (unsigned)rand());
			}
			if (GT_CHAR_TO_UINT(wchar_t, z) & GT_CHAR_TYPE_TOP_BIT(wchar_t))
				continue;
			{
				unsigned q = 0;
				for (; q < sizeof(x); q++)
					((unsigned char*)&x)[q] = (unsigned char)((unsigned char)-1 & (unsigned)rand());
			}
			GT_UINT_ALL_GE_(wchar_t, unsigned, z, x, r);
			{
				int r2 = 1; /* assume all chars are >= z */
				unsigned q = 0;
				for (; q < sizeof(x)/sizeof(wchar_t); q++) {
					if (GT_CHAR_TO_UINT(wchar_t, ((const wchar_t*)&x)[q]) < GT_CHAR_TO_UINT(wchar_t, z))
						r2 = 0;
				}
				TR(!r == !r2);
			}
			if (r)
				n++;
			else
				f++;
		}
	}
	/* */
	{
		unsigned n = 0;
		unsigned f = 0;
		while (n < 10 || f < 10) {
			int r;
			wchar_t z;
			{
				unsigned q = 0;
				for (; q < sizeof(z); q++)
					((unsigned char*)&z)[q] = (unsigned char)((unsigned char)-1 & (unsigned)rand());
			}
			if (GT_CHAR_TO_UINT(wchar_t, z) & GT_CHAR_TYPE_TOP_BIT(wchar_t))
				continue;
			{
				unsigned q = 0;
				for (; q < sizeof(x64); q++)
					((unsigned char*)&x64)[q] = (unsigned char)((unsigned char)-1 & (unsigned)rand());
			}
			GT_UINT_ALL_GE_(wchar_t, unsigned INT64_TYPE, z, x64, r);
			{
				int r2 = 1; /* assume all chars are >= z */
				unsigned q = 0;
				for (; q < sizeof(x64)/sizeof(wchar_t); q++) {
					if (GT_CHAR_TO_UINT(wchar_t, ((const wchar_t*)&x64)[q]) < GT_CHAR_TO_UINT(wchar_t, z))
						r2 = 0;
				}
				TR(!r == !r2);
			}
			if (r)
				n++;
			else
				f++;
		}
	}
	printf("result: %s, total: %u, passed: %u, skipped: %u\n", rr ? "fail" : "ok", t, t - k, k);
	return rr;
}
