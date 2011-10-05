/**
 * \file  CxButton.h
 * \brief button
 */


#ifndef XLib_Gui_CxButtonH
#define XLib_Gui_CxButtonH
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
#include <xLib/Gui/Win/xCommon.h>
#include <xLib/Gui/Win/CxWindow.h>
#include <xLib/GUI/Win/CxButtonBase.h>
//---------------------------------------------------------------------------
class CxButton :
    public CxButtonBase
    /// button
{
    public:
        //-------------------------------------
        //���������

        //����� (�����������/�����)
        enum EViewStyle {
            vsText     = BS_TEXT,
            vsBitmap   = BS_BITMAP,
            vsIcon     = BS_ICON
        };

        //��� �����������
        enum EImageType {
            itBitmap   = IMAGE_BITMAP,
            itIcon       = IMAGE_ICON,
            itCursor   = IMAGE_CURSOR,
            itMetaFile = IMAGE_ENHMETAFILE
        };

                 CxButton        ();
        virtual ~CxButton        ();

        BOOL     bCreateRes      (INT iID, CxWindow *pwndParent);

        //-------------------------------------
        //���������
        BOOL     bSetViewStyle   (EViewStyle vsViewStyle);
        BOOL     bSetImage       (EImageType itImageType, HANDLE hImage);

        //-------------------------------------
        //�������
        VOID     vSet_OnClick    (SClosureT<VOID(CxButton *pbtnSender)> vCallback);
        VOID     vSet_OnDbClick  (SClosureT<VOID(CxButton *pbtnSender)> vCallback);
        VOID     vSet_OnKillFocus(SClosureT<VOID(CxButton *pbtnSender)> vCallback);
        VOID     vSet_OnSetFocus (SClosureT<VOID(CxButton *pbtnSender)> vCallback);

    private:
        EViewStyle _m_vsViewStyle;

        virtual void vOnClick    () { _vHandler_OnClick    (this); }
        virtual void vOnDbClick  () { _vHandler_OnDbClick  (this); }
        virtual void vOnKillFocus() { _vHandler_OnKillFocus(this); }
        virtual void vOnSetFocus () { _vHandler_OnSetFocus (this); }


        //callback ������
        SClosureT<VOID(CxButton *pthSender)> _m_vCallback_OnClick;
        VOID                                 _vHandler_OnClick(CxButton *pthSender);

        SClosureT<VOID(CxButton *pthSender)> _m_vCallback_OnDbClick;
        VOID                                 _vHandler_OnDbClick(CxButton *pthSender);

        SClosureT<VOID(CxButton *pthSender)> _m_vCallback_OnKillFocus;
        VOID                                 _vHandler_OnKillFocus(CxButton *pthSender);

        SClosureT<VOID(CxButton *pthSender)> _m_vCallback_OnSetFocus;
        VOID                                 _vHandler_OnSetFocus(CxButton *pthSender);
};
#endif
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxButtonH












//GetParent()->PostMessage (WM_COMMAND, MAKELONG (GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);,
