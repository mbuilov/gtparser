# gtparser
Small library of generic text parsing functions enough to parse simple configs

## Contents

- [Generic text functions](#generic-text-functions)
- [Text iterator API](#text-iterator-api)
- [Handy functions for use with text iterator](#handy-functions-for-use-with-text-iterator)
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
9. [_scan_name](#scan-chars-of-a-name)
10. [_scan_uint](#scan-unsigned-decimal-integer)
11. [_scan_uint64](#scan-unsigned-decimal-64-bit-integer)
12. [_scan_hex](#scan-unsigned-hexadecimal-integer)
13. [_scan_hex64](#scan-unsigned-hexadecimal-64-bit-integer)
14. [is_space](#check-if-char-is-a-space)

### Text iterator API

1. [src_iter_init](#initialize-source-text-iterator-structure)
2. [src_iter_step](#step-over-current-character)
3. [src_iter_eof](#check-if-iterator-points-to-eof)
4. [src_iter_next](#move-iterator-to-next-character-and-check-it-for-eof)
5. [src_iter_process_tab](#account-encountered-tab-character)
6. [src_iter_check_tab](#check-if-current-character-is-a-tab)
7. [src_iter_inc_line](#account-encountered-newline)
8. [src_iter_check](#check-if-current-character-is-a-tab-or-eol)
9. [src_iter_current](#get-current-character)
10. [src_iter_current_eof](#get-current-character-or-0-as-eof-indicator)
11. [src_iter_get_column](#get-current-column-number)
12. [src_iter_get_pos](#get-iterator-text-position-line-and-column-numbers)
13. [src_iter_return_pos](#return-iterator-text-position-line-and-column-numbers)
14. [src_iter_save_pos](#save-iterator-state)
15. [src_iter_return_save_pos](#return-iterator-state)
16. [src_iter_restore_pos](#restore-iterator-state)

### Handy functions for use with text iterator
1. [_skip_rest_of_line](#skip-characters-until-end-of-line)
2. [_skip_comment](#skip-one-line-comment)
3. [read_non_space_skip_comments](#read-first-non-space-character-skipping-comments)
4. [read_non_space_stop_eol](#read-first-non-space-character-or-eol)

********************************************************************************

#### Check if given char is a decimal digit and get its value
```
unsigned digit_value(char c);
```
Parameters:
- ```c```  - char to check

**Returns:** value <= ```9``` if ```c``` is in range ```[0-9]```.

*Declared in:* [```gtparser/char_func.h```](/gtparser/char_func.h)

#### Check if given char is a decimal digit
```
int is_digit(char c);
```
Parameters:
- ```c```  - char to check

**Returns:** non-zero if ```c``` is in range ```[0-9]```.

*Declared in:* [```gtparser/char_func.h```](/gtparser/char_func.h)

#### Check if given char may start an identifier name
```
int _is_first_name(char c);
```
Parameters:
- ```c```  - char to check

**Returns:** non-zero if ```c``` is in range ```[_a-zA-Z]```.

*Declared in:* [```gtparser/char_func.h```](/gtparser/char_func.h)

_Note_: table lookup-based [```is_first_name()```](#check-if-given-char-may-start-an-identifier-name-table-lookup-based-version) may be slightly faster than this header-only inline ```_is_first_name()```.

#### Check if given char may continue an identifier name
```
int _is_next_name(char c);
```
Parameters:
- ```c```  - char to check

**Returns:** non-zero if ```c``` is in range ```[_a-zA-Z0-9]```.

*Declared in:* [```gtparser/char_func.h```](/gtparser/char_func.h)

_Note_: table lookup-based [```is_next_name()```](#check-if-given-char-may-continue-an-identifier-name-table-lookup-based-version) may be slightly faster than this header-only inline ```_is_next_name()```.

#### Check if given char is a hexadecimal digit and get its value
```
unsigned _hex_char_value(char c);
```
Parameters:
- ```c```  - char to check

**Returns:** value <= ```15``` if ```c``` is in range ```[a-fA-F0-9]```.

*Declared in:* [```gtparser/char_func.h```](/gtparser/char_func.h)

_Note_: table lookup-based [```hex_char_value()```](#check-if-given-char-is-a-hexadecimal-digit-and-get-its-value-table-lookup-based-version) may be slightly faster than this header-only inline ```_hex_char_value()```.

#### Check if given char may start an identifier name (table lookup-based version)
```
int is_first_name(char c);
```
Parameters:
- ```c```  - char to check

**Returns:** non-zero if ```c``` is in range ```[_a-zA-Z]```.

*Declared in:* [```gtparser/name_scanner.h```](/gtparser/name_scanner.h)

#### Check if given char may continue an identifier name (table lookup-based version)
```
int is_next_name(char c);
```
Parameters:
- ```c```  - char to check

**Returns:** non-zero if ```c``` is in range ```[_a-zA-Z0-9]```.

*Declared in:* [```gtparser/name_scanner.h```](/gtparser/name_scanner.h)

#### Check if given char is a hexadecimal digit and get its value (table lookup-based version)
```
unsigned hex_char_value(char c);
```
Parameters:
- ```c```  - char to check

**Returns:** value <= ```15``` if ```c``` is in range ```[a-fA-F0-9]```.

*Declared in:* [```gtparser/name_scanner.h```](/gtparser/name_scanner.h)

#### Scan chars of a name
```
const char *_scan_name(const char *s, const char *const end);
```
Parameters:
- ```s```  - points to first char of a name in a buffer (char in range ```[_a-zA-Z]```)
- ```end``` - points one char beyond the buffer containing a name

_Note_: ```s``` < ```end```

**Returns:** pointer beyond the last char of scanned name (pointer to char not in range ```[_a-zA-Z0-9]```) or ```end```.

*Declared in:* [```gtparser/name_scanner.h```](/gtparser/name_scanner.h)

#### Scan unsigned decimal integer
```
const char *_scan_uint(const char *s, const char *const end, unsigned *number);
```
Parameters:
- ```s```  - points to first char of unsigned decimal integer printed in a buffer (char in range ```[0-9]```)
- ```end``` - points one char beyond the buffer containing printed unsigned decimal integer
- ```number``` - (_output_) scanned unsigned integer value

_Note_: ```s``` < ```end```

**Returns:** pointer beyond the last char of scanned unsigned decimal integer (pointer to char not in range ```[0-9]```) or ```end```.

**_Note_**: on unsigned integer overflow, if printed number is too big, returns ```NULL```.

*Declared in:* [```gtparser/int_scanner.h```](/gtparser/int_scanner.h)

#### Scan unsigned decimal 64-bit integer
```
const char *_scan_uint64(const char *s, const char *const end, unsigned INT64_TYPE *number);
```
Parameters:
- ```s```  - points to first char of unsigned decimal integer printed in a buffer (char in range ```[0-9]```)
- ```end``` - points one char beyond the buffer containing printed unsigned decimal integer
- ```number``` - (_output_) scanned unsigned 64-bit integer value

_Notes_:
* ```s``` < ```end```
* ```INT64_TYPE``` - 64-bit integer type, by default defined as ```long long```.

**Returns:** pointer beyond the last char of scanned unsigned decimal integer (pointer to char not in range ```[0-9]```) or ```end```.

**_Note_**: on unsigned integer overflow, if printed number is too big to be stored in 64 bits, returns ```NULL```.

*Declared in:* [```gtparser/int_scanner.h```](/gtparser/int_scanner.h)

#### Scan unsigned hexadecimal integer
```
const char *_scan_hex(const char *s, const char *const end, unsigned *number);
```
Parameters:
- ```s```  - points to first char of unsigned hexadecimal integer printed in a buffer (char in range ```[0-9a-fA-F]```)
- ```end``` - points one char beyond the buffer containing printed unsigned hexadecimal integer
- ```number``` - (_output_) scanned unsigned integer value

_Note_: ```s``` < ```end```

**Returns:** pointer beyond the last char of scanned unsigned hexadecimal integer (pointer to char not in range ```[0-9a-fA-F]```) or ```end```.

**_Note_**: on unsigned integer overflow, if printed number is too big, returns ```NULL```.

*Declared in:* [```gtparser/int_scanner.h```](/gtparser/int_scanner.h)

#### Scan unsigned hexadecimal 64-bit integer
```
const char *_scan_hex64(const char *s, const char *const end, unsigned INT64_TYPE *number);
```
Parameters:
- ```s```  - points to first char of unsigned hexadecimal integer printed in a buffer (char in range ```[0-9a-fA-F]```)
- ```end``` - points one char beyond the buffer containing printed unsigned hexadecimal integer
- ```number``` - (_output_) scanned unsigned 64-bit integer value

_Notes_:
* ```s``` < ```end```
* ```INT64_TYPE``` - 64-bit integer type, by default defined as ```long long```.

**Returns:** pointer beyond the last char of scanned unsigned hexadecimal integer (pointer to char not in range ```[0-9a-fA-F]```) or ```end```.

**_Note_**: on unsigned integer overflow, if printed number is too big to be stored in 64 bits, returns ```NULL```.

*Declared in:* [```gtparser/int_scanner.h```](/gtparser/int_scanner.h)

#### Check if char is a _space_
```
int is_space(char c);
```
Parameters:
- ```c``` - checked char

**Returns:** non-zero if ```c``` is a _space_ - character with value in ascii range ```[0..32]```

_Note_: this fast and simple function is usable to skip all space characters, like tabulations, new lines, form feeds, bells and so on.

*Declared in:* [```gtparser/parser_base.h```](/gtparser/parser_base.h)

================================================================

#### Initialize source text iterator structure
```
void src_iter_init(struct src_iter *it, const char *input, size_t size);
```
Parameters:
- ```it```    - iterator structure to initialize
- ```input``` - text buffer to parse
- ```size```  - number of chars to parse in text buffer

_Note_: Iterator line and column numbers are set to ```1```

*Example:*
```
extern const char *input;
extern size_t size;
struct src_iter it;
src_iter_init(&it, input, size);
```

*Declared in:* [```gtparser/parser_base.h```](/gtparser/parser_base.h)

#### Step over current character
```
void src_iter_step(struct src_iter *it);
```
Parameters:
- ```it``` - text iterator structure

Iterator column number incremented by ```1```.

_Notes_:
* assume current char was checked for ```<TAB>``` (horizontal tabulate character ```'\t'```) or ```<EOL>``` (end-of-line indicator character ```'\n'```)
* iterator must not point to ```<EOF>``` (end-of-file indicator)

*Declared in:* [```gtparser/parser_base.h```](/gtparser/parser_base.h)

#### Check if iterator points to &lt;EOF&gt;
```
int src_iter_eof(const struct src_iter *it);
```
Parameters:
- ```it``` - text iterator structure

**Returns:** non-zero if iterator points to ```<EOF>```, zero - if not

*Example of simple parsing loop:*
```
extern struct src_iter *it;
while (!src_iter_eof(it)) {
	/* process current character */
	src_iter_step(it);
}
```

*Declared in:* [```gtparser/parser_base.h```](/gtparser/parser_base.h)

#### Move iterator to next character and check it for &lt;EOF&gt;
```
int src_iter_next(struct src_iter *it);
```
Parameters:
- ```it``` - text iterator structure

**Returns:** non-zero if current character is _**not**_ ```<EOF>```, may continue parsing

Iterator column number incremented by ```1```.

_Notes_:
* assume current char was checked for ```<TAB>``` or ```<EOL>```
* iterator must not point to ```<EOF>```

*Example of simple parsing loop:*
```
extern struct src_iter *it;
if (!src_iter_eof(it)) {
	do {
		/* process current character */
	} while (src_iter_next(it));
}
```

*Declared in:* [```gtparser/parser_base.h```](/gtparser/parser_base.h)

#### Account encountered &lt;TAB&gt; character
```
void src_iter_process_tab(struct src_iter *it);
```
Parameters:
- ```it``` - text iterator structure

Iterator column number incremented by ```1``` to ```GTPARSER_TAB_SIZE```, depending on current column number value.

_Notes_:
* iterator must point to ```<TAB>``` character
* horizontal tabulate width equals to ```GTPARSER_TAB_SIZE``` spaces, ```4``` by default.

*Declared in:* [```gtparser/parser_base.h```](/gtparser/parser_base.h)

#### Check if current character is a &lt;TAB&gt;
```
void src_iter_check_tab(struct src_iter *it);
```
Parameters:
- ```it``` - text iterator structure

Check if current character is a ```<TAB>``` and account it if it is.

_Note_: iterator must not point to ```<EOF>```

*Declared in:* [```gtparser/parser_base.h```](/gtparser/parser_base.h)

#### Account encountered newline
```
void src_iter_inc_line(struct src_iter *it);
```
Parameters:
- ```it``` - text iterator structure

Increment iterator line number, set column number to zero.

_Note_: iterator must point to ```<EOL>```

*Declared in:* [```gtparser/parser_base.h```](/gtparser/parser_base.h)

#### Check if current character is a &lt;TAB&gt; or &lt;EOL&gt;
```
void src_iter_check(struct src_iter *it);
```
Parameters:
- ```it``` - text iterator structure

Check if current character is a ```<TAB>``` or ```<EOL>```, then account it appropriately.

_Note_: iterator must not point to ```<EOF>```

*Example of simple parsing loop:*
```
extern struct src_iter *it;
if (!src_iter_eof(it)) {
	do {
		/* process current character */
		/* account <TAB> or new line */
		src_iter_check(it);
	} while (src_iter_next(it));
}
```

*Declared in:* [```gtparser/parser_base.h```](/gtparser/parser_base.h)

#### Get current character
```
char src_iter_current(const struct src_iter *it);
```
Parameters:
- ```it``` - text iterator structure

**Returns:** current character iterator points to

_Note_: iterator must not point to ```<EOF>```

*Example of simple parsing loop:*
```
extern struct src_iter *it;
if (!src_iter_eof(it)) {
	do {
		/* get current character to process */
		char c = src_iter_current(it);
		/* process current character */
		/* account <TAB> or new line */
		src_iter_check(it);
	} while (src_iter_next(it));
}
```

*Declared in:* [```gtparser/parser_base.h```](/gtparser/parser_base.h)

#### Get current character or 0 as &lt;EOF&gt; indicator
```
char src_iter_current_eof(const struct src_iter *it);
```
Parameters:
- ```it``` - text iterator structure

**Returns:** non-zero current character if iterator points to non-```<EOF>```, else returns ```0```

_Note_: this function may be usable for parsing texts where characters with zero value are not expected

*Example of simple parsing loop:*
```
extern struct src_iter *it;
for (;;) {
	/* get current character to process */
	char c = src_iter_current_eof(it);
	if (!c)
		break; /* iterator points to <EOF> */
	/* process current character */
	/* account <TAB> or new line */
	src_iter_check(it);
}
```

*Declared in:* [```gtparser/parser_base.h```](/gtparser/parser_base.h)

#### Get current column number
```
unsigned src_iter_get_column(const struct src_iter *it);
```
Parameters:
- ```it``` - text iterator structure

**Returns:** current iterator column number

_Note_: column number may overflow for large texts, but it is not fatal for parsing

*Declared in:* [```gtparser/parser_base.h```](/gtparser/parser_base.h)

#### Get iterator text position (line and column numbers)
```
void src_iter_get_pos(const struct src_iter *it, struct src_pos *pos);
```
Parameters:
- ```it``` - text iterator structure
- ```pos``` - (_output_) current iterator text position

*Declared in:* [```gtparser/parser_base.h```](/gtparser/parser_base.h)

#### Return iterator text position (line and column numbers)
```
struct src_pos src_iter_return_pos(const struct src_iter *it);
```
Parameters:
- ```it``` - text iterator structure

**Returns:** current iterator text position

*Declared in:* [```gtparser/parser_base.h```](/gtparser/parser_base.h)

#### Save iterator state
```
void src_iter_save_pos(const struct src_iter *it, struct src_save_pos *save_pos);
```
Parameters:
- ```it```       - text iterator structure
- ```save_pos``` - (_output_) current iterator state

```save_pos``` may be used to restore iterator state - unparse characters processed after ```save_pos``` was taken.

*Declared in:* [```gtparser/parser_base.h```](/gtparser/parser_base.h)

#### Return iterator state
```
struct src_save_pos src_iter_return_save_pos(const struct src_iter *it);
```
Parameters:
- ```it``` - text iterator structure

**Returns:** current iterator state

Returned state value may be used to restore iterator state - unparse characters processed after state was taken.

*Declared in:* [```gtparser/parser_base.h```](/gtparser/parser_base.h)

#### Restore iterator state
```
void src_iter_restore_pos(struct src_iter *it, const struct src_save_pos *save_pos);
```
Parameters:
- ```it```       - text iterator structure
- ```save_pos``` - saved iterator state

_Note_: ```save_pos``` may be obtained either by ```src_iter_save_pos()``` or ```src_iter_return_save_pos()```

*Declared in:* [```gtparser/parser_base.h```](/gtparser/parser_base.h)

================================================================

#### Skip characters until end of line
```
void _skip_rest_of_line(struct src_iter *it);
```
Parameters:
- ```it``` - text iterator structure

Skip current character, then next characters until new line.

On return, iterator points to beginning of next line or to ```<EOF>```.

_Notes_:
* this function is usable to skip one-line comment
* before the call, iterator must not point to ```<EOF>``` (assume iterator points to char indicating start of a comment)

*Declared in:* [```gtparser/parser_base.h```](/gtparser/parser_base.h)

#### Skip one-line comment
```
void _skip_comment(struct src_iter *it);
```

Just another name of [```_skip_rest_of_line()```](#skip-characters-until-end-of-line) function.

*Declared in:* [```gtparser/parser_base.h```](/gtparser/parser_base.h)

#### Read first non-space character skipping comments
```
char read_non_space_skip_comments(struct src_iter *it, char comment);
```
Parameters:
- ```it```      - text iterator structure
- ```comment``` - char indicating start of one-line comment

**Returns:** current non-space char or ```0```, if non-space char was not found and iterator points to ```<EOF>```

_Notes_:
* checks all characters, starting from current one by ```is_space()``` function
* skips one-line comments by ```_skip_comment()``` fuction
* iterator may point to ```<EOF>```

#### Read first non-space character or &lt;EOL&gt;
```
char read_non_space_stop_eol(struct src_iter *it);
```
Parameters:
- ```it``` - text iterator structure

**Returns:** current non-space char or ```<EOL>``` or ```0```, if non-space char or ```<EOL>``` was not found and iterator points to ```<EOF>```

*Declared in:* [```gtparser/parser_base.h```](/gtparser/parser_base.h)

--------------------------------------------------------------------------

### Installing

1. Get clean-build build system:

    [```git clone https://github.com/mbuilov/clean-build```](https://github.com/mbuilov/clean-build)

2. For windows, get [Gnu Make](https://www.gnu.org/software/make) executable:

    [```git clone https://github.com/mbuilov/gnumake-windows```](https://github.com/mbuilov/gnumake-windows)

3. Build library

    3.1 On Linux:
    ```
    $ make MTOP=/home/user/clean-build OS=LINUX CPU=x86_64 TARGET=GTPARSER
    ```

    3.2 On Windows:
    ```
    C:\tools\gnumake-4.2.1.exe MTOP=C:\tools\clean-build OS=WINXX CPU=x86_64 TARGET=GTPARSER OSVARIANT=WIN7 VS="C:\Program Files (x86)\Microsoft Visual Studio 14.0" WDK="C:\Program Files (x86)\Windows Kits\10" WDK_TARGET="10.0.14393.0"
    ```

    _**Tips**_:
    - define ```NO_STATIC=1``` to not build static library archive
    - define ```NO_SHARED=1``` to not build shared library (dll)
    - to view other possible values of ```OS```, ```CPU``` or ```TARGET``` variables, do not define them
    - define variable ```V=1``` for verbose build, to print executed commands

    If make target is not specified, default target _```all```_ (compile the library) will be built.

    _**Tip**_: there are predefined targets:
    * _```test```_      - to build library and tests
    * _```check```_     - to build library and tests, then run tests
    * _```clean```_     - to delete built artifacts, except created directories
    * _```distclean```_ - to delete all artifacts, including created directories

4. Install library and interface headers

    _Note_: make command should be the same as for building, except the target should be _```install```_ or _```uninstall```_.

    4.1 On Linux (_example_):

    possibly as root, do
    ```
    $ make MTOP=/home/user/clean-build OS=LINUX CPU=x86_64 TARGET=GTPARSER install
    ```

    4.2 On Windows (_example_):
    ```
    C:\tools\gnumake-4.2.1.exe MTOP=C:\tools\clean-build OS=WINXX CPU=x86_64 TARGET=GTPARSER OSVARIANT=WIN7 VS="C:\Program Files (x86)\Microsoft Visual Studio 14.0" WDK="C:\Program Files (x86)\Windows Kits\10" WDK_TARGET="10.0.14393.0" PREFIX=C:\dst install
    ```

    _Note_: Headers are installed in ```$(PREFIX)/include```, libraries - in ```$(PREFIX)/lib```.

    _**Tips**_:
    - define variable ```PREFIX``` to override default install location - ```/usr/local``` (for UNIX) or ```dist``` (for WINDOWS)
    - define variable ```LIBDIR``` to override default libraries install location - ```$(PREFIX)/lib```
    - define variable ```DESTDIR``` to add prefix to ```$(PREFIX)``` - to make path to temporary install location

    _**Tip**_: there is one more predefined target:
    * _```uninstall```_ - to delete installed files. Note: some installed directories may not be deleted.
