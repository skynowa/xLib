/**
 * \file  CxWindow.h
 * \brief base class for windows controls
 */


#ifndef xLib_Gui_CxWindowH
#define xLib_Gui_CxWindowH
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)

#include <xLib/Common/xClosure.h>
#include <xLib/Gui/xCommon.h>
#include <xLib/Gui/xMessageMap.h>
#include <xLib/Gui/CxApplication.h>
#include <xLib/Gui/CxFont.h>
#include <xLib/Gui/CxStyle.h>
//---------------------------------------------------------------------------
class CxWindow :
    public CxNonCopyable
    /// base class for windows controls
{
    public:
        CxFont            m_fnFont;            //�����
        CxStyle           m_stStyle;

                          CxWindow           ();
        virtual          ~CxWindow           () = 0;


        virtual LRESULT   lpProcessMsg       (UINT uiMsg, WPARAM wParam, LPARAM lParam);

        BOOL              bIsWindow          () const;
        //CxWindow       *pGetParentWnd      () const;
        //BOOL            bSetParentWnd      ();

        //������
        HWND              hGetHandle         () const;
        BOOL              bSetHandle         (HWND hWnd);
        INT               iGetID             () const;
        BOOL              bSetID             (INT iID);
        tString           sGetClassName      () const;
        BOOL              bSetClassName      (const tString &csClassName);
        //HWND            _m_hParentWnd;            //����� ������������� ����
        tString           sGetText           () const;
        BOOL              bSetText           (const tString &csText);
        //INT             _m_iLeft,  _m_iTop;        //���������� ����
        //INT             _m_iWidth, _m_iHeight;    //������� ����

        //��������
        BOOL              bCreate            (INT iID, HWND hParent, const tString &csClassName, const tString &csText,
                                              INT iLeft, INT iTop, INT iWidth, INT iHeight, ULONG ulStyle, ULONG ulStyleEx, LPVOID lpParam);
        BOOL              bCreate            (INT iID, CxWindow *pwndParent, const tString &csClassName, const tString &csText,
                                              INT iLeft, INT iTop, INT iWidth, INT iHeight, ULONG ulStyle, ULONG ulStyleEx, LPVOID lpParam);
        BOOL              bCreateRes         (INT iID, HWND hParent);
        //BOOL            bCreateRes         (INT iID, CxWindow *pwndParent);

        //��������
        BOOL              bShow              (INT iCmdShow) const;
        BOOL              bUpdate            () const;
        BOOL              bMove              (INT iLeft, INT iTop, INT iWidth, INT iHeight);
        BOOL              bMoveCenter        (HWND hParentWnd);
        BOOL              bSetPos            (INT iLeft, INT iTop, INT iWidth, INT iHeight, UINT uiFlags);
        BOOL              bEnable            (BOOL bFlag) const;
        BOOL              bSetActive         () const;
        BOOL              bSetRedraw         (BOOL bFlag) const;
        BOOL              bInvalidateRect    (const RECT *prcRect, BOOL bErase) const;
        BOOL              bDestroy           () const;
        BOOL              bClose             ();

        //������� ���������
        LRESULT           pSendMessage       (UINT uiMsg, WPARAM wParam, LPARAM lParam) const;
        BOOL              bPostMessage       (UINT uiMsg, WPARAM wParam, LPARAM lParam) const;

        //���������
        LONG              liGetWindowLong    (INT iIndex);
        LONG              liSetWindowLong    (INT iIndex, LONG liNewLong);

        virtual VOID      vOnClick           () {/*iMsgBox(xT(__FUNCTION__);*/}
        virtual VOID      vOnDbClick         () {/*iMsgBox(xT(__FUNCTION__);*/}
        virtual VOID      vOnKillFocus       () {/*iMsgBox(xT(__FUNCTION__);*/}
        virtual VOID      vOnSetFocus        () {/*iMsgBox(xT(__FUNCTION__);*/}

    protected:
        HWND              _m_hWnd;                //����� ����
        INT               _m_iID;                //������������� ��������    /*SHORT*/
        tString           _m_sClassName;        //����� ����, ��������
        HWND              _m_hParentWnd;        //����� ������������� ����
        tString           _m_sText;                //����� ����
        INT               _m_iLeft,  _m_iTop;    //���������� ����
        INT               _m_iWidth, _m_iHeight;//������� ����
        ULONG             _m_ulStyle;            //����� ����
        ULONG             _m_ulStyleEx;            //����������� ����� ����
        ////INT           _m_iMenu;                //����

        CxWindow         *_m_pwndParent;


        BOOL              _m_bIsControl;        //�������� �� ���� ���������
        mutable BOOL      _m_bRes;
        static CxTraceLog _m_tlLog;                //���

        static LRESULT    _s_pWndProc         (HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);   //������� ����
        static BOOL       _bInitCommonControls(ULONG ulFlags);
        static BOOL       _bRegisterClass     (const WNDCLASSEX *cpwcWndClassEx);
        static BOOL       _bUnregisterClass   (const tString &csClassName);
        //Attach, Detach

    private:

};
#endif
//---------------------------------------------------------------------------
#endif    //xLib_Gui_CxWindowH



/*
GetDlgCtrlID
*/
