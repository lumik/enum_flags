CXX = g++
CXXFLAGS = -pipe -fno-keep-inline-dllexport -O2 -std=c++0x -frtti -Wall -Wextra -fexceptions -mthreads
LIBS = -lgtest
LINKER = g++
LFLAGS = -Wl,-s -Wl,-subsystem,console -mthreads

detected_OS := $(shell uname -s)

CXXFLAGS = -pipe -O2 -std=c++0x -frtti -Wall -Wextra -fexceptions -pthread
LFLAGS = -Wl,-O1 -pthread
TARGET = enum_flags_unittest
ifeq ($(detected_OS),Linux)
  CXXFLAGS = -pipe -O2 -std=c++0x -frtti -Wall -Wextra -fexceptions -pthread
  LFLAGS = -Wl,-O1 -pthread
	TARGET = enum_flags_unittest
	MKDIRCMD = mkdir -p
endif
ifneq (, $(findstring MINGW, $(detected_OS)))
  CXXFLAGS = -pipe -fno-keep-inline-dllexport -O2 -std=c++0x -frtti -Wall -Wextra -fexceptions -mthreads
  LFLAGS = -Wl,-s -Wl,-subsystem,console -mthreads
	TARGET = enum_flags_unittest.exe
	MKDIRCMD = mkdir -p
endif

HEADERS = src/enum_flags.h
SOURCES = tests/enum_flags_unittest.cpp

BUILDDIR = build/
OBJECTS = $(BUILDDIR)enum_flags_unittest.o

DESTDIR        = bin/#avoid trailing-slash linebreak
DESTDIR_TARGET = $(DESTDIR)$(TARGET)


all: $(DESTDIR_TARGET)

test: $(DESTDIR_TARGET)

$(DESTDIR_TARGET): $(OBJECTS)
	$(MKDIRCMD) $(DESTDIR) 
	$(LINKER) $(LFLAGS) -o $(DESTDIR_TARGET) $(OBJECTS)  $(LIBS)
 
$(OBJECTS): $(SOURCES) $(HEADERS)
	$(MKDIRCMD) build 
	$(CXX) $(CXXFLAGS) -c -o build/enum_flags_unittest.o tests/enum_flags_unittest.cpp
	
.PHONY: doc clean
doc:
	doxygen 
    
clean:
	$(RM) build/* 