/**
 * \file  CxToolBar.h
 * \brief toolbar
 */


#ifndef XLib_Gui_CxToolBarH
#define XLib_Gui_CxToolBarH
//---------------------------------------------------------------------------
#include <xLib/GUI/CxWindow.h>
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
class CxToolBar :
    public CxWindow
    /// toolbar
{
    public:
         CxToolBar ();
        ~CxToolBar();

        //������ ������
        HWND Create(HWND hParentWnd,
                    DWORD tbStyle,
                    DWORD tbExStyle,
                    UINT tbID,//ID �������
                    INT nBitmaps,//����������� �������� � �������(������/������)
                    UINT_PTR wBMID,//ID ������� ������� ��� �������
                    INT dxButton,//������ ������
                    INT dyButton,//������ ������
                    INT dxBitmap,//������ �������� ��� ������
                    INT dyBitmap);//������ �������� ��� ������
        //��������� ������
        INT AddButton(INT nBitmap,//����� �������� ��� ������� (������/������, ���� ����� �������)
                    INT idCommand,//ID ��������(������)
                    BYTE btnState,//��������� ������
                    BYTE btnStyle,//����� ������
                    DWORD_PTR dwData,
                    INT_PTR iString,//������� ��� ������
                    TCHAR* szTTip,//������ ��� ������
                    INT idMenu);//ID ������������ ���� ��� ������(���� btnStyle==BTNS_DROPDOWN)
        //��������� ������
        INT InsertButton(INT nInto,//���� ��������
                    INT nBitmap,
                    INT idCommand,
                    BYTE btnState,
                    BYTE btnStyle,
                    DWORD_PTR dwData,
                    INT_PTR iString,
                    TCHAR* szTTip,
                    INT idMenu);
        //���������� WM_NOTIFY
        VOID DoNotify(LPARAM lParam);//�������� � ���������� WM_NOTIFY ���� ��������
        //���������� WM_SIZE
        VOID AutoSize();//�������� � ���������� WM_SIZE ���� ��������
        //������� ��������� ������
        INT DeleteButton(INT nButton);

    protected:
        struct ULTB_INFO_BUTTONS {
            TCHAR* szToolTip;
            INT idCommand;
            INT idMenu;
            INT nBitmap;
        } *m_InfoButtons;

        INT       m_nBitmaps;
        INT       m_nButtons;
        HINSTANCE m_hInstance;
};
#endif
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxToolBarH
