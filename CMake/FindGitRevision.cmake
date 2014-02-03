#--------------------------------------------------------------------------------------------------
# \file  FindGitRevision.cmake
# \brief GIT revision informaytion
#
# GIT_REVISION_FOUND  - true if project under GIT
# GIT_REVISION_BRANCH - GIT current brunch
# GIT_REVISION_HASH   - GIT revision hash
#--------------------------------------------------------------------------------------------------


if (NOT EXISTS "${CMAKE_SOURCE_DIR}/.git")
    set(GIT_REVISION_FOUND FALSE)
    set(GIT_REVISION_BRANCH "")
    set(GIT_REVISION_HASH "")
else()
    set(GIT_REVISION_FOUND TRUE)

    execute_process(
        COMMAND git rev-parse --abbrev-ref HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_REVISION_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    execute_process(
        COMMAND git log -1 --format=%h
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_REVISION_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif()

# info
if (NOT GIT_REVISION_FOUND)
    if (GIT_REVISION_FIND_REQUIRED)
        message(FATAL_ERROR "Could not find Git revision")
    endif()
else()
    message(STATUS "Found Git revision: ${GIT_REVISION_BRANCH}/${GIT_REVISION_HASH}")
endif()
