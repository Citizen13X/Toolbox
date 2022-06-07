cmake_minimum_required(VERSION 3.0)

project(DevApi)


if(CMAKE_SIZEOF_VOID_P EQUAL 4)
  set(ARCH x86)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(ARCH amd64)
else()
  set(ARCH unknown)
endif()


################################################################################
# Paths
################################################################################

set(ROOT_DIR ${CMAKE_SOURCE_DIR}/../..)


################################################################################
# Set output directories
################################################################################

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${ARCH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${ARCH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${ARCH})


################################################################################
# Global stuff
################################################################################

if(MSVC)
  add_compile_options(
    "/MT"
    "/W4"
    "/WX"
  )
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

include_directories(${ROOT_DIR})


################################################################################
# Binaries
################################################################################

add_executable(
  hex_dump_test
  ${CMAKE_SOURCE_DIR}/hex_dump_test.c

  ${ROOT_DIR}/toolbox/hex_dump.c
  ${ROOT_DIR}/toolbox/log.c
)

add_executable(
  log_test
  ${CMAKE_SOURCE_DIR}/log_test.c

  ${ROOT_DIR}/toolbox/log.c
)
