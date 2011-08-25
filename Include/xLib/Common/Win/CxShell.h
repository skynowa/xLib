/**
 * \file  CxShell.h
 * \brief shell
 */


#ifndef xLib_Common_Win_CxShellH
#define xLib_Common_Win_CxShellH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#if defined(xOS_WIN)
    #include <shellapi.h>
    #include <shlwapi.h>
    #include <shlobj.h>
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
class CxShell :
    public CxNonCopyable
{
     public:
        //operations
        enum EOperation {
            opEdit,        //Launches an editor and opens the document for editing. If lpFile is not a document file, the function will fail.
            opExplore,    //Explores a folder specified by lpFile
            opFind,        //Initiates a search beginning in the directory specified by lpDirectory
            opOpen,        //Opens the item specified by the lpFile parameter. The item can be a file or folder
            opPrint,    //Prints the file specified by lpFile. If lpFile is not a document file, the function fails
            opNull        //
        };

        //The flags that specify how an application is to be displayed when it is opened
        enum EShowFlag {
            sfHide            = SW_HIDE,            //Hides the window and activates another window
            sfMaximize        = SW_MAXIMIZE,        //Maximizes the specified window
            sfMinimize        = SW_MINIMIZE,        //Minimizes the specified window and activates the next top-level window in the z-order
            sfRestore         = SW_RESTORE,            //Activates and displays the window
            sfShow            = SW_SHOW,            //Activates the window and displays it in its current size and position
            sfShowDefault     = SW_SHOWDEFAULT,        //Sets the show state based on the sf flag specified in the STARTUPINFO structure passed to the CreateProcess function by the program that started the application
            sfShowMaximized   = SW_SHOWMAXIMIZED,    //Activates the window and displays it as a maximized window
            sfShowMinimized   = SW_SHOWMINIMIZED,    //Activates the window and displays it as a minimized window
            sfShowMinNoActive = SW_SHOWMINNOACTIVE,    //Displays the window as a minimized window
            sfShowNa          = SW_SHOWNA,            //Displays the window in its current state
            sfShowNoActivate  = SW_SHOWNOACTIVATE,    //Displays a window in its most recent size and position
            sfShowNormal      = SW_SHOWNORMAL        //Activates and displays a window
        };

        //special folders
        enum ESpecialDir {
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
            sfCommonFavorites         = CSIDL_COMMON_FAVORITES,
            sfCommonMusic             = CSIDL_COMMON_MUSIC,
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
            ////TODO: G++ sfMyDocuments            = CSIDL_MYDOCUMENTS,
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

        static std::tstring bFindExecutable   (const std::tstring csFileName, const std::tstring csFindDirPath);
        static BOOL    bExecute          (HWND hOwner, EOperation opOperation, const std::tstring &csFilePath, const std::tstring &csParams, const std::tstring &csDir, EShowFlag sfShowCmd);
        static BOOL    bExecuteEx        (SHELLEXECUTEINFO *peiInfo);
        static BOOL    bExecuteHttp      (const std::tstring &csUrl);
        static BOOL    bExecuteFtp       (const std::tstring &csUrl);
        static BOOL    bExecuteEmail     (const std::tstring &csToEmail, const std::tstring &csSubject, const std::tstring &csBody);
        static std::tstring sGetSpecialDirPath(ESpecialDir sfDir, HANDLE hToken);
        static BOOL    bCreateShortcut   (const std::tstring &csFilePath, const std::tstring &csShortCutPath, const std::tstring &csDescription);

    private:
        static   BOOL  _ms_bRes;

                       CxShell           ();
        virtual       ~CxShell           ();
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif //xLib_Common_Win_CxShellH
