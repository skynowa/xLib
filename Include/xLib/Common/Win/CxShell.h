/**
 * \file  CxShell.h
 * \brief shell
 */


#ifndef xLib_Common_Win_CxShellH
#define xLib_Common_Win_CxShellH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if defined(xOS_ENV_WIN)
    #include <shellapi.h>
    #include <shlwapi.h>
    #include <shlobj.h>
#endif
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)

class CxShell :
    public CxNonCopyable
    /// shell
{
     public:
        enum EOperation
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
		#if defined(xCOMPILER_MS) || defined(xCOMPILER_CODEGEAR)
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

        static std::string_t bFindExecutable   (const std::string_t &csFileName, const std::string_t &csFindDirPath);
        	///< find executable file path
        static BOOL         bExecute          (const HWND chOwner, const EOperation copOperation, const std::string_t &csFilePath, const std::string_t &csParams, const std::string_t &csDir, const EShowFlag csfShowCmd);
        	///< execute
        static BOOL         bExecuteEx        (SHELLEXECUTEINFO *peiInfo);
        	///< execute
        static BOOL         bExecuteHttp      (const std::string_t &csUrl);
        	///< execute HTTP
        static BOOL         bExecuteFtp       (const std::string_t &csUrl);
        	///< execute FTP
        static BOOL         bExecuteEmail     (const std::string_t &csToEmail, const std::string_t &csSubject, const std::string_t &csBody);
        	///< execute email
        static std::string_t sGetSpecialDirPath(const ESpecialDir csfDir, const HANDLE chToken);
        	///< get special dir path
        static BOOL         bCreateShortcut   (const std::string_t &csShortCutFilePath,
                                               const std::string_t &csFilePath,
                                               const std::string_t &csWorkingDirectory,
                                               const std::string_t &csArguments,
                                               const WORD          cwHotKey,
                                               const INT           ciCmdShow,
                                               const std::string_t &csIconFilePath,
                                               const INT           ciIconIndex,
                                               const std::string_t &csDescription
                                              );
        	///< create shortcut

    private:
                            CxShell           ();
            ///< constructor
        virtual            ~CxShell           ();
        	///< destructor
};

#endif
//---------------------------------------------------------------------------
#endif //xLib_Common_Win_CxShellH
