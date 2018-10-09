cmake_minimum_required(VERSION 3.1.3)
project(enum_flags VERSION 3.0.0 LANGUAGES CXX)

OPTION(ENUM_FLAGS_MAKE_TESTS
    "Makes tests."
    OFF)

OPTION(ENUM_FLAGS_VERSION_INSTALL_INCLUDE
    "Append version to sprelay include dir (include/sprelay<version>)."
    OFF)

# check for Doxygen
find_package(Doxygen)

# check for python for pylint
find_package(PythonInterp)

# enable tests
enable_testing()

# install correct libraries into correct locations on all platforms
include(GNUInstallDirs)

# collect library files
set(${PROJECT_NAME}_lib_hdr
    enum_flags.h)

# append version to include
if(ENUM_FLAGS_VERSION_INSTALL_INCLUDE)
    set(enum_flags_include_dirname ${PROJECT_NAME}${PROJECT_VERSION})
else()
    set(enum_flags_include_dirname ${PROJECT_NAME})
endif(ENUM_FLAGS_VERSION_INSTALL_INCLUDE)

set(enum_flags_source_dirname "${PROJECT_SOURCE_DIR}/src/lumik/${PROJECT_NAME}")
set(enum_flags_install_include_dirname "${CMAKE_INSTALL_INCLUDEDIR}/lumik/${enum_flags_include_dirname}")
set(enum_flags_install_cmake_dirname "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME}")
set(enum_flags_bin_cmake_dirname "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}")
set(enum_flags_install_doc_dirname "${CMAKE_INSTALL_DATAROOTDIR}/doc/${PROJECT_NAME}")

# create build and install file paths
foreach(hdr ${${PROJECT_NAME}_lib_hdr})
    list(APPEND ${PROJECT_NAME}_lib_hdr_build "${enum_flags_source_dirname}/${hdr}" )
    list(APPEND ${PROJECT_NAME}_lib_hdr_install
        "${enum_flags_install_include_dirname}/${hdr}" )
endforeach()

# create the library
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} SYSTEM INTERFACE $<INSTALL_INTERFACE:include>)
target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

# attach header files to the library (mainly to display them in IDEs)
target_sources(${PROJECT_NAME} INTERFACE
    $<INSTALL_INTERFACE:${${PROJECT_NAME}_lib_hdr_install}>
    $<BUILD_INTERFACE:${${PROJECT_NAME}_lib_hdr_build}>)

# force C++11
if(CMAKE_VERSION VERSION_LESS "3.8.2")
    target_compile_features(${PROJECT_NAME} INTERFACE cxx_constexpr)
else()
    target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_11)
endif(CMAKE_VERSION VERSION_LESS "3.8.2")

# create alias to enable treating the library inside this projec as if it were imported in namespace
add_library(lumik::${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# install the library and export it to target list
install(FILES ${${PROJECT_NAME}_lib_hdr_build}
    DESTINATION "${enum_flags_install_include_dirname}")
install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# export the target list into build tree
export(EXPORT ${PROJECT_NAME}Targets
    FILE "${enum_flags_bin_cmake_dirname}/${PROJECT_NAME}Targets.cmake"
    NAMESPACE lumik::${PROJECT_NAME}::
)

# create package to be discoverable in find package
include(CMakePackageConfigHelpers)
configure_package_config_file(cmake/${PROJECT_NAME}Config.cmake.in
    "${enum_flags_bin_cmake_dirname}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION "${enum_flags_install_cmake_dirname}"
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO)
write_basic_package_version_file(
    "${enum_flags_bin_cmake_dirname}/${PROJECT_NAME}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion)

# install package cmake files
install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE lumik::${PROJECT_NAME}::
    DESTINATION "${enum_flags_install_cmake_dirname}"
    COMPONENT Develop)
install(
    FILES
        "${enum_flags_bin_cmake_dirname}/${PROJECT_NAME}Config.cmake"
        "${enum_flags_bin_cmake_dirname}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION "${enum_flags_install_cmake_dirname}"
    COMPONENT Develop)

# make tests
if(ENUM_FLAGS_MAKE_TESTS)
    add_subdirectory(tests)
endif(ENUM_FLAGS_MAKE_TESTS)

# documentation
if(DOXYGEN_FOUND)
    # find cppreference file
    find_file(cppreference_tag_file cppreference-doxygen-web.tag.xml HINTS ENV CPPREFERENCE_TAGS_ROOT)
    if (cppreference_tag_file)
        set(cppreference_tags "\"${cppreference_tag_file}=http://en.cppreference.com/w/\"")
    else()
        add_custom_command(
            OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/cppreference-doxygen-web.tag.xml
            COMMAND ${CMAKE_COMMAND}
            -D DEST_DIR=${CMAKE_CURRENT_BINARY_DIR}
            -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/get_cppreference_tags.cmake
            COMMENT "Getting cppreference.com doxygen tags...")
        add_custom_target(get_ccpreference_tags DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/cppreference-doxygen-web.tag.xml)
        set(cppreference_tags
            "\"${CMAKE_CURRENT_BINARY_DIR}/cppreference-doxygen-web.tag.xml=http://en.cppreference.com/w/\"")
    endif()
    # get Qt documentation location
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    set(enum_flags_tags ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.tags)
    set(doxy_main_page ${enum_flags_source_dirname}/index.md)
    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation with Doxygen"
        VERBATIM)
    if (NOT cppreference_tag_file)
        add_dependencies(doc get_ccpreference_tags)
    endif()
    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc/html DESTINATION ${enum_flags_install_doc_dirname} OPTIONAL)
    install(
        FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.tags
        DESTINATION ${enum_flags_install_doc_dirname} OPTIONAL)
endif(DOXYGEN_FOUND)

# Other tests
if(PYTHONINTERP_FOUND)
    add_test(NAME pylint
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ${PYTHON_EXECUTABLE}
            external/cpplint-1.3.0/cpplint.py --recursive src tests)
endif(PYTHONINTERP_FOUND)
