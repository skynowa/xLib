#--------------------------------------------------------------------------------------------------
# \file  FindOS.cmake
# \brief find OS
#
# OS environment:
#   ENV_WIN
#   ENV_UNIX
#   ENV_LINUX
#   ENV_BSD
#   ENV_APPLE
#
# OS:
#   OS_WIN
#   OS_LINUX
#   OS_ANDROID
#   OS_FREEBSD
#   OS_MACOSX
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# unset cache
unset(ENV_WIN    CACHE)
unset(ENV_UNIX   CACHE)
unset(ENV_LINUX  CACHE)
unset(ENV_BSD    CACHE)
unset(ENV_APPLE  CACHE)
unset(OS_WIN     CACHE)
unset(OS_LINUX   CACHE)
unset(OS_ANDROID CACHE)
unset(OS_FREEBSD CACHE)
unset(OS_MACOSX  CACHE)

#--------------------------------------------------------------------------------------------------
# OS environment
if     (WIN32)
    set(ENV_WIN TRUE)
elseif (UNIX)
    set(ENV_UNIX TRUE)

    if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        set(ENV_LINUX TRUE)
    endif()

    if (${CMAKE_SYSTEM_NAME} MATCHES "BSD")
        set(ENV_BSD TRUE)
    endif()

    if (APPLE)
        set(ENV_APPLE TRUE)
    endif()
else()

endif()

#--------------------------------------------------------------------------------------------------
# OS
if     (ENV_WIN)
    set(OS_WIN TRUE)
elseif (ENV_UNIX)
    if (ENV_LINUX)
        # Linux
        set(OS_LINUX TRUE)

        # Android
        if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "armv7-a")
            set(OS_ANDROID TRUE)
        endif()
    endif()

    if (ENV_BSD)
        if (${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
            set(OS_FREEBSD TRUE)
        else()
            message(ERROR "ENV_BSD - failed")
        endif()
    endif()

    if (ENV_APPLE)
        if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
            set(OS_MACOSX TRUE)
        else()
            message(ERROR "ENV_APPLE - failed")
        endif()
    endif()
endif()

#--------------------------------------------------------------------------------------------------
# trace
# message("")
# message("************ FindOS.cmake Variables **************")

# message("* OS environment:")
# message("*   ENV_WIN:    " ${ENV_WIN})
# message("*   ENV_UNIX:   " ${ENV_UNIX})
# message("*   ENV_LINUX:  " ${ENV_LINUX})
# message("*   ENV_BSD:    " ${ENV_BSD})
# message("*   ENV_APPLE:  " ${ENV_APPLE})

# message("* OS:")
# message("*   OS_WIN:     " ${OS_WIN})
# message("*   OS_LINUX:   " ${OS_LINUX})
# message("*   OS_ANDROID: " ${OS_ANDROID})
# message("*   OS_FREEBSD: " ${OS_FREEBSD})
# message("*   OS_MACOSX:  " ${OS_MACOSX})

# message("**************************************************")
# message("")
#--------------------------------------------------------------------------------------------------
