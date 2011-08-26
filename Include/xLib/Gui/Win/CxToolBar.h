/**
 * \file  CxToolBar.h
 * \brief toolbar
 */


#ifndef XLib_Gui_CxToolBarH
#define XLib_Gui_CxToolBarH
//---------------------------------------------------------------------------
#include <xLib/GUI/CxWindow.h>
//---------------------------------------------------------------------------
class CxToolBar : 
    public CxWindow 
    /// toolbar 
{
    public:
         CxToolBar ();
        ~CxToolBar();

        //создаёт тулбар
        HWND Create(HWND hParentWnd,
                    DWORD tbStyle,
                    DWORD tbExStyle,
                    UINT tbID,//ID тулбара
                    INT nBitmaps,//колличество битмапов в тулбаре(ресурс/ширина)
                    UINT_PTR wBMID,//ID ресурса битмапа для тулбара
                    INT dxButton,//ширина кнопки
                    INT dyButton,//высота кнопки
                    INT dxBitmap,//ширина картинки для кнопки
                    INT dyBitmap);//высота картинки для кнопки
        //добавляет кнопку
        INT AddButton(INT nBitmap,//номер картинки для тулбара (ресурс/ширина, счёт слева направо)
                    INT idCommand,//ID контрола(кнопки)
                    BYTE btnState,//состояние кнопки
                    BYTE btnStyle,//стиль кнопки
                    DWORD_PTR dwData,
                    INT_PTR iString,//подпись для кнопки
                    TCHAR* szTTip,//тултип для кнопки
                    INT idMenu);//ID контекстного меню для кнопки(если btnStyle==BTNS_DROPDOWN)
        //вставляет кнопку
        INT InsertButton(INT nInto,//куда вставить
                    INT nBitmap,
                    INT idCommand,
                    BYTE btnState,
                    BYTE btnStyle,
                    DWORD_PTR dwData,
                    INT_PTR iString,
                    TCHAR* szTTip,
                    INT idMenu);
        //Обработчик WM_NOTIFY
        VOID DoNotify(LPARAM lParam);//вставить в обработчик WM_NOTIFY окна родителя
        //Обработчик WM_SIZE
        VOID AutoSize();//вставить в обработчик WM_SIZE окна родителя
        //удаляет указанную кнопку
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
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxToolBarH
