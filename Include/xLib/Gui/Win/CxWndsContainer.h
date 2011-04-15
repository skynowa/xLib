/****************************************************************************
* Class name:  CxWndsContainer
* Description: контейнер для окон
* File name:   CxWndsContainer.h
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     16.03.2010 15:42:54
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef XLib_Gui_CxWndsContainerH
#define XLib_Gui_CxWndsContainerH
//---------------------------------------------------------------------------
#include <XLib/xCommon.h>
#include <XLib/Gui/CxWindow.h>
//---------------------------------------------------------------------------
class CxWndsContainer : public CxNonCopyable {
	public:
			      CxWndsContainer();
			     ~CxWndsContainer();

		BOOL      bAdd           (CxWindow *pwndCtrl);
		BOOL      bRemove        (CxWindow *pwndCtrl);
		CxWindow *pwndGet        (UINT uiIndex);
		UINT      uiGetSize      ();

	private:
		std::vector<CxWindow *>  _m_vecpWnds;
};
//---------------------------------------------------------------------------
#endif //XLib_Gui_CxWndsContainerH
