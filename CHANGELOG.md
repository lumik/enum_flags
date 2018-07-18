# Change Log
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/) 
and this project adheres to [Semantic Versioning](http://semver.org/).


## [Unreleased](https://github.com/lumik/enum_flags/compare/master...develop)


### Added


### Changed


### Fixed
- Fixed failing Makefile for MinGW installation from Qt.
- Readme for Windows installation.


### Removed


## [Version 2.1.0](https://github.com/lumik/enum_flags/compare/v2.0.0...v2.1.0)


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
