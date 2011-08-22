/****************************************************************************
* Class name:  CxButtonBase
* Description: ������ � �������
* File name:   CxButtonBase.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     23.07.2009 13:11:14
*
*****************************************************************************/


#ifndef XLib_Gui_CxButtonBaseH
#define XLib_Gui_CxButtonBaseH
//---------------------------------------------------------------------------
#include <xLib/Gui/xCommon.h>
#include <xLib/Gui/CxWindow.h>
//---------------------------------------------------------------------------
class CxButtonBase : public CxWindow {
    public:
        //-------------------------------------
        //���������

        //������������ ������
        enum ETextAligment {
            taLeft    = BS_LEFT,
            taTop     = BS_TOP,
            taRight   = BS_RIGHT,
            taBottom  = BS_BOTTOM,
            taHCenter = BS_CENTER,
            taVCenter = BS_VCENTER
        };

                 CxButtonBase    ();
        virtual ~CxButtonBase    () = 0;

        ////BOOL bCreateRes       (INT iID, CxWindow *pwndParent);

        //-------------------------------------
        //���������
        BOOL     bSetAlignment   (ETextAligment taTextAligment);
        BOOL     bSetNotify      (BOOL bFlag);
        BOOL     bSetFlat        (BOOL bFlag);
        BOOL     bSetMultiLine   (BOOL bFlag);
        BOOL     bClick          ();

        //-------------------------------------
        //�������
        VOID     vSet_OnClick    (SClosureT<VOID(CxButtonBase *pbtnSender)> vCallback);
        VOID     vSet_OnDbClick  (SClosureT<VOID(CxButtonBase *pbtnSender)> vCallback);
        VOID     vSet_OnKillFocus(SClosureT<VOID(CxButtonBase *pbtnSender)> vCallback);
        VOID     vSet_OnSetFocus (SClosureT<VOID(CxButtonBase *pbtnSender)> vCallback);

    private:
        virtual VOID vOnClick    () { _vHandler_OnClick    (this); }
        virtual VOID vOnDbClick  () { _vHandler_OnDbClick  (this); }
        virtual VOID vOnKillFocus() { _vHandler_OnKillFocus(this); }
        virtual VOID vOnSetFocus () { _vHandler_OnSetFocus (this); }


        //callback ������
        SClosureT<VOID(CxButtonBase *pthSender)> _m_vCallback_OnClick;
        VOID                                     _vHandler_OnClick(CxButtonBase *pthSender);

        SClosureT<VOID(CxButtonBase *pthSender)> _m_vCallback_OnDbClick;
        VOID                                     _vHandler_OnDbClick(CxButtonBase *pthSender);

        SClosureT<VOID(CxButtonBase *pthSender)> _m_vCallback_OnKillFocus;
        VOID                                     _vHandler_OnKillFocus(CxButtonBase *pthSender);

        SClosureT<VOID(CxButtonBase *pthSender)> _m_vCallback_OnSetFocus;
        VOID                                     _vHandler_OnSetFocus(CxButtonBase *pthSender);
};
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxButtonBaseH







//GetParent()->PostMessage (WM_COMMAND, MAKELONG (GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
