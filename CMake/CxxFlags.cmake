#--------------------------------------------------------------------------------------------------
# \file  CxxFlags.cmake
# \brief More CMAKE_CXX_FLAGS
#
# MSVC  -
# Clamg -
# MINGW -
# GCC   - http://gcc.gnu.org/onlinedocs/
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
if     (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
elseif (MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -Wall -Wno-deprecated -Wextra -Wconversion")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wno-unknown-pragmas -Wno-unused-parameter")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable -Wno-return-type-c-linkage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
        # -pedantic
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
elseif (CMAKE_COMPILER_IS_CLANGXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -Wall -Wno-deprecated -Wextra -Wconversion")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wno-unused-parameter -Wno-unused-variable")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas -Wno-return-type-c-linkage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -fcolor-diagnostics -Qunused-arguments")
        # -pedantic
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
elseif (CMAKE_COMPILER_IS_GNUCXX)
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -Wall -Wno-deprecated -Wextra -Wconversion")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wno-unknown-pragmas -Wno-unused-parameter")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable -Wno-return-type-c-linkage")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstack-protector -Wformat -Wformat-security")

    include(CMake/CxxFlags_gcc_4.6.4.cmake)
else()
    message("xLib: unknown compiler")
endif()

if (OS_ANDROID)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -Wall -Wno-deprecated -Wextra -Wconversion")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wno-unused-parameter -Wno-unused-variable")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas -frtti -fexceptions")
endif()
#--------------------------------------------------------------------------------------------------
