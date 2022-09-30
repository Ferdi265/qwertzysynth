if(NOT ${CMAKE_ARGC} EQUAL 6)
    message(FATAL_ERROR "usage: cmake -P embed.cmake <target> <template.cpp.in> <generated.cpp>")
endif()

set(file "${CMAKE_ARGV3}")
set(file-template "${CMAKE_ARGV4}")
set(file-source "${CMAKE_ARGV5}")

cmake_path(GET file STEM file-base)
cmake_path(GET file EXTENSION file-ext)
set(file-name "${file-base}${file-ext}")
string(REGEX REPLACE "\\." "_" file-name "${file-name}")

file(READ ${file} file-data HEX)
string(REPEAT "[0-9a-f]" 2 byte-regex)
string(REPEAT "[0-9a-f]" 16 line-regex)
string(REGEX REPLACE "(${line-regex})" "\\1\n    " file-data "${file-data}")
string(REGEX REPLACE "(${byte-regex})" "0x\\1, " file-data "${file-data}")

set(FILENAME "${file-name}")
set(DATA "${file-data}")
configure_file("${file-template}" "${file-source}" @ONLY)
