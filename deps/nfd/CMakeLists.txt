cmake_minimum_required(VERSION 3.14)

if(UNIX AND NOT APPLE)
	set(LINUX TRUE)
endif()

if(APPLE)
	project(nfd LANGUAGES C OBJC)

	set(SOURCES_NFD "nfd_common.c"
					"nfd_cocoa.m")
elseif(LINUX)
	project(nfd LANGUAGES C)

	set(SOURCES_NFD "nfd_common.c"
					"nfd_gtk.c")
else()
	project(nfd LANGUAGES C CXX)

	set(SOURCES_NFD "nfd_common.c"
					"nfd_win.cpp")
endif()

add_library(nfd ${SOURCES_NFD})
