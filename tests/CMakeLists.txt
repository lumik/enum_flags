project(enum_flags_test VERSION 1.0.0 LANGUAGES CXX)

# setup compiler flags
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(NOT MINGW)
    # find GTest
    set(GTEST_ROOT "c:/Programs/Qt/Qt5.4.2/Tools/mingw491_32/i686-w64-mingw32")
    find_package(GTest REQUIRED)
endif()

# Add threading
#set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
#set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-pipe -frtti -Wall -Wextra -fexceptions)
endif()

if(MINGW)
    add_compile_options(-mthreads -fno-keep-inline-dllexport -DUNICODE)
    list(APPEND enum_flags_console_link_flags "-Wl,-subsystem,console")
endif()

set(${PROJECT_NAME}_src
    ${PROJECT_SOURCE_DIR}/enum_flags_unittest.cpp)

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_src})

target_link_libraries(${PROJECT_NAME}
    enum_flags)
if(MINGW)
    target_link_libraries(${PROJECT_NAME}
        gtest)
else()
    target_link_libraries(${PROJECT_NAME}
        ${GTEST_LIBRARIES}
        Threads::Threads)
endif()
if(enum_flags_console_link_flags)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS ${enum_flags_console_link_flags})
endif(enum_flags_console_link_flags)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})