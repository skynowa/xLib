/**
 * \file  CxShell.h
 * \brief shell
 */


#pragma once

#ifndef xLib_CxShellH
#define xLib_CxShellH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>

#if xENV_WIN
    #include <shellapi.h>
    #include <shlwapi.h>
    #include <shlobj.h>
#endif
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, system)

class CxShell
    /// shell
{
public:
               CxShell() {}
        ///< constructor
    virtual   ~CxShell() {}
        ///< destructor

    bool_t     isAvailable() const xWARN_UNUSED_RV;
        ///< is available
    void_t     execute(std::ctstring_t &filePath, std::ctstring_t &params) const;
        ///< execute file

#if xENV_WIN
    enum ExOperation
        /// operations
    {
        opEdit,
        opExplore,
        opFind,
        opOpen,
        opPrint,
        opNull
    };

    enum EShowFlag
        /// The flags that specify how an application is to be displayed when it is opened
    {
        sfHide            = SW_HIDE,
        sfMaximize        = SW_MAXIMIZE,
        sfMinimize        = SW_MINIMIZE,
        sfRestore         = SW_RESTORE,
        sfShow            = SW_SHOW,
        sfShowDefault     = SW_SHOWDEFAULT,
        sfShowMaximized   = SW_SHOWMAXIMIZED,
        sfShowMinimized   = SW_SHOWMINIMIZED,
        sfShowMinNoActive = SW_SHOWMINNOACTIVE,
        sfShowNa          = SW_SHOWNA,
        sfShowNoActivate  = SW_SHOWNOACTIVATE,
        sfShowNormal      = SW_SHOWNORMAL
    };

    enum ESpecialDir
        /// special folders
    {
        sfAdminTools             = CSIDL_ADMINTOOLS,
        sfAltStartup             = CSIDL_ALTSTARTUP,
        sfAppData                = CSIDL_APPDATA,
        sfBitbucket              = CSIDL_BITBUCKET,
        sfCDBurnArea             = CSIDL_CDBURN_AREA,
        sfCommonAdminTools       = CSIDL_COMMON_ADMINTOOLS,
        sfCommonAltStartup       = CSIDL_COMMON_ALTSTARTUP,
        sfCommonAppData          = CSIDL_COMMON_APPDATA,
        sfCommonDesktopDirectory = CSIDL_COMMON_DESKTOPDIRECTORY,
        sfCommonDocuments        = CSIDL_COMMON_DOCUMENTS,
        sfCommonFavorites        = CSIDL_COMMON_FAVORITES,
        sfCommonMusic            = CSIDL_COMMON_MUSIC,
        sfCommonOemLinks         = CSIDL_COMMON_OEM_LINKS,
        sfCommonPictures         = CSIDL_COMMON_PICTURES,
        sfCommonPrograms         = CSIDL_COMMON_PROGRAMS,
        sfCommonStartmenu        = CSIDL_COMMON_STARTMENU,
        sfCommonStartup          = CSIDL_COMMON_STARTUP,
        sfCommonTemplates        = CSIDL_COMMON_TEMPLATES,
        sfCommonVideo            = CSIDL_COMMON_VIDEO,
        sfComputersNearMe        = CSIDL_COMPUTERSNEARME,
        sfConnections            = CSIDL_CONNECTIONS,
        sfControls               = CSIDL_CONTROLS,
        sfCookies                = CSIDL_COOKIES,
        sfDesktop                = CSIDL_DESKTOP,
        sfDesktopDirectory       = CSIDL_DESKTOPDIRECTORY,
        sfDrives                 = CSIDL_DRIVES,
        sfFavorites              = CSIDL_FAVORITES,
        sfFonts                  = CSIDL_FONTS,
        sfHistory                = CSIDL_HISTORY,
        sfInternet               = CSIDL_INTERNET,
        sfInternetCache          = CSIDL_INTERNET_CACHE,
        sfLocalAppData           = CSIDL_LOCAL_APPDATA,
    #if xCOMPILER_MS || xCOMPILER_CODEGEAR
        sfMyDocuments            = CSIDL_MYDOCUMENTS,
    #endif
        sfMyMusic                = CSIDL_MYMUSIC,
        sfMyPictures             = CSIDL_MYPICTURES,
        sfMyVideo                = CSIDL_MYVIDEO,
        sfNetHood                = CSIDL_NETHOOD,
        sfNetWork                = CSIDL_NETWORK,
        sfPersonal               = CSIDL_PERSONAL,
        sfPrinters               = CSIDL_PRINTERS,
        sfPrintHood              = CSIDL_PRINTHOOD,
        sfProfile                = CSIDL_PROFILE,
        sfProgramFiles           = CSIDL_PROGRAM_FILES,
        sfProgramFilesx86        = CSIDL_PROGRAM_FILESX86,
        sfProgramFiles_common    = CSIDL_PROGRAM_FILES_COMMON,
        sfProgramFiles_commonx86 = CSIDL_PROGRAM_FILES_COMMONX86,
        sfPrograms               = CSIDL_PROGRAMS,
        sfRecent                 = CSIDL_RECENT,
        sfResources              = CSIDL_RESOURCES,
        sfResourcesLocalized     = CSIDL_RESOURCES_LOCALIZED,
        sfSendTo                 = CSIDL_SENDTO,
        sfStartMenu              = CSIDL_STARTMENU,
        sfStartup                = CSIDL_STARTUP,
        sfSystem                 = CSIDL_SYSTEM,
        sfSystemx86              = CSIDL_SYSTEMX86,
        sfTemplates              = CSIDL_TEMPLATES,
        sfWindows                = CSIDL_WINDOWS
    };

    std::tstring_t findExecutable(std::ctstring_t &fileName, std::ctstring_t &findDirPath) const
                       xWARN_UNUSED_RV;
        ///< find executable file path
    void_t         execute(const HWND &owner, const ExOperation &operation,
                       std::ctstring_t &filePath, std::ctstring_t &params, std::ctstring_t &dirPath,
                       const EShowFlag &showCmd) const;
        ///< execute
    void_t         executeEx(SHELLEXECUTEINFO &info) const;
        ///< execute
    void_t         executeHttp(std::ctstring_t &url) const;
        ///< execute HTTP
    void_t         executeFtp(std::ctstring_t &url) const;
        ///< execute FTP
    void_t         executeEmail(std::ctstring_t &toEmail, std::ctstring_t &subject,
                       std::ctstring_t &body) const;
        ///< execute email
    std::tstring_t specialDirPath(const ESpecialDir &dir, const HANDLE &token) const
                       xWARN_UNUSED_RV;
        ///< get special dir path
    void_t         createShortcut(std::ctstring_t &shortCutFilePath, std::ctstring_t &filePath,
                       std::ctstring_t &workingDirectory, std::ctstring_t &args, const WORD &hotKey,
                       cint_t &cmdShow, std::ctstring_t &iconFilePath, cint_t &iconIndex,
                       std::ctstring_t &description) const;
        ///< create shortcut
#endif

    xNO_COPY_ASSIGN(CxShell)
};

xNAMESPACE2_END(xlib, system)
//-------------------------------------------------------------------------------------------------
#include "CxShell.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxShellH
