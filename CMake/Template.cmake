#--------------------------------------------------------------------------------------------------
# \file  Template.cmake
# \brief Configure xLib tempalte
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# Config (set manually)
unset(cmXLIB_TEMPLATE                CACHE)
unset(cmXLIB_TEMPLATE_COMMENTS       CACHE)
unset(cmXLIB_TEMPLATE_SUBDIR         CACHE)
unset(cmXLIB_TEMPLATE_NS             CACHE)
unset(cmXLIB_TEMPLATE_PLATFORM_FILES CACHE)

set(cmXLIB_TEMPLATE                "GitClient") # TODO: set manually
set(cmXLIB_TEMPLATE_COMMENTS       "GIT client") # TODO: set manually
set(cmXLIB_TEMPLATE_SUBDIR         "Package")       # TODO: set manually
set(cmXLIB_TEMPLATE_NS             "package")       # TODO: set manually
set(cmXLIB_TEMPLATE_PLATFORM_FILES ON)

if (NOT cmXLIB_TEMPLATE OR
    NOT cmXLIB_TEMPLATE_COMMENTS OR
    NOT cmXLIB_TEMPLATE_SUBDIR OR
    NOT cmXLIB_TEMPLATE_NS)

    message(FATAL_ERROR "xLib: Template - bad variable(s)")
endif()
#--------------------------------------------------------------------------------------------------.
# Configure
message("Create: ${cmXLIB_TEMPLATE}")

configure_file(
    ${XLIB_TEMPLATES}/[Class].h.in
    ${XLIB_LOCATION}/Include/xLib/${cmXLIB_TEMPLATE_SUBDIR}/${cmXLIB_TEMPLATE}.h)

configure_file(
    ${XLIB_TEMPLATES}/[Class].cpp.in
    ${XLIB_LOCATION}/Include/xLib/${cmXLIB_TEMPLATE_SUBDIR}/${cmXLIB_TEMPLATE}.cpp)

configure_file(
    ${XLIB_TEMPLATES}/Test_[Class].cpp.in
    ${XLIB_LOCATION}/Tests/${cmXLIB_TEMPLATE_SUBDIR}/Test_${cmXLIB_TEMPLATE}.cpp)

if (cmXLIB_TEMPLATE_PLATFORM_FILES)
    configure_file(
        ${XLIB_TEMPLATES}/Platform/Win/[Class]_win.inl.in
        ${XLIB_LOCATION}/Include/xLib/${cmXLIB_TEMPLATE_SUBDIR}/Platform/Win/${cmXLIB_TEMPLATE}_win.inl)

    configure_file(
        ${XLIB_TEMPLATES}/Platform/Unix/[Class]_unix.inl.in
        ${XLIB_LOCATION}/Include/xLib/${cmXLIB_TEMPLATE_SUBDIR}/Platform/Unix/${cmXLIB_TEMPLATE}_unix.inl)

    configure_file(
        ${XLIB_TEMPLATES}/Platform/Linux/[Class]_linux.inl.in
        ${XLIB_LOCATION}/Include/xLib/${cmXLIB_TEMPLATE_SUBDIR}/Platform/Linux/${cmXLIB_TEMPLATE}_linux.inl)

    configure_file(
        ${XLIB_TEMPLATES}/Platform/Bsd/[Class]_bsd.inl.in
        ${XLIB_LOCATION}/Include/xLib/${cmXLIB_TEMPLATE_SUBDIR}/Platform/Bsd/${cmXLIB_TEMPLATE}_bsd.inl)

    configure_file(
        ${XLIB_TEMPLATES}/Platform/Apple/[Class]_apple.inl.in
        ${XLIB_LOCATION}/Include/xLib/${cmXLIB_TEMPLATE_SUBDIR}/Platform/Apple/${cmXLIB_TEMPLATE}_apple.inl)
endif(cmXLIB_TEMPLATE_PLATFORM_FILES)
#--------------------------------------------------------------------------------------------------
