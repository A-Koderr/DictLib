cmake_minimum_required(VERSION 3.0.0)
project(
    DictLib
    VERSION 0.1.0 
    LANGUAGES C
    )

set(CMAKE_INSTALL_PREFIX "/home/ars/Source Code/dict_install")

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()

add_subdirectory(src)
include_directories(include)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

install(TARGETS Dict 
    EXPORT DictTargets
    FILE_SET HEADERS
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
    )

install(EXPORT DictTargets
    FILE DictTargets.cmake
    DESTINATION lib/cmake/Dict
    )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "DictConfigVersion.cmake"
    COMPATIBILITY AnyNewerVersion)

install(FILES "DictConfig.cmake" "${CMAKE_CURRENT_BINARY_DIR}/DictConfigVersion.cmake"
    DESTINATION lib/cmake/Dict)

install(FILES "${PROJECT_SOURCE_DIR}/include/Dict/Dict.h" DESTINATION include/Dict)
    