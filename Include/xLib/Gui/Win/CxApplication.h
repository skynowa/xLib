/**
 * \file  CxApplication.h
 * \brief application
 */


//---------------------------------------------------------------------------
#ifndef xLib_Gui_CxApplication_H
#define xLib_Gui_CxApplication_H
//---------------------------------------------------------------------------
//--#include <xLib/GUI/CxWindow.h>
#include <xLib/Gui/xCommon.h>
//--#include <xLib/Gui/CxResources.h>
#include <vector>
//---------------------------------------------------------------------------
class CxApplication :
	public CxNonCopyable
{
    public:
        static BOOL      bInit           (HINSTANCE hInstance, const tString &csCmdLine);
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
