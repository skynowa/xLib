#--------------------------------------------------------------------------------------------------
# \file  Template.cmake
# \brief Configure xLib tempalte
#--------------------------------------------------------------------------------------------------


#--------------------------------------------------------------------------------------------------
# Config
set(XLIB_TEMPLATES_DIR     "${XLIB_LOCATION}/Tools/Templates")

set(XLIB_TEMPLATE          "Dropbox")
set(XLIB_TEMPLATE_COMMENTS "Dropbox tools")
set(XLIB_TEMPLATE_SUBDIR   "Package")
set(XLIB_TEMPLATE_NS       "package")
#--------------------------------------------------------------------------------------------------.
# Configure
if (NOT XLIB_TEMPLATE)
    return()
endif()

configure_file(
    ${XLIB_TEMPLATES_DIR}/[Class].h.in
    ${XLIB_LOCATION}/Include/xLib/${XLIB_TEMPLATE_SUBDIR}/${XLIB_TEMPLATE}.h)

configure_file(
    ${XLIB_TEMPLATES_DIR}/[Class].cpp.in
    ${XLIB_LOCATION}/Include/xLib/${XLIB_TEMPLATE_SUBDIR}/${XLIB_TEMPLATE}.cpp)

configure_file(
    ${XLIB_TEMPLATES_DIR}/Test_[Class].h.in
    ${XLIB_LOCATION}/Tests/${XLIB_TEMPLATE_SUBDIR}/Test_${XLIB_TEMPLATE}.h)

configure_file(
    ${XLIB_TEMPLATES_DIR}/Test_[Class].cpp.in
    ${XLIB_LOCATION}/Tests/${XLIB_TEMPLATE_SUBDIR}/Test_${XLIB_TEMPLATE}.cpp)

configure_file(
    ${XLIB_TEMPLATES_DIR}/Platform/Win/[Class]_win.inl.in
    ${XLIB_LOCATION}/Include/xLib/${XLIB_TEMPLATE_SUBDIR}/Platform/Win/${XLIB_TEMPLATE}_win.inl)

configure_file(
    ${XLIB_TEMPLATES_DIR}/Platform/Unix/[Class]_unix.inl.in
    ${XLIB_LOCATION}/Include/xLib/${XLIB_TEMPLATE_SUBDIR}/Platform/Unix/${XLIB_TEMPLATE}_unix.inl)

configure_file(
    ${XLIB_TEMPLATES_DIR}/Platform/Linux/[Class]_linux.inl.in
    ${XLIB_LOCATION}/Include/xLib/${XLIB_TEMPLATE_SUBDIR}/Platform/Linux/${XLIB_TEMPLATE}_linux.inl)

configure_file(
    ${XLIB_TEMPLATES_DIR}/Platform/Bsd/[Class]_bsd.inl.in
    ${XLIB_LOCATION}/Include/xLib/${XLIB_TEMPLATE_SUBDIR}/Platform/Bsd/${XLIB_TEMPLATE}_bsd.inl)

configure_file(
    ${XLIB_TEMPLATES_DIR}/Platform/Apple/[Class]_apple.inl.in
    ${XLIB_LOCATION}/Include/xLib/${XLIB_TEMPLATE_SUBDIR}/Platform/Apple/${XLIB_TEMPLATE}_apple.inl)
#--------------------------------------------------------------------------------------------------
