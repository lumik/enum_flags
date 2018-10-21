project(enum_flags_test VERSION 1.0.0 LANGUAGES CXX)

# setup compiler flags
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (NOT MINGW OR DEFINED ENV{GTEST_ROOT})
    #set policy of <package_name>_ROOT
    if (POLICY CMP0074)
        cmake_policy(SET CMP0074 NEW)
    endif()

    # find GTest
    find_package(GTest REQUIRED)
endif()

# Add threading
#set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
#set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-pipe -frtti -Wall -Wextra -Wpedantic -fexceptions)
endif()

if (MSVC)
    add_compile_options(/W4)
endif()

if (MINGW)
    add_compile_options(-mthreads -fno-keep-inline-dllexport -DUNICODE)
    list(APPEND enum_flags_console_link_flags "-Wl,-subsystem,console")
endif()

if (ENABLE_COVERAGE)
    add_custom_target(coverage)
    set_property(GLOBAL PROPERTY coverage_raw_files "")
    set_property(GLOBAL PROPERTY coverage_binaries "")
endif()

set(${PROJECT_NAME}_src
    ${PROJECT_SOURCE_DIR}/enum_flags_unittest.cpp)

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_src})

target_link_libraries(${PROJECT_NAME}
    lumik::enum_flags::enum_flags)
if (MINGW AND NOT DEFINED ENV{GTEST_ROOT})
    target_link_libraries(${PROJECT_NAME}
        gtest)
elseif(DEFINED ENV{GTEST_ROOT})
    target_link_libraries(${PROJECT_NAME}
        ${GTEST_LIBRARIES})
    target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
        ${GTEST_INCLUDE_DIRS})
else()
    target_link_libraries(${PROJECT_NAME}
        ${GTEST_LIBRARIES}
        Threads::Threads)
    target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE
        ${GTEST_INCLUDE_DIRS})
endif()
if (enum_flags_console_link_flags)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS ${enum_flags_console_link_flags})
endif()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

if (ENABLE_COVERAGE)
    target_link_libraries(${PROJECT_NAME} -fprofile-instr-generate -fcoverage-mapping)
    add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.profraw
            COMMAND LLVM_PROFILE_FILE=${PROJECT_NAME}.profraw ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
            DEPENDS ${PROJECT_NAME}
            COMMENT "Creating raw coverage data...")
    set_property(GLOBAL APPEND PROPERTY coverage_raw_files "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.profraw")
    set_property(GLOBAL APPEND PROPERTY coverage_binaries "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}")
endif()

if (ENABLE_COVERAGE)
    if (DEFINED ENV{LLVM_PROFILE_BINARY})
        set(llvm_profile_binary_file $ENV{LLVM_PROFILE_BINARY})
    else()
        get_filename_component(compiler_parent ${CMAKE_CXX_COMPILER} DIRECTORY)
        set(llvm_profile_binary_file ${compiler_parent}/llvm-profdata)
    endif()

    if (DEFINED ENV{LLVM_COV_BINARY})
        set(llvm_cov_binary_file $ENV{LLVM_COV_BINARY})
    else()
        get_filename_component(compiler_parent ${CMAKE_CXX_COMPILER} DIRECTORY)
        set(llvm_cov_binary_file ${compiler_parent}/llvm-cov)
    endif()

    if (EXISTS ${llvm_profile_binary_file})
        message(STATUS "llvm_profile_binary_file: ${llvm_profile_binary_file}")
    else()
        message(WARNING "llvm_cov_binary_file does not exist at location ${llvm_profile_binary_file}. Set please LLVM_COV_BINARY environment variable to llvm-cov")
    endif()
    if (EXISTS ${llvm_cov_binary_file})
        message(STATUS "llvm_cov_binary_file: ${llvm_cov_binary_file}")
    else()
        message(WARNING "llvm_cov_binary_file does not exists at location ${llvm_cov_binary_file}. Set please LLVM_COV_BINARY environment variable to llvm-cov")
    endif()

    if (EXISTS ${llvm_profile_binary_file} AND EXISTS ${llvm_cov_binary_file})
        # covert cmake global list to strings
        get_property(coverage_raw_files GLOBAL PROPERTY coverage_raw_files)
        get_property(coverage_binaries GLOBAL PROPERTY coverage_binaries)
        foreach(item ${coverage_raw_files})
            set(coverage_raw_files_string "${coverage_raw_files_string} ${item}")
        endforeach()
        foreach(item ${coverage_binaries})
            set(coverage_binaries_string "${coverage_binaries_string} ${item}")
        endforeach()
        string(STRIP ${coverage_raw_files_string} coverage_raw_files_string)
        string(STRIP ${coverage_binaries_string} coverage_binaries_string)

        # merge .profraw files into .profdata file and convert them into enum_flags.coverage.txt summary
        add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/enum_flags.coverage.txt
            COMMAND ${llvm_profile_binary_file} merge -sparse ${coverage_raw_files_string}
                -o ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.profdata
            COMMAND ${llvm_cov_binary_file} show
                ${coverage_binaries_string}
                -instr-profile=${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.profdata
                > enum_flags.coverage.txt
            DEPENDS ${coverage_raw_files}
            COMMENT "Merging and converting coverage data...")
        add_custom_target(enum_flags_gather_coverage
            DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/enum_flags.coverage.txt)
        add_dependencies(coverage enum_flags_gather_coverage)
    endif()
endif()

if (ADDRESS_SANITIZE)
    target_link_libraries(${PROJECT_NAME} -fsanitize=address)
    set_tests_properties(${PROJECT_NAME} PROPERTIES ENVIRONMENT ASAN_OPTIONS=verbosity=1:detect_leaks=1:check_initialization_order=1)
elseif (THREAD_SANITIZE)
    target_link_libraries(${PROJECT_NAME} -fsanitize=thread)
    set_tests_properties(${PROJECT_NAME} PROPERTIES ENVIRONMENT TSAN_OPTIONS=verbosity=1)
elseif (MEMORY_SANITIZE)
    target_link_libraries(${PROJECT_NAME} -fsanitize=memory)
    set_tests_properties(${PROJECT_NAME} PROPERTIES ENVIRONMENT MSAN_OPTIONS=verbosity=1)
elseif (UB_SANITIZE)
    target_link_libraries(${PROJECT_NAME} -fsanitize=undefined)
    set_tests_properties(${PROJECT_NAME} PROPERTIES ENVIRONMENT UBSAN_OPTIONS=verbosity=1)
endif()
