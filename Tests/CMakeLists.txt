#--------------------------------------------------------------------------------------------------
# \file  CMakeLists.txt
# \brief tests
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
include_directories(Include)
file(GLOB_RECURSE XLIB_TESTS_SOURCES Source/*.cpp)

foreach(IT_SOURCE ${XLIB_TESTS_SOURCES})
    get_filename_component(SOURCE_NAME ${IT_SOURCE} NAME_WE)

    add_executable(${SOURCE_NAME} ${IT_SOURCE})
    target_link_libraries(${SOURCE_NAME} ${PROJECT_NAME}_static)
    install(TARGETS ${SOURCE_NAME} DESTINATION "bin")

    add_test(NAME ${SOURCE_NAME} COMMAND ${SOURCE_NAME})
endforeach()
#--------------------------------------------------------------------------------------------------
