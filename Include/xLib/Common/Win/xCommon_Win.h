/****************************************************************************
* Class name:  xCommon_Win
* Description: Windows common header for xLib
* File name:   xCommon_Win.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     23.12.2010 23:25:16
*
*****************************************************************************/


#ifndef xLib_Common_Win_xCommon_WinH
#define xLib_Common_Win_xCommon_WinH
//---------------------------------------------------------------------------
//win version
#define xWINVER      WINVER

#define xWIN32_NT4   0x0400    //Windows NT 4.0
#define xWIN32_2K    0x0500    //Windows 2000
#define xWIN32_XP    0x0501    //Windows Server 2003, Windows XP
#define xWIN32_S03   0x0502    //Windows Server 2003 with SP1, Windows XP with SP2
#define xWIN32_VISTA 0x0600    //Windows Vista, Windows Server 2008
#define xWIN32_7     0x0601    //Windows 7, Windows Server 2008 R2
//---------------------------------------------------------------------------
//Remove pointless warning messages
#if defined(xCOMPILER_MINGW32) || defined(xCOMPILER_MS)
    ////#pragma warning (disable : 4511)    //copy operator could not be generated
    ////#pragma warning (disable : 4512)    //assignment operator could not be generated
    ////#pragma warning (disable : 4702)    //unreachable code (bugs in Microsoft's STL)
    ////#pragma warning (disable : 4786)    //identifier was truncated
    #pragma warning (disable : 4996)        //function or variable may be unsafe (deprecated)
    #pragma warning (disable : 4355)        //'this' : used in base member initializer list

    #ifndef _CRT_SECURE_NO_WARNINGS
        #define _CRT_SECURE_NO_WARNINGS     //eliminate deprecation warnings for VS2005
    #endif
    ////#define _SECURE_SCL 0

    //Required for VS 2008 (fails on XP and Win2000 without this fix)
    #ifndef _WIN32_WINNT
        #define _WIN32_WINNT 0x0600
    #endif

    #ifdef WINVER
        #undef  WINVER
        #define WINVER 0x0600
    #else
        #define WINVER 0x0600
    #endif

    #ifdef _WIN32_WINNT
        #undef  _WIN32_WINNT
        #define _WIN32_WINNT 0x0600
    #else
        #define _WIN32_WINNT 0x0600
    #endif

#endif // _MSC_VER || __MINGW32__

#if defined(xCOMPILER_CODEGEAR)
    #pragma option -w-8027                //function not expanded inline
    #pragma option -w-8057                //parameter is never used
    #pragma option -w-8058                //cannot create pre-compiled header: initialized data in header
    #pragma option -w-8004                 //is assigned a value that is never used
    #pragma option -w-8022                 //hides virtual function 'Image::Clone()'
    #pragma option -w-8008                 //Condition is always true

    #define xD2S(s)     tString((s).c_str())
    #define xD2AS(s)    tString((s).t_str())
    #define xS2D(s)     String((s).c_str())
    #define xD2WD(s)    WideString((s))

    //xTRY_BOOL
    #define xTRY_BOOL    \
                BOOL bRes = FALSE;  \
                try    {                \
                    {

    #define xCATCH_BOOL_RET    \
                    }    \
                    bRes = TRUE;    \
                } \
                catch (Exception &e) {    \
                    xASSERT_MSG(FALSE, xD2AS(e.Message).c_str());    \
                }                             \
                catch (std::exception e) {   \
                    std::string asWhat = e.what();    \
                    xASSERT_MSG(FALSE, xS2TS(asWhat).c_str());    \
                }    \
                catch (...) {    \
                    xASSERT_MSG(FALSE, xT("Uknown error"));    \
                }    \
                return bRes;

    //xTRY_LONG
    #define xTRY_LONG(ret_error_value)    LONG liRes = ret_error_value;  \
                try    {                \
                    {                \
                        liRes =         \

    #define xCATCH_LONG_RET    \
                    }    \
                }    \
                catch (Exception &e) {    \
                    xASSERT_MSG(FALSE, xD2AS(e.Message).c_str());    \
                }    \
                catch (std::exception e) {    \
                    std::string asWhat = e.what();    \
                    xASSERT_MSG(FALSE, xS2TS(asWhat).c_str());    \
                }    \
                catch (...) {    \
                    xASSERT_MSG(FALSE, xT("Uknown error"));    \
                }    \
                return liRes;

    //xTRY_VARIANT
    #define xTRY_VARIANT(ret_error_value)    Variant vRes = ret_error_value;  \
                try    {                \
                    {                \
                        vRes =         \

    #define xCATCH_VARIANT_RET    \
                    }    \
                }    \
                catch (Exception &e) {    \
                    xASSERT_MSG(FALSE, xD2AS(e.Message).c_str());    \
                }    \
                catch (std::exception e) {    \
                    std::string asWhat = e.what();    \
                    xASSERT_MSG(FALSE, xS2TS(asWhat).c_str());    \
                }    \
                catch (...) {    \
                    xASSERT_MSG(FALSE, xT("Uknown error"));    \
                }    \
                return vRes;

#endif //xCOMPILER_CODEGEAR
//---------------------------------------------------------------------------
//OBM_ (#include <winuser.h>)
#define OEMRESOURCE

#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif

#define _WINSOCKAPI_        //Prevent winsock.h #include's

#include <winsock2.h>
#include <ws2tcpip.h>
////#include <Wspiapi.h>

#include <windows.h>
#include <tchar.h>
#include <windowsx.h>
#include <winuser.h>
#include <Objbase.h>
////#include <shellapi.h>
////#include <registry.hpp>
//---------------------------------------------------------------------------
//For compilers lacking Win64 support
#if xTEMP_DISABLED
    #ifndef  GetWindowLongPtr
        #define GetWindowLongPtr   GetWindowLong
        #define SetWindowLongPtr   SetWindowLong
        #define GWLP_WNDPROC       GWL_WNDPROC
        #define GWLP_HINSTANCE     GWL_HINSTANCE
        #define GWLP_ID            GWL_ID
        #define GWLP_USERDATA      GWL_USERDATA
        #define DWLP_DLGPROC       DWL_DLGPROC
        #define DWLP_MSGRESULT     DWL_MSGRESULT
        #define DWLP_USER          DWL_USER
        #define DWORD_PTR          DWORD
        #define LONG_PTR           LONG
        #define ULONG_PTR          LONG
    #endif
        #ifndef GetClassLongPtr
        #define GetClassLongPtr    GetClassLong
        #define SetClassLongPtr    SetClassLong
        #define GCLP_HBRBACKGROUND GCL_HBRBACKGROUND
        #define GCLP_HCURSOR       GCL_HCURSOR
        #define GCLP_HICON         GCL_HICON
        #define GCLP_HICONSM       GCL_HICONSM
        #define GCLP_HMODULE       GCL_HMODULE
        #define GCLP_MENUNAME      GCL_MENUNAME
        #define GCLP_WNDPROC       GCL_WNDPROC
    #endif
#endif

//Strict
#if !defined(STRICT)
    #define STRICT 1
#endif

//For Visual Studio 6 (without an updated platform SDK) and Dev-C++
#ifndef OPENFILENAME_SIZE_VERSION_400
    #define OPENFILENAME_SIZE_VERSION_400 sizeof(OPENFILENAME)
#endif
//---------------------------------------------------------------------------
#include <xLib/Gui/Win/Dialogs/CxMsgBoxT.h>
//---------------------------------------------------------------------------
#endif  //xLib_Common_Win_xCommon_WinH
