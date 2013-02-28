/**
 * \file  CxShell.h
 * \brief shell
 */


#ifndef xLib_Common_Win_CxShellH
#define xLib_Common_Win_CxShellH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if xOS_ENV_WIN
    #include <shellapi.h>
    #include <shlwapi.h>
    #include <shlobj.h>
#endif
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxShell :
    private CxNonCopyable
    /// shell
{
public:
    static bool_t           isAvailable   () xWARN_UNUSED_RV;
    static void           execute       (std::ctstring_t &csFilePath, std::ctstring_t &csParams);

#if   xOS_ENV_WIN
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

    static std::tstring_t findExecutable(std::ctstring_t &csFileName, std::ctstring_t &csFindDirPath) xWARN_UNUSED_RV;
        ///< find executable file path
    static void           execute       (const HWND &chOwner, const ExOperation &copOperation,
                                         std::ctstring_t &csFilePath, std::ctstring_t &csParams,
                                         std::ctstring_t &csDir, const EShowFlag &csfShowCmd);
        ///< execute
    static void           executeEx     (SHELLEXECUTEINFO *peiInfo);
        ///< execute
    static void           executeHttp   (std::ctstring_t &csUrl);
        ///< execute HTTP
    static void           executeFtp    (std::ctstring_t &csUrl);
        ///< execute FTP
    static void           executeEmail  (std::ctstring_t &csToEmail, std::ctstring_t &csSubject, std::ctstring_t &csBody);
        ///< execute email
    static std::tstring_t specialDirPath(const ESpecialDir &csfDir, const HANDLE &chToken) xWARN_UNUSED_RV;
        ///< get special dir path
    static void           createShortcut(std::ctstring_t &csShortCutFilePath,
                                         std::ctstring_t &csFilePath,
                                         std::ctstring_t &csWorkingDirectory,
                                         std::ctstring_t &csArguments,
                                         const WORD           &cwHotKey,
                                         cint_t            &ciCmdShow,
                                         std::ctstring_t &csIconFilePath,
                                         cint_t            &ciIconIndex,
                                         std::ctstring_t &csDescription);
        ///< create shortcut
#endif

private:
                          CxShell       ();
        ///< constructor
    virtual              ~CxShell       ();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Common_Win_CxShellH
