#--------------------------------------------------------------------------------------------------
# \file  Configure.cmake
# \brief configure xLib sources
#--------------------------------------------------------------------------------------------------


include(CheckLibraryExists)
include(CheckCXXSourceCompiles)
include(FindMySQL)


#--------------------------------------------------------------------------------------------------
# find packages
find_package(OpenSSL REQUIRED)
find_package(MySQL REQUIRED)

if (MYSQL_FOUND)
    message("MySQL found:       ${MYSQL_FOUND}")
    message("MySQL include dir: ${MYSQL_INCLUDE_DIR}")
    message("MySQL libraries:   ${MYSQL_LIBRARIES}")
else()
    message("STATUS MySQL found: ${MYSQL_FOUND}")
endif()
#--------------------------------------------------------------------------------------------------
# configure
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/xLib/Core/xConfig.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/Include/xLib/Core/xConfig.h)

CHECK_LIBRARY_EXISTS(crypto BF_cfb64_encrypt "" xHAVE_OPENSSL_CRYPTO)

if (UNIX)
    # xHAVE_PR_SET_DUMPABLE
    check_cxx_source_compiles(
        "#include <sys/prctl.h>

        int main()
        {
            ::prctl(PR_SET_DUMPABLE, 0);
            return 0;
        }"
        xHAVE_PR_SET_DUMPABLE)

    # xHAVE_RLIMIT_CORE
    check_cxx_source_compiles(
        "#include <sys/resource.h>

        int main()
        {
            struct rlimit limit = {0, 0}
            ::setrlimit(RLIMIT_CORE, &limit);
            return 0;
        }"
        xHAVE_RLIMIT_CORE)

    # xHAVE_PT_DENY_ATTACH
    if (APPLE)
        check_cxx_source_compiles(
            "#include <sys/types.h>
            #include <sys/ptrace.h>

            int main()
            {
                ::ptrace(PT_DENY_ATTACH, 0, 0, 0);
                return 0;
            }"
            xHAVE_PT_DENY_ATTACH)
    endif()
endif()
#--------------------------------------------------------------------------------------------------
