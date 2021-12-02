cmake_minimum_required(VERSION 2.6)

PROJECT(tw-c-client-mini C)

SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")

ADD_DEFINITIONS(-D_FILE_OFFSET_BITS=64 -Os -Wall -Werror -Wmissing-declarations --std=gnu99)
ADD_DEFINITIONS(-DTW_OS_INCLUDE=\"twLinux-openssl.h\")

FIND_LIBRARY(twCSdk_lib NAMES twCSdk)

FIND_PATH(twCSdk_inc_dir NAME twApi.h twVersion.h PATH_SUFFIXES thingworx)

INCLUDE_DIRECTORIES(${twCSdk_inc_dir})

SET(SOURCES main.c util.c)

ADD_EXECUTABLE(twCSdkClientMini ${SOURCES})

TARGET_LINK_LIBRARIES(twCSdkClientMini ${twCSdk_lib})

INSTALL(TARGETS twCSdkClientMini
	RUNTIME DESTINATION bin
)
