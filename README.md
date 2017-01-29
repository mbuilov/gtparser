# gtparser
Small library of generic text parsing functions enough to parse simple configs

## Available functions

1. [_is_first_name](#check-if-given-char-may-start-an-identifier-name)
2. [digit_value](#check-if-given-char-is-a-decimal-digit-and-get-its-value)
3. [is_digit](#check-if-given-char-is-a-decimal-digit)
4. [_is_next_name](#check-if-given-char-may-continue-an-identifier-name)
5. [_hex_char_value](#check-if-given-char-is-a-hexadecimal-digit-and-get-its-value)


#### Check if given char may start an identifier name
```
int _is_first_name(char c);
```
Parameters:
- ```c```  - char to check

**Returns:** non-zero if ```c``` is in range [_a-zA-Z].
*Declared in:* ```gtparser/char_func.h```

#### Check if given char is a decimal digit and get its value
```
unsigned digit_value(char c);
```
Parameters:
- ```c```  - char to check

**Returns:** value <= ```9``` if ```c``` is in range [0-9].
*Declared in:* ```gtparser/char_func.h```

#### Check if given char is a decimal digit
```
int is_digit(char c);
```
Parameters:
- ```c```  - char to check

**Returns:** non-zero if ```c``` is in range [0-9].
*Declared in:* ```gtparser/char_func.h```

#### Check if given char may continue an identifier name
```
int _is_next_name(char c);
```
Parameters:
- ```c```  - char to check

**Returns:** non-zero if ```c``` is in range [_a-zA-Z0-9].
*Declared in:* ```gtparser/char_func.h```

#### Check if given char is a hexadecimal digit and get its value
```
unsigned _hex_char_value(char c);
```
Parameters:
- ```c```  - char to check

**Returns:** value <= ```15``` if ```c``` is in range [a-fA-F0-9].
*Declared in:* ```gtparser/char_func.h```


## Building

1. Get clean-build build system:

    ```
    git clone https://github.com/mbuilov/clean-build
    ```
2. For windows, get Gnu Make:

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

    _**Tip**_:
    to view other possible values of OS, CPU or TARGET variables, do not define them.

    If make target is not specified, default target _all_ (compile the library) will be built.

    _**Tip**_: there are predefined targets:
    * test      - to build library and tests
    * check     - to build library and tests, then run tests
    * clean     - to delete built artifacts, except created directories
    * distclean - to delete all artifacts, including created directories

4. Install library with interface headers

    4.1 On Linux:
    possibly as root, do
    ```
    $ make MTOP=/home/user/clean-build OS=LINUX CPU=x86_64 TARGET=GTPARSER install
    ```

    4.2 On Windows:
    ```
    C:\tools\gnumake-4.2.1.exe MTOP=C:\tools\clean-build OS=WINXX CPU=x86_64 TARGET=GTPARSER OSVARIANT=WIN7 VS="C:\Program Files (x86)\Microsoft Visual Studio 14.0" WDK="C:\Program Files (x86)\Windows Kits\10" WDK_TARGET="10.0.14393.0" PREFIX=C:\dst install
    ```

    Headers are installed in $(PREFIX)/include, libraries - in $(PREFIX)/lib.

    _**Tips**_.
    - define variable PREFIX to override default install location - /usr/local
    - define variable LIBDIR to override default libraries install location - $(PREFIX)/lib
    - define variable DESTDIR to add prefix to $(PREFIX) - to make path to temporary install location.

    _**Tip**_: there is one more predefined target:
    * uninstall - to delete installed files. Note: installed directories are not deleted.
