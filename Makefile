VERSION = 2.1.0

CXX = g++
CXXFLAGS = -pipe -fno-keep-inline-dllexport -O2 -std=c++0x -frtti -Wall -Wextra -fexceptions -mthreads
LIBS = -lgtest
LINKER = g++
LFLAGS = -Wl,-s -Wl,-subsystem,console -mthreads
TESTINC = -I$(CURDIR)/src

CXXFLAGS = -pipe -O3 -std=c++0x -frtti -Wall -Wextra -fexceptions -pthread
LFLAGS = -Wl,-O3 -pthread
TARGET = enum_flags_unittest
ifdef MINGW
	CXXFLAGS = -pipe -fno-keep-inline-dllexport -O3 -std=c++0x -frtti -Wall -Wextra -fexceptions -mthreads
	LFLAGS = -Wl,-s -Wl,-subsystem,console -mthreads
	TARGET = enum_flags_unittest.exe
	ifeq ($(DESTDIR),)
		DESTDIR := c:
	endif
	mkdir_cmd = if not exist $(1) mkdir $(1)
	CPCMD = copy
	RM = del /Q
	fix_path = $(subst /,\,$1)
else
	detected_OS := $(shell uname -s)

	ifeq ($(detected_OS),Linux)
		CXXFLAGS = -pipe -O3 -std=c++0x -frtti -Wall -Wextra -fexceptions -pthread
		LFLAGS = -Wl,-O3 -pthread
		TARGET = enum_flags_unittest
		ifeq ($(DESTDIR),)
			DESTDIR := /usr/local
		endif
		mkdir_cmd = mkdir -p $1
		CPCMD = cp
		RM = rm -f
		fix_path = $1
	endif
	ifneq (, $(findstring MINGW, $(detected_OS)))
		CXXFLAGS = -pipe -fno-keep-inline-dllexport -O3 -std=c++0x -frtti -Wall -Wextra -fexceptions -mthreads
		LFLAGS = -Wl,-s -Wl,-subsystem,console -mthreads
		TARGET = enum_flags_unittest.exe
		ifeq ($(DESTDIR),)
			DESTDIR := /usr/local
		endif
		mkdir_cmd = mkdir -p $1
		CPCMD = cp
		RM = rm -f
		fix_path = $1
	endif
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
	$(call mkdir_cmd,$(call fix_path,$(INCLUDEDIR)))
	$(CPCMD) $(call fix_path,src/enum_flags/enum_flags.h) $(call fix_path,$(INCLUDEDIR)/enum_flags.h)

.PHONY: test
test: $(TESTDESTDIR_TARGET)
	$(call fix_path,$(TESTDESTDIR_TARGET))

$(TESTDESTDIR_TARGET): $(OBJECTS)
	$(call mkdir_cmd,$(call fix_path,$(TESTDESTDIR)))
	$(LINKER) $(LFLAGS) -o $(TESTDESTDIR_TARGET) $(OBJECTS) $(LIBS)
 
$(OBJECTS): $(SOURCES) $(HEADERS)
	$(call mkdir_cmd,$(call fix_path,$(BUILDDIR)))
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
