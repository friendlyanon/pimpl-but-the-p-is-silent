cmake_minimum_required(VERSION 3.14)

project(pimpl-but-the-p-is-silent CXX)

add_library(impl-private-storage STATIC cmake/impl-private-storage.cpp)

set(storage_root "${PROJECT_BINARY_DIR}")
get_cmake_property(is_multi_config GENERATOR_IS_MULTI_CONFIG)
if(is_multi_config)
  string(APPEND storage_root "/\$<CONFIG>")
endif()

set(storage_h "${storage_root}/include/impl-private-storage.hpp")
add_custom_command(
    OUTPUT "${storage_h}"
    COMMAND "${CMAKE_COMMAND}"
    "-Dout=${storage_h}"
    "-Dlib=\$<TARGET_FILE:impl-private-storage>"
    -P cmake/impl-private-storage.cmake
    MAIN_DEPENDENCY cmake/impl-private-storage.cmake
    DEPENDS impl-private-storage
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
    COMMENT "Querying size and alignment"
    VERBATIM
)

include(GenerateExportHeader)
add_library(impl SHARED source/impl.cpp source/impl-private.cpp "${storage_h}")
generate_export_header(impl EXPORT_FILE_NAME export/impl-export.hpp)
target_include_directories(
    impl PUBLIC
    "\$<BUILD_INTERFACE:${storage_root}/include>"
    "\$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/export>"
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)
set_target_properties(
    impl PROPERTIES
    VERSION 1.0
    SOVERSION 1
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
)

foreach(target impl-private-storage impl)
  target_include_directories("${target}" PRIVATE source)
  target_compile_features("${target}" PUBLIC cxx_std_20)
  # To pick up headers from 3rd party class members or inheritance, we must
  # also link them to the private storage target
  # target_link_libraries("${target}" PUBLIC deps... PRIVATE private deps...)
endforeach()

include(GNUInstallDirs)
install(TARGETS impl)
install(
    DIRECTORY
    include/
    "${storage_root}/include/"
    "${PROJECT_BINARY_DIR}/export/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

enable_testing()

add_executable(impl-test test/impl-test.cpp)
target_link_libraries(impl-test PRIVATE impl)
add_test(NAME impl-test COMMAND impl-test)
