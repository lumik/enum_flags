# enum_flags

[![codecov](https://codecov.io/gh/lumik/enum_flags/branch/master/graph/badge.svg)](https://codecov.io/gh/lumik/enum_flags)
[![Build Status](https://travis-ci.org/lumik/enum_flags.svg?branch=master)](https://travis-ci.org/lumik/enum_flags)
[![Build status](https://ci.appveyor.com/api/projects/status/997j7fdbsrqlqiot/branch/master?svg=true)](https://ci.appveyor.com/project/lumik/enum-flags/branch/master)


Library which overloades bitwise operators for scoped enumerations.


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

Run this commands from the terminal from the `enum_flags` project directory to create build folder and `cmake` files.
```
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=.. -DCMAKE_BUILD_TYPE=Release -DENUM_FLAGS_MAKE_TESTS=ON \
         -DENUM_FLAGS_VERSION_INSTALL_INCLUDE=OFF
```
The `CMAKE_INSTALL_PREFIX` specifies the installation path (the `..` means, that the library would be installed in the
parent directory, i.e. `enum_flags` project directory) which defaults to system default paths if omited. The other two
options specifies test configuration. They defaults to `CMAKE_BUILD_TYPE=Debug` and `ENUM_FLAGS_MAKE_TEST=OFF` if
omited. The last define `ENUM_FLAGS_VERSION_INSTALL_INCLUDE` specifies, if the installation destination directory will
be in the for `lumik/enum_flags/enum_flags.h` (if switched `OFF`) or `enum_flags<version>/enum_flags.h` (`<version>`
can stand for `3.1.0` for example). The default is `OFF`.

Then you can install the library by issuing
```
make install
```


#### Windows and MinGW


If you are using Windows and MinWG you should also specify to the `cmake` command from the previous section
`cmake .. -G "MinGW Makefiles"`. The other specifications are the same.

To install the library, you have to issue then
```
mingw32-make install
```


### Usage

If you want bitwise operators to work for your enumeration, you have to specialize
lumik::enum_flags::EnableBitmaskOperators struct template to contain member `value = true`.

```cpp
#include <lumik/enum_flags/enum_flags.h>

namespace my_namespace {

enum struct TestFlags : unsigned char
{
    One   = 1u << 0u,
    Two   = 1u << 1u,
};

}  // namespace my_namespace

namespace lumik {
namespace enum_flags {

template<>
struct EnableBitmaskOperators<my_namespace::TestFlags> {
    static constexpr bool value = true;
};

// declaration of members of partialy specialized structs (not needed in c++17,
// which introduces inline variables and make constexpr variables inline by
// default)
constexpr bool EnableBitmaskOperators<TestFlags>::value;

}  // namespace lumik
}  // namespace enum_flags

int main(int argc, char** argv) {
    my_namespace::TestFlags a, b, c;
    a = TestFlags::One;
    b = TestFlags::Two;
    c = a | b;
```

More info can be found in the [documentation](#documentation).

The integration into external cmake project and more usage examples can be found for example in the
[sprelay][sprelay] application.


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

After you run  the cmake commands from the installation section you can run the following commands from the `build`
folder.
- Linux 
  ```
  make
  make test
  make doc
  ```
- Windows, MSYS2, MinGW
  ```
  mingw32-make
  mingw32-make test
  mingw32-make doc
  ```

Tests can be also performed by running binary file from the `tests` folder from terminal.


## Documentation

Documentation can be found in the `share/doc/enum_flags` folder, html documentation can be opened by the `index.html`
file.


[git]: https://git-scm.com/
[msys2]: http://www.msys2.org/
[doxygen]: http://www.stack.nl/~dimitri/doxygen/
[graphviz]: http://graphviz.org/
[gtest]: https://github.com/google/googletest
[cmake]: https://cmake.org/download/
[sprelay]: https://github.com/biomolecules/sprelay
