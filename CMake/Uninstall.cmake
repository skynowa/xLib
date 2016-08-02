#--------------------------------------------------------------------------------------------------
# \file  Uninstall.cmake
# \brief Uninstall xLib
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
message(STATUS "Uninstalling \"${XLIB_INSTALL_PATH}\"")

if (NOT EXISTS "${XLIB_INSTALL_PATH}")
    message(STATUS "Directory \"${XLIB_INSTALL_PATH}\" does not exist.")
else()
    exec_program("@CMAKE_COMMAND@"
        ARGS "-E remove_directory \"${XLIB_INSTALL_PATH}\""
        OUTPUT_VARIABLE rm_out RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
        message(FATAL_ERROR "Problem when removing \"${XLIB_INSTALL_PATH}\"")
    endif()
endif()
#--------------------------------------------------------------------------------------------------
