cmake_minimum_required(VERSION 3.9)

file(STRINGS "${lib}" strings LIMIT_COUNT 10 REGEX "INFO:storage")

set(found 0)
foreach(info IN LISTS strings)
  if(info MATCHES "INFO:storage\\[0*([^:]*):0*([^]]*)\\]")
    set(found 1)
    break()
  endif()
endforeach()

if(NOT found)
  message(FATAL_ERROR "Couldn't find storage info in ${lib}")
endif()

file(WRITE "${out}_" "\
#pragma once

#include <cstddef>

namespace impl
{

constexpr size_t private_size = ${CMAKE_MATCH_1};
constexpr size_t private_align = ${CMAKE_MATCH_2};

}  // impl
")
configure_file("${out}_" "${out}" COPYONLY)
file(REMOVE "${out}_")
