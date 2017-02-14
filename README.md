# gtparser
Small library of generic text parsing functions enough to parse simple grammars.

For such grammars, it may be easier to implement parsing rules by hand, over than using parser generator like Bison.

To use these functions, source text should be available as a raw array of chars (large text from file may be mmap()'ed to a memory region).

## Contents

- [Generic text functions](#generic-text-functions)
- [Source text iterator API](#source-text-iterator-api-gtparserparser_baseh)
- [Handy functions for use with source text iterator](#handy-functions-for-use-with-source-text-iterator)
- [Helpers to compose error message](#helpers-to-compose-error-message)
- [Installing](#installing)

### Generic text functions

1. [digit_value](#check-if-given-char-is-a-decimal-digit-and-get-its-value)
2. [is_digit](#check-if-given-char-is-a-decimal-digit)
3. [_is_first_name](#check-if-given-char-may-start-an-identifier-name)
4. [_is_next_name](#check-if-given-char-may-continue-an-identifier-name)
5. [_hex_char_value](#check-if-given-char-is-a-hexadecimal-digit-and-get-its-value)
6. [is_first_name (table lookup-based)](#check-if-given-char-may-start-an-identifier-name-table-lookup-based-version)
7. [is_next_name (table lookup-based)](#check-if-given-char-may-continue-an-identifier-name-table-lookup-based-version)
8. [hex_char_value (table lookup-based)](#check-if-given-char-is-a-hexadecimal-digit-and-get-its-value-table-lookup-based-version)
9. [_scan_name](#scan-characters-of-a-name)
10. [_scan_uint](#scan-unsigned-decimal-integer)
11. [_scan_uint64](#scan-unsigned-decimal-integer)
12. [_scan_hex](#scan-unsigned-hexadecimal-integer)
13. [_scan_hex64](#scan-unsigned-hexadecimal-integer)
14. [is_space](#check-if-char-is-a-space)

### Source text iterator API ([gtparser/parser_base.h](/gtparser/parser_base.h))

1. [src_iter_init](#initialize-source-text-iterator-structure)
2. [src_iter_step](#step-over-current-character)
3. [src_iter_eof](#check-if-iterator-points-to-eof)
4. [src_iter_next](#move-iterator-to-next-character-and-check-it-for-eof)
5. [src_iter_process_tab](#account-encountered-tab-character)
6. [src_iter_check_tab](#check-if-current-character-is-a-tab)
7. [src_iter_inc_line](#account-encountered-eol-character)
8. [src_iter_check](#check-if-current-character-is-a-tab-or-eol)
9. [src_iter_current_char](#get-current-character)
10. [src_iter_char_or_eof](#get-current-character-or-0-as-eof-indicator)
11. [src_iter_get_column](#get-current-column-number)
12. [src_iter_get_pos](#get-iterator-text-position-line-and-column-numbers)
13. [src_iter_return_pos](#return-iterator-text-position-line-and-column-numbers)
14. [src_iter_save_pos](#save-iterator-state)
15. [src_iter_return_save_pos](#return-iterator-state)
16. [src_iter_restore_pos](#restore-iterator-state)

### Handy functions for use with source text iterator

1. [_skip_rest_of_line](#skip-characters-until-new-line)
2. [_skip_comment](#skip-one-line-comment)
3. [read_non_space_skip_comments](#read-first-non-space-character-skipping-comments)
4. [read_non_space_stop_eol](#read-first-non-space-character-or-eol)
5. [read_name](#read-characters-of-a-name)
6. [read_uint](#read-unsigned-decimal-integer)
7. [read_uint64](#read-unsigned-decimal-integer)
8. [read_hex](#read-unsigned-hexadecimal-integer)
9. [read_hex64](#read-unsigned-hexadecimal-integer)

### Helpers to compose error message

1. [parser_err_reserve](#reserve-a-space-for-error-message-location-info)
2. [parser_err_reserve_](#reserve-a-space-for-error-message-location-info)
3. [parser_err_prepend_at](#prepend-location-info-to-error-message)
4. [parser_err_prepend_at_](#prepend-location-info-to-error-message)
5. [parser_err_prepend_at_line](#prepend-location-info-to-error-message)
6. [parser_err_prepend_at_line_](#prepend-location-info-to-error-message)
7. [parser_err_prepend_at_char](#prepend-location-info-to-error-message)
8. [parser_err_prepend_at_char_](#prepend-location-info-to-error-message)
9. [parser_err_print_char](#append-character-to-a-buffer)
10. [parser_err_print_chars](#append-characters-array-to-a-buffer)
11. [parser_err_print_string_constant](#append-string-constant-to-a-buffer)
12. [parser_err_print_string](#append-0-terminated-string-to-a-buffer)
13. [parser_err_print](#append-parametrized-message-to-a-buffer)
14. [parser_err_finish](#terminate-buffer-with-0)

---------------------------------------------------

#### Check if given char is a decimal digit and get its value
```C
unsigned digit_value(char c);
```
Parameters:
- `c`  - char to check

**Returns:** value <= `9` if `c` is matched by regexp `[0-9]`

*Declared in:* [`gtparser/char_func.h`](/gtparser/char_func.h)

#### Check if given char is a decimal digit
```C
int is_digit(char c);
```
Parameters:
- `c`  - char to check

**Returns:** non-zero if `c` is matched by regexp `[0-9]`

*Declared in:* [`gtparser/char_func.h`](/gtparser/char_func.h)

#### Check if given char may start an identifier name
```C
int _is_first_name(char c);
```
Parameters:
- `c`  - char to check

**Returns:** non-zero if `c` is matched by regexp: `[_a-zA-Z]`

*Declared in:* [`gtparser/char_func.h`](/gtparser/char_func.h)

_Note_: table lookup-based [`is_first_name()`](#check-if-given-char-may-start-an-identifier-name-table-lookup-based-version) may be slightly faster than this header-only inline `_is_first_name()`

#### Check if given char may continue an identifier name
```C
int _is_next_name(char c);
```
Parameters:
- `c`  - char to check

**Returns:** non-zero if `c` is matched by regexp: `[_a-zA-Z0-9]`

*Declared in:* [`gtparser/char_func.h`](/gtparser/char_func.h)

_Note_: table lookup-based [`is_next_name()`](#check-if-given-char-may-continue-an-identifier-name-table-lookup-based-version) may be slightly faster than this header-only inline `_is_next_name()`

#### Check if given char is a hexadecimal digit and get its value
```C
unsigned _hex_char_value(char c);
```
Parameters:
- `c`  - char to check

**Returns:** value <= `15` if `c` is matched by regexp: `[0-9a-fA-F]`

*Declared in:* [`gtparser/char_func.h`](/gtparser/char_func.h)

_Note_: table lookup-based [`hex_char_value()`](#check-if-given-char-is-a-hexadecimal-digit-and-get-its-value-table-lookup-based-version) may be slightly faster than this header-only inline `_hex_char_value()`

#### Check if given char may start an identifier name (table lookup-based version)
```C
int is_first_name(char c);
```
Parameters:
- `c`  - char to check

**Returns:** non-zero if `c` is matched by regexp: `[_a-zA-Z]`

*Declared in:* [`gtparser/name_scanner.h`](/gtparser/name_scanner.h)

#### Check if given char may continue an identifier name (table lookup-based version)
```C
int is_next_name(char c);
```
Parameters:
- `c`  - char to check

**Returns:** non-zero if `c` is matched by regexp: `[_a-zA-Z0-9]`

*Declared in:* [`gtparser/name_scanner.h`](/gtparser/name_scanner.h)

#### Check if given char is a hexadecimal digit and get its value (table lookup-based version)
```C
unsigned hex_char_value(char c);
```
Parameters:
- `c`  - char to check

**Returns:** value <= `15` if `c` is matched by regexp: `[0-9a-fA-F]`

*Declared in:* [`gtparser/name_scanner.h`](/gtparser/name_scanner.h)

#### Scan characters of a name
```C
const char *_scan_name(const char *s/*<end*/, const char *const end);
```
Parameters:
- `s`   - points to first char of a name in a buffer (likely a char matched by regexp: `[_a-zA-Z]`)
- `end` - points one char beyond the buffer containing a name

_Note_: `s < end`

**Returns:** pointer beyond the last char of scanned name (pointer to char not matched by regexp: `[_a-zA-Z0-9]`) or `end`

*Declared in:* [`gtparser/name_scanner.h`](/gtparser/name_scanner.h)

#### Scan unsigned decimal integer
```C
const char *_scan_uint(const char *s/*<end*/, const char *const end, unsigned *number/*out*/);
const char *_scan_uint64(const char *s/*<end*/, const char *const end, unsigned INT64_TYPE *number/*out*/);
```
Parameters:
- `s`      - points to first char of unsigned decimal integer printed in a buffer (char matched by regexp: `[0-9]`)
- `end`    - points one char beyond the buffer containing printed unsigned decimal integer
- `number` - (_output_) scanned unsigned (64-bit) integer value

_Notes_:
* `s < end`
* `INT64_TYPE` - 64-bit integer type, by default defined as `long long`

**Returns:** pointer beyond the last char of scanned unsigned decimal integer (pointer to char not matched by regexp: `[0-9]`) or `end`

**_Note_**: on unsigned integer overflow, if printed number is too big, returns `NULL`

*Declared in:* [`gtparser/int_scanner.h`](/gtparser/int_scanner.h)

#### Scan unsigned hexadecimal integer
```C
const char *_scan_hex(const char *s/*<end*/, const char *const end, unsigned *number/*out*/);
const char *_scan_hex64(const char *s/*<end*/, const char *const end, unsigned INT64_TYPE *number/*out*/);
```
Parameters:
- `s`      - points to first char of unsigned hexadecimal integer printed in a buffer (char matched by regexp: `[0-9a-fA-F]`)
- `end`    - points one char beyond the buffer containing printed unsigned hexadecimal integer
- `number` - (_output_) scanned unsigned (64-bit) integer value

_Notes_:
* `s < end`
* `INT64_TYPE` - 64-bit integer type, by default defined as `long long`

**Returns:** pointer beyond the last char of scanned unsigned hexadecimal integer (pointer to char not matched by regexp: `[0-9a-fA-F]`) or `end`

**_Note_**: on unsigned integer overflow, if printed number is too big, returns `NULL`

*Declared in:* [`gtparser/int_scanner.h`](/gtparser/int_scanner.h)

#### Check if char is a _space_
```C
int is_space(char c);
```
Parameters:
- `c` - checked char

**Returns:** non-zero if `c` is a _space_ - character with value in ASCII range `[0..32]`

_Note_: this fast and simple function is usable to skip all space characters, like tabulations, new lines, form feeds, bells and so on

*Declared in:* [`gtparser/parser_base.h`](/gtparser/parser_base.h)

================================================================

#### Initialize source text iterator structure
```C
void src_iter_init(struct src_iter *it, const char *input, size_t size);
```
Parameters:
- `it`    - iterator structure to initialize
- `input` - text buffer to parse
- `size`  - number of chars to parse in text buffer

_Note_: Iterator line and column numbers are set to `1`

*Example:*
```C
extern const char *input;
extern size_t size;
struct src_iter it;
src_iter_init(&it, input, size);
```

*Declared in:* [`gtparser/parser_base.h`](/gtparser/parser_base.h)

#### Step over current character
```C
void src_iter_step(struct src_iter *it);
```
Parameters:
- `it` - text iterator structure

Iterator column number incremented by `1`

_Notes_:
* assume current char was checked for `<TAB>` (horizontal tabulate character `'\t'`) or `<EOL>` (end-of-line indicator character `'\n'`)
* iterator must not point to `<EOF>` (end-of-file indicator)

*Declared in:* [`gtparser/parser_base.h`](/gtparser/parser_base.h)

#### Check if iterator points to &lt;EOF&gt;
```C
int src_iter_eof(const struct src_iter *it);
```
Parameters:
- `it` - text iterator structure

**Returns:** non-zero if iterator points to `<EOF>`, `0` - if not

*Example of simple parsing loop:*
```C
extern struct src_iter *it;
while (!src_iter_eof(it)) {
	/* process current character */
	src_iter_step(it);
}
```

*Declared in:* [`gtparser/parser_base.h`](/gtparser/parser_base.h)

#### Move iterator to next character and check it for &lt;EOF&gt;
```C
int src_iter_next(struct src_iter *it);
```
Parameters:
- `it` - text iterator structure

**Returns:** non-zero if current character is _**not**_ `<EOF>`, may continue parsing

Iterator column number incremented by `1`

_Notes_:
* assume current char was checked for `<TAB>` or `<EOL>`
* iterator must not point to `<EOF>`

*Example of simple parsing loop:*
```C
extern struct src_iter *it;
if (!src_iter_eof(it)) {
	do {
		/* process current character */
	} while (src_iter_next(it));
}
```

*Declared in:* [`gtparser/parser_base.h`](/gtparser/parser_base.h)

#### Account encountered &lt;TAB&gt; character
```C
void src_iter_process_tab(struct src_iter *it);
```
Parameters:
- `it` - text iterator structure

Iterator column number incremented by some value in range `[1..GTPARSER_TAB_SIZE]`, depending on current column number value

_Notes_:
* iterator must point to `<TAB>` character
* horizontal tabulate width equals to `GTPARSER_TAB_SIZE` spaces, `4` by default

*Declared in:* [`gtparser/parser_base.h`](/gtparser/parser_base.h)

#### Check if current character is a &lt;TAB&gt;
```C
void src_iter_check_tab(struct src_iter *it);
```
Parameters:
- `it` - text iterator structure

Check if current character is a `<TAB>` and account it by [`src_iter_process_tab()`](#account-encountered-tab-character) if it is

_Note_: iterator must not point to `<EOF>`

*Declared in:* [`gtparser/parser_base.h`](/gtparser/parser_base.h)

#### Account encountered &lt;EOL&gt; character
```C
void src_iter_inc_line(struct src_iter *it);
```
Parameters:
- `it` - text iterator structure

Increment iterator line number, set column number to zero

_Note_: iterator must point to `<EOL>` character

*Declared in:* [`gtparser/parser_base.h`](/gtparser/parser_base.h)

#### Check if current character is a &lt;TAB&gt; or &lt;EOL&gt;
```C
void src_iter_check(struct src_iter *it);
```
Parameters:
- `it` - text iterator structure

Check if current character is a `<TAB>` or `<EOL>`, then account it appropriately by [`src_iter_process_tab()`](#account-encountered-tab-character) or [`src_iter_inc_line()`](#account-encountered-eol-character)

_Note_: iterator must not point to `<EOF>`

*Example of simple parsing loop:*
```C
extern struct src_iter *it;
if (!src_iter_eof(it)) {
	do {
		/* process current character */
		/* account <TAB> or <EOL> */
		src_iter_check(it);
	} while (src_iter_next(it));
}
```

*Declared in:* [`gtparser/parser_base.h`](/gtparser/parser_base.h)

#### Get current character
```C
char src_iter_current_char(const struct src_iter *it);
```
Parameters:
- `it` - text iterator structure

**Returns:** current character iterator points to

_Note_: iterator must not point to `<EOF>`

*Example of simple parsing loop:*
```C
extern struct src_iter *it;
if (!src_iter_eof(it)) {
	do {
		/* get current character to process */
		char c = src_iter_current_char(it);
		/* process current character */
		/* account <TAB> or <EOL> */
		src_iter_check(it);
	} while (src_iter_next(it));
}
```

*Declared in:* [`gtparser/parser_base.h`](/gtparser/parser_base.h)

#### Get current character or '\0' as &lt;EOF&gt; indicator
```C
char src_iter_char_or_eof(const struct src_iter *it);
```
Parameters:
- `it` - text iterator structure

**Returns:** current non-zero character if iterator points to non-`<EOF>`, else returns `'\0'`

_Note_: this function may be usable for parsing texts where characters with zero value are not expected

*Example of simple parsing loop:*
```C
extern struct src_iter *it;
for (;;) {
	/* get current character to process */
	char c = src_iter_char_or_eof(it);
	if (!c)
		break; /* iterator points to <EOF> */
	/* process current character */
	/* account <TAB> or <EOL> */
	src_iter_check(it);
}
```

*Declared in:* [`gtparser/parser_base.h`](/gtparser/parser_base.h)

#### Get current column number
```C
unsigned src_iter_get_column(const struct src_iter *it);
```
Parameters:
- `it` - text iterator structure

**Returns:** current iterator column number

_Note_: column number may overflow for large texts, but it is not fatal for parsing

*Declared in:* [`gtparser/parser_base.h`](/gtparser/parser_base.h)

#### Get iterator text position (line and column numbers)
```C
void src_iter_get_pos(const struct src_iter *it, struct src_pos *pos/*out*/);
```
Parameters:
- `it`  - text iterator structure
- `pos` - (_output_) current iterator text position

*Declared in:* [`gtparser/parser_base.h`](/gtparser/parser_base.h)

#### Return iterator text position (line and column numbers)
```C
struct src_pos src_iter_return_pos(const struct src_iter *it);
```
Parameters:
- `it` - text iterator structure

**Returns:** current iterator text position

*Declared in:* [`gtparser/parser_base.h`](/gtparser/parser_base.h)

#### Save iterator state
```C
void src_iter_save_pos(const struct src_iter *it, struct src_save_pos *save_pos/*out*/);
```
Parameters:
- `it`       - text iterator structure
- `save_pos` - (_output_) current iterator state

`save_pos` may be used to restore iterator state - unparse characters processed after `save_pos` was taken

*Declared in:* [`gtparser/parser_base.h`](/gtparser/parser_base.h)

#### Return iterator state
```C
struct src_save_pos src_iter_return_save_pos(const struct src_iter *it);
```
Parameters:
- `it` - text iterator structure

**Returns:** current iterator state

Returned state value may be used to restore iterator state - unparse characters processed after state was taken

*Declared in:* [`gtparser/parser_base.h`](/gtparser/parser_base.h)

#### Restore iterator state
```C
void src_iter_restore_pos(struct src_iter *it, const struct src_save_pos *save_pos);
```
Parameters:
- `it`       - text iterator structure
- `save_pos` - saved iterator state

_Note_: `save_pos` may be obtained either by [`src_iter_save_pos()`](#save-iterator-state) or [`src_iter_return_save_pos()`](#return-iterator-state)

*Declared in:* [`gtparser/parser_base.h`](/gtparser/parser_base.h)

================================================================

#### Skip characters until new line
```C
void _skip_rest_of_line(struct src_iter *it);
```
Parameters:
- `it` - text iterator structure

Skip current character, then next characters until `<EOL>`, then skip `<EOL>`

On return, iterator points to beginning of next line or to `<EOF>`

_Notes_:
* this function is usable to skip one-line comment
* before the call, iterator must not point to `<EOF>` (assume iterator points to char indicating start of a comment)

*Declared in:* [`gtparser/parser_base.h`](/gtparser/parser_base.h)

#### Skip one-line comment
```C
void _skip_comment(struct src_iter *it);
```

Just another name of [`_skip_rest_of_line()`](#skip-characters-until-new-line) function

*Declared in:* [`gtparser/parser_base.h`](/gtparser/parser_base.h)

#### Read first non-space character skipping comments
```C
char read_non_space_skip_comments(struct src_iter *it, char comment);
```
Parameters:
- `it`      - text iterator structure
- `comment` - char indicating start of one-line comment

**Returns:** current non-space char or `'\0'`, if non-space char was not found and iterator points to `<EOF>`

_Notes_:
* checks all characters, starting from current one by [`is_space()`](#check-if-char-is-a-space) function
* skips one-line comments by [`_skip_comment()`](#skip-one-line-comment) function
* iterator may point to `<EOF>`

*Declared in:* [`gtparser/parser_base.h`](/gtparser/parser_base.h)

#### Read first non-space character or &lt;EOL&gt;
```C
char read_non_space_stop_eol(struct src_iter *it);
```
Parameters:
- `it` - text iterator structure

**Returns:** current non-space char or `<EOL>` or `'\0'`, if non-space char or `<EOL>` was not found and iterator points to `<EOF>`

*Declared in:* [`gtparser/parser_base.h`](/gtparser/parser_base.h)

#### Read characters of a name
```C
const char *read_name(struct src_iter *it);
```
Parameters:
- `it` - source text iterator structure

_Note_: iterator must point to first char of a name ([`src_iter_current_char()`](#get-current-character) returns likely a char matched by regexp: `[_a-zA-Z]`)

**Returns:** pointer to first char of read name

_Note_: by return, `it` points to non-name char (not matched by regexp `[_a-zA-Z0-9]` or to `<EOF>`

*Declared in:* [`gtparser/name_parser.h`](/gtparser/name_parser.h)

#### Read unsigned decimal integer
```C
int read_uint(struct src_iter *it, unsigned *number/*out*/);
int read_uint64(struct src_iter *it, unsigned INT64_TYPE *number/*out*/);
```
Parameters:
- `it`     - source text iterator structure
- `number` - (_output_) parsed unsigned (64-bit) integer value

_Note_: iterator must point to first char of unsigned decimal integer ([`src_iter_current_char()`](#get-current-character) must return a char matched by regexp: `[0-9]`)

**Returns:** `1` if number was successfully read, `0` - on unsigned integer overflow, if printed number is too big

_Notes_:
* by successful return, `it` points beyond the last char of scanned unsigned decimal integer (points to a char not matched by regexp: `[0-9]` or to `<EOF>`)
* on integer overflow, iterator not changed
* `INT64_TYPE` - 64-bit integer type, by default defined as `long long`

*Declared in:* [`gtparser/int_parser.h`](/gtparser/int_parser.h)

#### Read unsigned hexadecimal integer
```C
int read_hex(struct src_iter *it, unsigned *number/*out*/);
int read_hex64(struct src_iter *it, unsigned INT64_TYPE *number/*out*/);
```
Parameters:
- `it`     - source text iterator structure
- `number` - (_output_) parsed unsigned (64-bit) integer value

_Note_: iterator must point to first char of unsigned hexadecimal integer ([`src_iter_current_char()`](#get-current-character) must return a char matched by regexp: `[0-9a-fA-F]`)

**Returns:** `1` if number was successfully read, `0` - on unsigned integer overflow, if printed number is too big

_Notes_:
* by successful return, `it` points beyond the last char of scanned unsigned hexadecimal integer (points to a char not matched by regexp: `[0-9a-fA-F]` or to `<EOF>`)
* on integer overflow, iterator not changed
* `INT64_TYPE` - 64-bit integer type, by default defined as `long long`

*Declared in:* [`gtparser/int_parser.h`](/gtparser/int_parser.h)

================================================================

#### Reserve a space for error message location info
```C
char *parser_err_reserve(char err_buf[], size_t err_buf_size, size_t filename_reserve);
char *parser_err_reserve_(char err_buf[], size_t err_buf_size);
```
Parameters:
- `err_buf`          - buffer where to compose error message
- `err_buf_size`     - size of `err_buf`
- `filename_reserve` - how much space to reserve in `err_buf` for file name passed to [`parser_err_prepend_at()`](#prepend-location-info-to-error-message)

**Returns:** pointer to a space inside `err_buf` to print error message details to, or returns `err_buf`, if `err_buf` is too small

`parser_err_reserve_()` - just calls `parser_err_reserve()` with zero `filename_reserve` value

_Note_: if `err_buf` is big enough, then [`parser_err_prepend_at()`](#prepend-location-info-to-error-message) will prepend resulting error message with something like `"filename: parse error at (4294967295:4294967295):"`

*Example:* see [`parser_err_prepend_at()`](#prepend-location-info-to-error-message)

*Declared in:* [`gtparser/parser_err.h`](/gtparser/parser_err.h)

#### Prepend location info to error message
```C
const char *parser_err_prepend_at(
	char err_buf,
	size_t err_buf_size,
	size_t filename_reserve/*0?*/,
	const char *filename/*NULL?*/,
	const char *err,
	unsigned line/*0?*/,
	unsigned column/*0?*/);

const char *parser_err_prepend_at_line(
	char err_buf,
	size_t err_buf_size,
	size_t filename_reserve/*0?*/,
	const char *filename/*NULL?*/,
	const char *err,
	unsigned line/*!=0*/);

const char *parser_err_prepend_at_char(
	char err_buf,
	size_t err_buf_size,
	size_t filename_reserve/*0?*/,
	const char *filename/*NULL?*/,
	const char *err,
	unsigned column/*!=0*/);

const char *parser_err_prepend_at_(
	char err_buf,
	size_t err_buf_size,
	const char *err,
	unsigned line/*0?*/,
	unsigned column/*0?*/);

const char *parser_err_prepend_at_line_(
	char err_buf,
	size_t err_buf_size,
	const char *err,
	unsigned line/*!=0*/);

const char *parser_err_prepend_at_char_(
	char err_buf,
	size_t err_buf_size,
	const char *err,
	unsigned column/*!=0*/);
```
Parameters:
- `err_buf`          - buffer where to compose error message
- `err_buf_size`     - size of `err_buf`
- `filename_reserve` - how much space to reserve in `err_buf` for file name
- `filename`         - `'\0'`-terminated source file name where an error was encountered, may be `NULL`
- `err`              - `'\0'`-terminated error message
- `line`             - source line number where a parsing error was encountered, if zero, then only column number is printed
- `column`           - source column number where a parsing error was encountered, if zero, then only line number is printed

**Returns:** pointer to composed error message with prepended location info in `err_buf` or `err`, if `err_buf` is too small

* `parser_err_prepend_at_line()`  - just calls `parser_err_prepend_at()` with zero `column` value
* `parser_err_prepend_at_char()`  - just calls `parser_err_prepend_at()` with zero `line` value
* `parser_err_prepend_at_()`      - just calls `parser_err_prepend_at()` with zero `filename_reserve` and `NULL` `filename` values
* `parser_err_prepend_at_line_()` - just calls `parser_err_prepend_at_line()` with zero `filename_reserve` and `NULL` `filename` values
* `parser_err_prepend_at_char_()` - just calls `parser_err_prepend_at_line()` with zero `filename_reserve` and `NULL` `filename` values

_Note_: if error message was printed to `err_buf` (i.e. `err` is the value returned by [`parser_err_reserve()`](#reserve-a-space-for-error-message-location-info)), then `err_buf`, `err_buf_size` and `filename_reserve` must be the same that were passed to [`parser_err_reserve()`](#reserve-a-space-for-error-message-location-info)

*Example:*
```C
extern char err_buf[];
extern size_t err_buf_size;
extern size_t filename_reserve;
const char *err = parser_err_reserve(err_buf, err_buf_size, filename_reserve);
size_t err_space = (size_t)(err_buf + err_buf_size - err);
...
snprintf((char*)err, err_space, "some parameterized error message: %d", 100);
/* or */
err = "some error message without parameters";
...
extern const char *filename;
extern unsigned line;
extern unsigned column;
const char *err_msg = parser_err_prepend_at(
	err_buf,
	err_buf_size,
	filename_reserve,
	filename,
	err,
	line,
	column);
```

*Declared in:* [`gtparser/parser_err.h`](/gtparser/parser_err.h)

#### Append character to a buffer
```C
char *parser_err_print_char(char *buf/*<=end*/, const char *const end, char c);
```
Parameters:
- `buf` - position in destination buffer where to append character
- `end` - points one char beyond destination buffer
- `c`   - character to append to destination buffer

**Returns:** buffer position `<= end` after appended character

_Note_: character added only if there is a place for it in destination buffer

*Example:*
```C
extern char *buf;
extern char *end;
if (error)
	buf = parser_err_print_char(buf, end, '.');
...
```

*Declared in:* [`gtparser/parser_err.h`](/gtparser/parser_err.h)

#### Append characters array to a buffer
```C
char *parser_err_print_chars(char *buf/*<=end*/, const char *const end, const char chars[], size_t count);
```
Parameters:
- `buf`   - position in destination buffer where to append chars
- `end`   - points one char beyond destination buffer
- `chars` - characters array to append to destination buffer
- `count` - number of characters to append to destination buffer

**Returns:** buffer position `<= end` after appended characters

_Note_: characters array tail may be trimmed if it's too long to fit in buffer

*Example:*
```C
extern char *buf;
extern char *end;
extern int error;
if (error)
	buf = parser_err_print_chars(buf, end, "some error", 10);
...
```

*Declared in:* [`gtparser/parser_err.h`](/gtparser/parser_err.h)

#### Append string constant to a buffer
```C
char *parser_err_print_string_constant(char *buf/*<=end*/, const char *const end, const char s[]);
```
Parameters:
- `buf` - position in destination buffer where to append string constant
- `end` - points one char beyond destination buffer
- `s`   - string constant to append to destination buffer

**Returns:** buffer position `<= end` after appended string constant

_Note_: string constant tail may be trimmed if it's too long to fit in buffer

_Note_: implemented as a macro calling [`parser_err_print_chars()`](#append-characters-array-to-a-buffer)

*Example:*
```C
extern char *buf;
extern char *end;
extern int error;
if (error)
	buf = parser_err_print_string_constant(buf, end, "some error");
...
```

*Declared in:* [`gtparser/parser_err.h`](/gtparser/parser_err.h)

#### Append '\0'-terminated string to a buffer
```C
char *parser_err_print_string(char *buf/*<=end*/, const char *const end, const char *string/*'\0'-terminated*/);
```
Parameters:
- `buf`    - position in destination buffer where to append string
- `end`    - points one char beyond destination buffer
- `string` - string to append to destination buffer

**Returns:** buffer position `<= end` after appended string

_Note_: string tail may be trimmed if it's too long to fit in buffer

*Example:*
```C
extern char *buf;
extern char *end;
extern int error;
extern const char *err_message1;
if (error)
	buf = parser_err_print_string(buf, end, err_message1);
...
```

*Declared in:* [`gtparser/parser_err.h`](/gtparser/parser_err.h)

#### Append parametrized message to a buffer
```C
char *parser_err_print(char *buf/*<=end*/, const char *const end, const char *format, ...);
```
Parameters:
- `buf`    - position in destination buffer where to append formatted message
- `end`    - points one char beyond destination buffer
- `format` - `printf()`-like format string of parametrized message to append to destination buffer
- `...`    - parameters of parametrized message

**Returns:** buffer position `<= end` after appended formatted message

_Note_: formatted message tail may be trimmed if it's too long to fit in buffer

*Example:*
```C
extern char *buf;
extern char *end;
extern int error;
if (error)
	buf = parser_err_print(buf, end, "an error occurred: %d", error);
...
```

*Declared in:* [`gtparser/parser_err.h`](/gtparser/parser_err.h)

#### Terminate buffer with '\0'
```C
void parser_err_finish(char *buf/*<=end*/, const char *const end, size_t err_space);
```
Parameters:
- `buf`       - position in destination buffer where to append `'\0'`
- `end`       - points one char beyond destination buffer
- `err_space` - total destination buffer size

_Notes_:
* if `err_space` is zero, nothing is appended
* if `buf == end`, then last char in buffer is replaced with `'\0'`

*Example:*
```C
extern char err[];
extern size_t err_space;
{
	const char *buf = err;
	const char *const end = err + err_space;
	buf = parser_err_print(buf, end, "some message: %d", 100);
	buf = parser_err_print(buf, end, "some message: %d", 101);
	buf = parser_err_print(buf, end, "some message: %d", 102);
	parser_err_finish(buf, end, err_space);
}
/* err - '\0'-terminated error message */
```

*Declared in:* [`gtparser/parser_err.h`](/gtparser/parser_err.h)

---------------------------------------------------

### Installing

1. Get clean-build build system:

    [`git clone https://github.com/mbuilov/clean-build`](https://github.com/mbuilov/clean-build)

2. For windows, get [Gnu Make](https://www.gnu.org/software/make) executable:

    [`git clone https://github.com/mbuilov/gnumake-windows`](https://github.com/mbuilov/gnumake-windows)

3. Build library

    3.1 On Linux (_example_):
    ```sh
    $ make MTOP=/home/user/clean-build OS=LINUX CPU=x86_64 TARGET=GTPARSER
    ```

    3.2 On Windows (_example_):
    ```cmd
    C:\tools\gnumake-4.2.1.exe MTOP=C:\tools\clean-build OS=WINXX CPU=x86_64 TARGET=GTPARSER OSVARIANT=WIN7 VS="C:\Program Files (x86)\Microsoft Visual Studio 14.0" WDK="C:\Program Files (x86)\Windows Kits\10" WDK_TARGET="10.0.14393.0"
    ```

    _**Tips**_:
    - define `NO_STATIC=1` to not build static library archive
    - define `NO_SHARED=1` to not build shared library (dll)
    - to view other possible values of `OS`, `CPU` or `TARGET` variables, do not define them
    - define variable `V=1` for verbose build, to print executed commands

    If make target is not specified, default target _`all`_ (compile the library) will be built

    _**Tip**_: there are predefined targets:
    * _`test`_      - to build library and tests
    * _`check`_     - to build library and tests, then run tests
    * _`clean`_     - to delete built artifacts, except created directories
    * _`distclean`_ - to delete all artifacts, including created directories

4. Install library and interface headers

    _Note_: make command should be the same as for building, except the target should be _`install`_ or _`uninstall`_

    4.1 On Linux (_example_):

    possibly as root, do
    ```sh
    $ make MTOP=/home/user/clean-build OS=LINUX CPU=x86_64 TARGET=GTPARSER install
    ```

    4.2 On Windows (_example_):
    ```cmd
    C:\tools\gnumake-4.2.1.exe MTOP=C:\tools\clean-build OS=WINXX CPU=x86_64 TARGET=GTPARSER OSVARIANT=WIN7 VS="C:\Program Files (x86)\Microsoft Visual Studio 14.0" WDK="C:\Program Files (x86)\Windows Kits\10" WDK_TARGET="10.0.14393.0" PREFIX=C:\dst install
    ```

    _Note_: Headers are installed in `$(PREFIX)/include`, libraries - in `$(LIBDIR)`

    _**Tips**_:
    - define variable `PREFIX` to override default install location - `/usr/local` (for UNIX) or `dist` (for WINDOWS)
    - define variable `LIBDIR` to override default libraries install location - `$(PREFIX)/lib`
    - define variable `DESTDIR` to add prefix to `$(PREFIX)` - to make path to temporary install location

    _**Tip**_: there is one more predefined target:
    * _`uninstall`_ - to delete installed files. Note: some installed directories may not be deleted.
