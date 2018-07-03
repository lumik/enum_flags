VERSION = 1.0.1

CXX = g++
CXXFLAGS = -pipe -fno-keep-inline-dllexport -O2 -std=c++0x -frtti -Wall -Wextra -fexceptions -mthreads
LIBS = -lgtest
LINKER = g++
LFLAGS = -Wl,-s -Wl,-subsystem,console -mthreads
TESTINC = -I$(CURDIR)/src

detected_OS := $(shell uname -s)

CXXFLAGS = -pipe -O2 -std=c++0x -frtti -Wall -Wextra -fexceptions -pthread
LFLAGS = -Wl,-O1 -pthread
TARGET = enum_flags_unittest
ifeq ($(detected_OS),Linux)
  CXXFLAGS = -pipe -O2 -std=c++0x -frtti -Wall -Wextra -fexceptions -pthread
  LFLAGS = -Wl,-O1 -pthread
	TARGET = enum_flags_unittest
	ifeq ($(DESTDIR),)
		DESTDIR := /usr/local
	endif
	MKDIRCMD = mkdir -p
	CPCMD = cp
endif
ifneq (, $(findstring MINGW, $(detected_OS)))
  CXXFLAGS = -pipe -fno-keep-inline-dllexport -O2 -std=c++0x -frtti -Wall -Wextra -fexceptions -mthreads
  LFLAGS = -Wl,-s -Wl,-subsystem,console -mthreads
	TARGET = enum_flags_unittest.exe
	ifeq ($(DESTDIR),)
		DESTDIR := /usr/local
	endif
	MKDIRCMD = mkdir -p
	CPCMD = cp
endif

HEADERS = src/enum_flags/enum_flags.h
SOURCES = tests/enum_flags_unittest.cpp

BUILDDIR = build
OBJECTS = $(BUILDDIR)/enum_flags_unittest.o

TESTDESTDIR        = bin
TESTDESTDIR_TARGET = $(TESTDESTDIR)/$(TARGET)

INCLUDEDIR = $(DESTDIR)/include/enum_flags$(VERSION)

.PHONY: all
all: $(TESTDESTDIR_TARGET)

.PHONY: install
install:
	$(MKDIRCMD) $(INCLUDEDIR)
	$(CPCMD) src/enum_flags/enum_flags.h $(INCLUDEDIR)/enum_flags.h

.PHONY: test
test: $(TESTDESTDIR_TARGET)
	$(TESTDESTDIR_TARGET)

$(TESTDESTDIR_TARGET): $(OBJECTS)
	$(MKDIRCMD) $(TESTDESTDIR) 
	$(LINKER) $(LFLAGS) -o $(TESTDESTDIR_TARGET) $(OBJECTS) $(LIBS)
 
$(OBJECTS): $(SOURCES) $(HEADERS)
	$(MKDIRCMD) build 
	$(CXX) $(CXXFLAGS) -c -o build/enum_flags_unittest.o tests/enum_flags_unittest.cpp $(TESTINC)

.PHONY: check-cpplint
check-cpplint:
	python third_party/cpplint-1.3.0/cpplint.py --recursive src tests
	
.PHONY: doc
doc:
	doxygen 

.PHONY: clean    
clean:
	$(RM) build/* 