/****************************************************************************
* Class name:  CxWndsContainer
* Description: контейнер для окон
* File name:   CxWndsContainer.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     16.03.2010 15:42:54
*
*****************************************************************************/


#ifndef XLib_Gui_CxWndsContainerH
#define XLib_Gui_CxWndsContainerH
//---------------------------------------------------------------------------
#include <xLib/xCommon.h>
#include <xLib/Gui/CxWindow.h>
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
