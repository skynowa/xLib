/**
 * \file  CxShell.h
 * \brief shell
 */


#ifndef xLib_Common_Win_CxShellH
#define xLib_Common_Win_CxShellH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if xOS_ENV_WIN
    #include <shellapi.h>
    #include <shlwapi.h>
    #include <shlobj.h>
#endif
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxShell :
    private CxNonCopyable
    /// shell
{
public:
    static bool           isAvailable   ();
    static void           execute       (const std::tstring_t &csFilePath, const std::tstring_t &csParams);

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

    static std::tstring_t findExecutable(const std::tstring_t &csFileName, const std::tstring_t &csFindDirPath);
        ///< find executable file path
    static void           execute       (const HWND &chOwner, const ExOperation &copOperation, const std::tstring_t &csFilePath, const std::tstring_t &csParams, const std::tstring_t &csDir, const EShowFlag &csfShowCmd);
        ///< execute
    static void           executeEx     (SHELLEXECUTEINFO *peiInfo);
        ///< execute
    static void           executeHttp   (const std::tstring_t &csUrl);
        ///< execute HTTP
    static void           executeFtp    (const std::tstring_t &csUrl);
        ///< execute FTP
    static void           executeEmail  (const std::tstring_t &csToEmail, const std::tstring_t &csSubject, const std::tstring_t &csBody);
        ///< execute email
    static std::tstring_t specialDirPath(const ESpecialDir &csfDir, const HANDLE &chToken);
        ///< get special dir path
    static void           createShortcut(const std::tstring_t &csShortCutFilePath,
                                         const std::tstring_t &csFilePath,
                                         const std::tstring_t &csWorkingDirectory,
                                         const std::tstring_t &csArguments,
                                         const WORD           &cwHotKey,
                                         const int            &ciCmdShow,
                                         const std::tstring_t &csIconFilePath,
                                         const int            &ciIconIndex,
                                         const std::tstring_t &csDescription);
        ///< create shortcut
#endif

private:
                          CxShell       ();
        ///< constructor
    virtual              ~CxShell       ();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Common_Win_CxShellH
