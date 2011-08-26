/**
 * \file  CxWndsContainer.h
 * \brief windows container
 */


#ifndef XLib_Gui_CxWndsContainerH
#define XLib_Gui_CxWndsContainerH
//---------------------------------------------------------------------------
#include <xLib/xCommon.h>
#include <xLib/Gui/CxWindow.h>
//---------------------------------------------------------------------------
class CxWndsContainer : 
    public CxNonCopyable 
    /// windows container
{
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
