# gtparser
Small library of generic text parsing functions enough to parse simple configs

## Contents

- [Available functions](#available-functions)
- [Installing](#installing)


### Available functions

1. [_is_first_name](#check-if-given-char-may-start-an-identifier-name)
2. [digit_value](#check-if-given-char-is-a-decimal-digit-and-get-its-value)
3. [is_digit](#check-if-given-char-is-a-decimal-digit)
4. [_is_next_name](#check-if-given-char-may-continue-an-identifier-name)
5. [_hex_char_value](#check-if-given-char-is-a-hexadecimal-digit-and-get-its-value)
6. [is_first_name (table lookup-based)](#check-if-given-char-may-start-an-identifier-name-table-lookup-based-version)
7. [is_next_name (table lookup-based)](#check-if-given-char-may-continue-an-identifier-name-table-lookup-based-version)
8. [hex_char_value (table lookup-based)](#check-if-given-char-is-a-hexadecimal-digit-and-get-its-value-table-lookup-based-version)
9. [_scan_name](#scan-chars-of-a-name)
10. [_scan_uint](#scan-unsigned-decimal-integer)
11. [_scan_uint64](#scan-unsigned-decimal-64-bit-integer)
12. [_scan_hex](#scan-unsigned-hexdecimal-integer)
13. [_scan_hex64](#scan-unsigned-hexdecimal-64-bit-integer)

#### Check if given char may start an identifier name
```
int _is_first_name(char c);
```
Parameters:
- ```c```  - char to check

**Returns:** non-zero if ```c``` is in range ```[_a-zA-Z]```.

*Declared in:* [```gtparser/char_func.h```](/gtparser/char_func.h)

_Note_: table lookup-based [```is_first_name()```](#check-if-given-char-may-start-an-identifier-name-table-lookup-based-version) may be slightly faster than this header-only inline ```_is_first_name()```.

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

_Note_: ```s``` < ```end```

_Note_: ```INT64_TYPE``` - 64-bit integer type, by default defined as ```long long```.

**Returns:** pointer beyond the last char of scanned unsigned decimal integer (pointer to char not in range ```[0-9]```) or ```end```.

**_Note_**: on unsigned integer overflow, if printed number is too big, returns ```NULL```.

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

_Note_: ```s``` < ```end```

_Note_: ```INT64_TYPE``` - 64-bit integer type, by default defined as ```long long```.

**Returns:** pointer beyond the last char of scanned unsigned hexadecimal integer (pointer to char not in range ```[0-9a-fA-F]```) or ```end```.

**_Note_**: on unsigned integer overflow, if printed number is too big, returns ```NULL```.

*Declared in:* [```gtparser/int_scanner.h```](/gtparser/int_scanner.h)


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
