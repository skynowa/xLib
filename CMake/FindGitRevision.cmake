#--------------------------------------------------------------------------------------------------
# \file  FindGitRevision.cmake
# \brief GIT revision informaytion
#
# GIT_REVISION_FOUND  - true if project under GIT
# GIT_REVISION_BRANCH - GIT current brunch
# GIT_REVISION_HASH   - GIT revision hash
#--------------------------------------------------------------------------------------------------


if (EXISTS "${CMAKE_SOURCE_DIR}/.git")
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

#--------------------------------------------------------------------------------------------------
# trace
if (NOT GIT_REVISION_FOUND AND GIT_REVISION_FIND_REQUIRED)
    message(FATAL_ERROR "GIT_REVISION_FOUND: ${GIT_REVISION_FOUND}")
else()
    message(STATUS "GIT_REVISION_FOUND: ${GIT_REVISION_FOUND}")
endif()
