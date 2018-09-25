cmake_minimum_required(VERSION 3.1.3)
project(enum_flags VERSION 2.1.2 LANGUAGES CXX)

OPTION(ENUM_FLAGS_MAKE_TESTS
    "Makes tests."
    OFF)

# check for Doxygen
find_package(Doxygen)

# check for python for pylint
find_package(PythonInterp)

# enable tests
enable_testing()

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} SYSTEM INTERFACE $<INSTALL_INTERFACE:include>)
target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(EXPORT ${PROJECT_NAME}Config DESTINATION share/${PROJECT_NAME}/cmake)
export(TARGETS ${PROJECT_NAME} FILE ${PROJECT_NAME}Config.cmake)
install(FILES "${PROJECT_SOURCE_DIR}/src/enum_flags/enum_flags.h"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/enum_flags${PROJECT_VERSION}")

if(ENUM_FLAGS_MAKE_TESTS)
    add_subdirectory(tests)
endif(ENUM_FLAGS_MAKE_TESTS)

# documentation
if(DOXYGEN_FOUND)
    # get Qt documentation location
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    set(doxy_main_page ${CMAKE_CURRENT_SOURCE_DIR}/src/enum_flags/index.md)
    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation with Doxygen"
        VERBATIM)
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc DESTINATION ${CMAKE_INSTALL_PREFIX} OPTIONAL)
endif(DOXYGEN_FOUND)

# Other tests
if(PYTHONINTERP_FOUND)
    add_test(NAME pylint
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ${PYTHON_EXECUTABLE}
            third_party/cpplint-1.3.0/cpplint.py --recursive src tests)
endif(PYTHONINTERP_FOUND)
