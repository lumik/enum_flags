# Change Log
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/) 
and this project adheres to [Semantic Versioning](http://semver.org/).


## [Unreleased](https://github.com/lumik/enum_flags/compare/master...develop)


### Added


### Changed


### Fixed


### Removed


## [Version 3.1.0 *(2018-10-10)*](https://github.com/lumik/enum_flags/compare/v3.0.0...v3.1.0)


### Added

- Importable doxygen documentation
- Appveyor tests for MSVC and MinGW
- Clang tests
- Coverage tests
- Badges


## [Version 3.0.0 *(2018-10-01)*](https://github.com/lumik/enum_flags/compare/v2.1.2...v3.0.0)


### Changed

- Moved to cmake.
- Moved the header file under `lumik` subfolder.
- Changed the `enable_enum_flags` function to `EnableEnumFlags` struct.
- Moved `EnableEnumFlags` to namespace `lumik::enum_flags`.


### Fixed

- Fixed README.md Documentation link.


### Removed

- Removed Makefile


## [Version 2.1.2 *(2018-07-24)*](https://github.com/lumik/enum_flags/compare/v2.1.1...v2.1.2)


### Changed

- Moved to Ubuntu 18.04 in automated tests.


### Fixed

- Fixed change log for dates
- Fixed anchor in readme.


## [Version 2.1.1 *(2018-07-18)*](https://github.com/lumik/enum_flags/compare/v2.1.0...v2.1.1)


### Fixed
- Fixed failing Makefile for MinGW installation without MSYS2.
- Readme for Windows installation.


## [Version 2.1.0 *(2018-07-03)*](https://github.com/lumik/enum_flags/compare/v2.0.0...v2.1.0)


### Added

- Added index documentation page.


### Changed

- Moved enum_flags.h to its own directory.
- Changed documentation style to Qt's one.
- Changed compilation flag for tests to `-O3`.


### Fixed

- Fixed doxygen warning of not documented parameter.
- Fixed bad version number in `Makefile` and `README.md`.


## [Version 2.0.0 *(2018-02-20)*](https://github.com/lumik/enum_flags/compare/v1.0.1...v2.0.0)


### Changed

- enableBitmaskOperators function name was changed to enable_bitmask_operators.


## [Version 1.0.1 *(2017-08-31)*](https://github.com/lumik/enum_flags/compare/v1.0.0...v1.0.1)


### Added

- `make install` possibility.


### Changed

- Third party libraries were moved to the `third_party` directory.
- All tests are performed through the `Makefile`.


## Version 1.0.0 *(2017-08-17)*


### Added
- Initial version of `enum_flags` library.
