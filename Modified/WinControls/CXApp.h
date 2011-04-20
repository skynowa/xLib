/****************************************************************************
*	CXApp
*
*****************************************************************************/


//---------------------------------------------------------------------------
#ifndef CXApp_H
#define CXApp_H
//---------------------------------------------------------------------------
#include <windows.h>
#include "CXWnd.h"
//---------------------------------------------------------------------------
class CXApp: public CXWnd { //MainFrm
	public:
		          CXApp              ();
		BOOL      bCreate            (HINSTANCE hInstance, INT nCmdShow);
		BOOL      bCreateRes         (HINSTANCE hInstance, INT iResID, INT iCmdShow);
		VOID      vRun               ();
		HICON     hIcon              ();
		VOID      vIcon              (HICON hIcon);
		HACCEL    hAccelerators      ();
		VOID      vAccelerators      (HACCEL hAccel);
		BOOL      bIsMaximized       ();
		VOID      vProcessMessages   ();
		BOOL      bSetPosScreenCenter();

    protected:
		HINSTANCE _m_hInstance;
		HICON     _m_hIcon;
		HACCEL    _m_hAccel;
	
	private:
};
//---------------------------------------------------------------------------
#endif