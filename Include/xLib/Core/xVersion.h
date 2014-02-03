/**
 * \file  xVersion.h
 * \brief xLib information
 */


#pragma once

#ifndef xLib_xVersionH
#define xLib_xVersionH
//-------------------------------------------------------------------------------------------------
#define xLIB_NAME           xT("xLib")
    ///< xLib name
#define xLIB_DESCRIPTION    xT("C++ cross-platform library")
    ///< xLib description
#define xLIB_VERSION        xT("1.0.000")
    ///< xLib version

#if xHAVE_GIT_REVISION
    #define xLIB_GIT_REVISION_BRANCH  xGIT_REVISION_BRANCH
        ///< xLib Git revision branch
    #define xLIB_GIT_REVISION_HASH    xGIT_REVISION_HASH
        ///< xLib Git revision hash
#endif

#define xLIB_VERSION_SUFFIX xT("Alpha")
    ///< xLib suffix version
#define xLIB_DATE           xDATETIME
    ///< xLib build datetime stamp

#define xLIB_AUTHOR         xT("Skynowa")
    ///< xLib author
#define xLIB_HOME_PAGE      xT("https://bitbucket.org/skynowa/xlib")
    ///< xLib home page
#define xLIB_EMAIL          xT("skynowa@gmail.com")
    ///< xLib email
#define xLIB_JABBER         xT("skynowa@jabber.ru")
    ///< xLib jabber
#define xLIB_SKYPE          xT("skynowa777")
    ///< xLib skype
//-------------------------------------------------------------------------------------------------
#endif // xLib_xVersionH
