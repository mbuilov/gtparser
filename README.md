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
1. [is_first_name (table lookup-based)](#check-if-given-char-may-start-an-identifier-name-table-lookup-based-version)
4. [is_next_name (table lookup-based)](#check-if-given-char-may-continue-an-identifier-name-table-lookup-based-version)
5. [hex_char_value (table lookup-based)](#check-if-given-char-is-a-hexadecimal-digit-and-get-its-value-table-lookup-based-version)


#### Check if given char may start an identifier name
```
int _is_first_name(char c);
```
Parameters:
- ```c```  - char to check

**Returns:** non-zero if ```c``` is in range ```[_a-zA-Z]```.

*Declared in:* ```gtparser/char_func.h```

_Note_: table lookup-based ```[is_first_name()](#check-if-given-char-may-start-an-identifier-name-table-lookup-based-version)``` may be slightly faster than this header-only inline ```_is_first_name()```.

#### Check if given char is a decimal digit and get its value
```
unsigned digit_value(char c);
```
Parameters:
- ```c```  - char to check

**Returns:** value <= ```9``` if ```c``` is in range ```[0-9]```.

*Declared in:* ```gtparser/char_func.h```

#### Check if given char is a decimal digit
```
int is_digit(char c);
```
Parameters:
- ```c```  - char to check

**Returns:** non-zero if ```c``` is in range ```[0-9]```.

*Declared in:* ```gtparser/char_func.h```

#### Check if given char may continue an identifier name
```
int _is_next_name(char c);
```
Parameters:
- ```c```  - char to check

**Returns:** non-zero if ```c``` is in range ```[_a-zA-Z0-9]```.

*Declared in:* ```gtparser/char_func.h```

_Note_: table lookup-based ```[is_next_name()](#check-if-given-char-may-continue-an-identifier-name-table-lookup-based-version)``` may be slightly faster than this header-only inline ```_is_next_name()```.

#### Check if given char is a hexadecimal digit and get its value
```
unsigned _hex_char_value(char c);
```
Parameters:
- ```c```  - char to check

**Returns:** value <= ```15``` if ```c``` is in range ```[a-fA-F0-9]```.

*Declared in:* ```gtparser/char_func.h```

_Note_: table lookup-based ```hex_char_value()```(#check-if-given-char-is-a-hexadecimal-digit-and-get-its-value-table-lookup-based-version) may be slightly faster than this header-only inline ```_hex_char_value()```.

#### Check if given char may start an identifier name (table lookup-based version)
```
int is_first_name(char c);
```
Parameters:
- ```c```  - char to check

**Returns:** non-zero if ```c``` is in range ```[_a-zA-Z]```.

*Declared in:* ```gtparser/name_scanner.h```

#### Check if given char may continue an identifier name (table lookup-based version)
```
int is_next_name(char c);
```
Parameters:
- ```c```  - char to check

**Returns:** non-zero if ```c``` is in range ```[_a-zA-Z0-9]```.

*Declared in:* ```gtparser/name_scanner.h```

#### Check if given char is a hexadecimal digit and get its value (table lookup-based version)
```
unsigned hex_char_value(char c);
```
Parameters:
- ```c```  - char to check

**Returns:** value <= ```15``` if ```c``` is in range ```[a-fA-F0-9]```.

*Declared in:* ```gtparser/name_scanner.h```


### Installing

1. Get clean-build build system:

    ```
    git clone https://github.com/mbuilov/clean-build
    ```
2. For windows, get Gnu Make excutable:

    ```
    git clone https://github.com/mbuilov/gnumake-windows
    ```
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
    - define ```NO_STATIC=1``` to not build static library archive,
    - define ```NO_SHARED=1``` to not build shared library (dll),
    - to view other possible values of ```OS```, ```CPU``` or ```TARGET``` variables, do not define them,
    - define variable ```V=1``` for verbose build, to print executed commands.

    If make target is not specified, default target _all_ (compile the library) will be built.

    _**Tip**_: there are predefined targets:
    * _test_      - to build library and tests
    * _check_     - to build library and tests, then run tests
    * _clean_     - to delete built artifacts, except created directories
    * _distclean_ - to delete all artifacts, including created directories

4. Install library and interface headers

    _Note_: make command should be the same as for building, except the target should be _install_ or _uninstall_.

    4.1 On Linux:
    possibly as root, do
    ```
    $ make MTOP=/home/user/clean-build OS=LINUX CPU=x86_64 TARGET=GTPARSER install
    ```

    4.2 On Windows:
    ```
    C:\tools\gnumake-4.2.1.exe MTOP=C:\tools\clean-build OS=WINXX CPU=x86_64 TARGET=GTPARSER OSVARIANT=WIN7 VS="C:\Program Files (x86)\Microsoft Visual Studio 14.0" WDK="C:\Program Files (x86)\Windows Kits\10" WDK_TARGET="10.0.14393.0" PREFIX=C:\dst install
    ```

    _Note_: Headers are installed in $(PREFIX)/include, libraries - in $(PREFIX)/lib.

    _**Tips**_:
    - define variable ```PREFIX``` to override default install location - ```/usr/local``` (for UNIX) or ```dist``` (for WINDOWS)
    - define variable ```LIBDIR``` to override default libraries install location - ```$(PREFIX)/lib```
    - define variable ```DESTDIR``` to add prefix to ```$(PREFIX)``` - to make path to temporary install location.

    _**Tip**_: there is one more predefined target:
    * _uninstall_ - to delete installed files. Note: some installed directories may not be deleted.
