#--------------------------------------------------------------------------------------------------
# \file  Configure.cmake
# \brief configure xLib sources
#--------------------------------------------------------------------------------------------------


include(CheckLibraryExists)
include(CheckCXXSourceCompiles)
include(FindMySQL)
include(FindExecInfo)


#--------------------------------------------------------------------------------------------------
# find packages
find_package(OpenSSL REQUIRED)
find_package(MySQL REQUIRED)
find_package(ExecInfo REQUIRED)

#--------------------------------------------------------------------------------------------------
# configure
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/xLib/Core/xConfig.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/xLib/Core/xConfig.h)

check_library_exists(crypto BF_cfb64_encrypt "" xHAVE_OPENSSL_CRYPTO)

if (WIN32)
    # TODO: windows part
elseif (UNIX)
    # xHAVE_EXECINFO
    if (EXECINFO_FOUND)
        # just for setting macro
        check_cxx_source_compiles(
            "int main() { return 0; }"
            xHAVE_EXECINFO
        )

        include_directories(${EXECINFO_INCLUDES})
        link_libraries(${EXECINFO_LIBRARIES})
    endif()

    # xHAVE_PR_SET_DUMPABLE
    check_cxx_source_compiles(
        "#include <sys/prctl.h>

        int main()
        {
            ::prctl(PR_SET_DUMPABLE, 0);
            return 0;
        }"
        xHAVE_PR_SET_DUMPABLE
    )

    # xHAVE_RLIMIT_CORE
    check_cxx_source_compiles(
        "#include <sys/resource.h>

        int main()
        {
            struct rlimit limit = {0, 0}
            ::setrlimit(RLIMIT_CORE, &limit);
            return 0;
        }"
        xHAVE_RLIMIT_CORE
    )

    # xHAVE_ADDR2LINE
    find_file(xHAVE_ADDR2LINE "addr2line")
    if (xHAVE_ADDR2LINE)
        message(STATUS "addr2line - found")
    else()
        message(WARNING "addr2line - failed")
    endif()

    # xHAVE_XMESSAGE
    find_file(xHAVE_XMESSAGE "xmessage")
    if (xHAVE_XMESSAGE)
        message(STATUS "xmessage - found")
    else()
        message(WARNING "xmessage - failed")
    endif()


    # Linux
    if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        # xHAVE_GETCPU
        check_cxx_source_compiles(
            "#include <linux/getcpu.h>

            int main()
            {
                unsigned int cpu = 0U;
                int iRv = ::getcpu(&cpu, NULL, NULL);
                return 0;
            }"
            xHAVE_GETCPU
        )
    endif()


    # Apple
    if (APPLE)
        # xHAVE_PT_DENY_ATTACH
        check_cxx_source_compiles(
            "#include <sys/types.h>
            #include <sys/ptrace.h>

            int main()
            {
                ::ptrace(PT_DENY_ATTACH, 0, 0, 0);
                return 0;
            }"
            xHAVE_PT_DENY_ATTACH
        )
    endif()
endif()
#--------------------------------------------------------------------------------------------------
