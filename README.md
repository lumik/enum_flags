# enum_flags.h – overloades bitwise operators for scoped enumerations.


## Requirements

* `c++` compiler.
* `git` – to clone the `enum_flags` repository. You can get git from [here][git].
* `Doxygen` – for documentation compilation, you can get it from [here][doxygen].
* `dot` – for graphs in documentation, it is part of the GraphViz library, you can get it from [here][graphviz].
* `Google Test` suite, you can get it from [here][gtest]
* `Cmake` – if MSYS2 is not used on windows, you have to install it manualy, you can get it from [here][cmake]

Make sure that the Doxygen and GraphViz binaries are in the `PATH` variable and Google Test suite headers and library
in your include path for compiler. If you installed cmake separately, ensure that it is in path too.


## Getting Started

Download `enum_flags.h` header from the repository and include it into your project.


### Obtaining `enum_flags.h`

If you just want to use `enum_flags` download the latest release from:
[https://github.com/lumik/enum_flags/releases](https://github.com/lumik/enum_flags/releases)


You can also clone the `enum_flags` repository using git:

```
git clone https://github.com/lumik/enum_flags.git
```


### Installation


#### Linux or Linux-like terminal (MSYS2, cygwin, ...)

Run this command from the terminal
```
make install
```

If you want to change destination directory, change variable DESTDIR, for example, if you want to place the header file
to `/opt/include/enum_flags2.1.0/enum_flags.h`, you should invoke
```
make DESTDIR=/opt install
```
or if you want it to install under the current directory, run
```
make DESTDIR=. install
```


#### Windows and MinGW

You can also install the library also using mingw32-make but then you have to specify it during make process:
```
mingw32-make MINGW=1 DESTDIR=c:\path\to\libraries\home
```


### Usage

If you want bitwise operators to work for your enumeration, you have to overload `enable_bitmask_operators()` function
to return true.

```cpp
#include "enum_flags2.1.0/enum_flags.h"

enum struct TestFlags : unsigned char
{
    One   = 1 << 0,
    Two   = 1 << 1,
};

constexpr bool enable_bitmask_operators(TestFlags) { return true; }

int main(int argc, char **argv) {
    TestFlags a, b, c;
    a = TestFlags::One;
    b = TestFlags::Two;
    c = a | b;
}
```

More info can be found in the [documentation](#documentation).


### Compilation of documentation and tests


#### Google test suite instalation in Windows with MinGW using [MSYS2][msys2]

- in MSYS2 console install `python` and `cmake`:
  ```
  pacman -Sy
  pacman -S mingw-w64-x86_64-python2 mingw-w64-x86_64-cmake
  ```
  (optionaly, you can also install winpty for python usage from terminal)
- download `googletest`, go to directory, where you want to compile `Google Test` and run:
  ```
  git clone --depth=1 https://github.com/google/googletest.git
  ```
- run Windows cmd, go to downloaded repository and add MinGW binaries to PATH and run cmake
  ```
  set PATH=c:\Programy\msys64\mingw64\bin\;%PATH%
  cd googletest\googletest
  mkdir build
  cd build
  cmake -G "MinGW Makefiles" ..
  mingw32-make
  ```
- in MSYS2 console copy headers and library files to their proper positions:
  ```
  cp -r include/gtest /mingw64/include/
  cp build/lib*.a /mingw64/lib
  ```


#### Google test suite instalation in Windows with MinGW (here installation from Qt)

- Make sure that `cmake`, `python` and `git` are installed.
- download `googletest` using git bash , go to directory, where you want to compile `Google Test` and run:
  ```
  git clone --depth=1 https://github.com/google/googletest.git
  ```
- run Windows cmd, go to downloaded repository and add MinGW binaries to PATH and run cmake
  ```
  set PATH=C:\Programs\Qt\Qt5.4.2\Tools\mingw491_32\bin;%PATH%
  cd googletest\googletest
  mkdir build
  cd build
  cmake -G "MinGW Makefiles" ..
  mingw32-make
  ```
- copy `include\gtest` directory inside `c:\Programs\Qt\Qt5.4.2\Tools\mingw491_32\i686-w64-mingw32\include\`
  and `*.a` files from build directory inside `c:\Programs\Qt\Qt5.4.2\Tools\mingw491_32\i686-w64-mingw32\lib\`


#### Google test suite instalation in Debian

- install `gtest` development package and cmake
  ```
  sudo apt install libgtest-dev cmake
  ```
- compile `Google Test` suite:
  ```
  cd /usr/src/gtest
  sudo cmake CMakeLists.txt
  sudo make
  ```
- copy or symlink libgtest.a and libgtest_main.a to your /usr/local/lib folder
  ```
  sudo cp *.a /usr/local/lib
  ```


#### Command line compilation of documentation and tests

Run these commands from console from the project root for your OS:
- Linux 
  ```
  make
  make test
  make doc
  ```
- Windows, MSYS2
  ```
  mingw32-make
  mingw32-make test
  mingw32-make doc
  ```
- Windows, MinGW withou MSYS2
  ```
  mingw32-make MINGW=1
  mingw32-make MINGW=1 test
  mingw32-make MINGW=1 doc
  ```

Tests can be also performed by running binary file from terminal in the `bin` folder.


## Documentation

Documentation can be found in the `doc` folder, html documentation can be opened by the `index.html` file.


[git]: https://git-scm.com/
[msys2]: http://www.msys2.org/
[doxygen]: http://www.stack.nl/~dimitri/doxygen/
[graphviz]: http://graphviz.org/
[gtest]: https://github.com/google/googletest
[cmake]: https://cmake.org/download/
