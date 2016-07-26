#--------------------------------------------------------------------------------------------------
# \file  Template.cmake
# \brief Configure xLib tempalte
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# Config
set(cmXLIB_TEMPLATE          "")    # <<< set class name here
set(cmXLIB_TEMPLATE_COMMENTS "Dropbox tools")
set(cmXLIB_TEMPLATE_SUBDIR   "Package")
set(cmXLIB_TEMPLATE_NS       "package")
#--------------------------------------------------------------------------------------------------.
# Configure
if (NOT cmXLIB_TEMPLATE)
    return()
endif()

configure_file(
    ${XLIB_TEMPLATES}/[Class].h.in
    ${XLIB_LOCATION}/Include/xLib/${cmXLIB_TEMPLATE_SUBDIR}/${cmXLIB_TEMPLATE}.h)

configure_file(
    ${XLIB_TEMPLATES}/[Class].cpp.in
    ${XLIB_LOCATION}/Include/xLib/${cmXLIB_TEMPLATE_SUBDIR}/${cmXLIB_TEMPLATE}.cpp)

configure_file(
    ${XLIB_TEMPLATES}/Test_[Class].h.in
    ${XLIB_LOCATION}/Tests/${cmXLIB_TEMPLATE_SUBDIR}/Test_${cmXLIB_TEMPLATE}.h)

configure_file(
    ${XLIB_TEMPLATES}/Test_[Class].cpp.in
    ${XLIB_LOCATION}/Tests/${cmXLIB_TEMPLATE_SUBDIR}/Test_${cmXLIB_TEMPLATE}.cpp)

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
#--------------------------------------------------------------------------------------------------
