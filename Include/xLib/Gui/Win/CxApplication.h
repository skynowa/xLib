/****************************************************************************
* Class name:  CxApplication
* Description: работа с приложением
* File name:   CxApplication.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     23.07.2009 13:08:45
*
*****************************************************************************/


//---------------------------------------------------------------------------
#ifndef xLib_Gui_CxApplication_H
#define xLib_Gui_CxApplication_H
//---------------------------------------------------------------------------
//--#include <xLib/GUI/CxWindow.h>
#include <xLib/Gui/xCommon.h>
//--#include <xLib/Gui/CxResources.h>
#include <vector>
//---------------------------------------------------------------------------
class CxApplication : public CxNonCopyable { 
    public:
        static BOOL         bInit           (HINSTANCE hInstance, const tString &csCmdLine);
        static HINSTANCE hGetInstance    ();
        static BOOL      bGetCmdLine     (std::vector<std::wstring> *pvecwsCmdLine); 
        static VOID      vProcessMessages();
        static BOOL      bRun            ();
        static BOOL      bIsRunning      (const tString &csInstanceName);
        static VOID      vTerminate      ();

        static VOID      vCreateWnd      ();

    private:
        static HINSTANCE _m_hInstance;

                         CxApplication   ();
                        ~CxApplication   ();
};
//---------------------------------------------------------------------------
#endif    //xLib_Gui_CxApplication_H