#--------------------------------------------------------------------------------------------------
# \file  FindXCB.cmake
# \brief Find libXCB
#
# XCB_FOUND             - true if XCB is available
# XCB_INCLUDE_DIR       - include directories to use XCB
# XLIB_XCB_INCLUDE_PATH - include directories to use XLIB/XCB
# XCB_LIBRARIES         - link against these to use XCB
#--------------------------------------------------------------------------------------------------


if (UNIX)
    find_path(XCB_INCLUDE_DIR xcb/xcb.h
        /usr/include
        DOC "The directory where xcb/xcb.h resides")

    find_path(XLIB_XCB_INCLUDE_PATH X11/Xlib-xcb.h
        /usr/include
        DOC "The directory where X11/Xlib-xcb.h resides")

    find_library(XCB_LIBRARY
        NAMES xcb
        PATHS
        /usr/lib
        DOC "The xcb library")

    # find_library(XCB_XLIB_LIBRARY
    #     NAMES xcb-xlib
    #     PATHS
    #     /usr/lib
    #     DOC "The xcb-xlib library")

    find_library(XLIB_XCB_LIBRARY
        NAMES X11-xcb
        PATHS
        /usr/lib
        DOC "The X11-xcb library")

    set(XCB_LIBRARIES ${XCB_LIBRARY} ${XLIB_XCB_LIBRARY}) # ${XCB_XLIB_LIBRARY}
endif()

if (XCB_INCLUDE_DIR AND XCB_LIBRARIES)
    set(XCB_FOUND TRUE)
else()
    set(XCB_FOUND FALSE)
endif()

if (XCB_FOUND)
    message(STATUS "Found XCB: ${XCB_LIBRARIES}")
else()
    if (XCB_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find XCB library")
    endif()
endif()
