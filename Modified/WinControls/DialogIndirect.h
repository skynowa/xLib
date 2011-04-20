/****************************************************************************
*   Классы для создания диалоговых окон "налету"
*
*
*   Для этого в API есть функции CreateDialogIndirect и DialogBoxIndirect. 
*   Эти функции замечательно работают, но формировать шаблон вручную — довольно противное занятие. 
*   
*   Краткое описание классов, решающих эту проблему:
*   
*   — С помощью объекта формируешь шаблон
*   — Передаёшь его в CreateDialogIndirect или DialogBoxIndirect
*   — работаешь 
*   
*   Координаты и размеры скорее всего в dialog unit-ах. 
*   Я лично устанавливал все размеры в 0, 
*   а потом расставлял контролы в обработчике WM_INITDIALOG.
*
*****************************************************************************/


//Заголовок DialogIndirect.h
#ifndef DIALOGINDIRECT_H
#define DIALOGINDIRECT_H

#include <vector>

namespace DialogIndirect {
    // Либо строчка, либо 0
    class sz_Or_0
    {
        public:

            sz_Or_0(const WCHAR* s);

            int size() const;
            const void* get() const;

        private:

            const WCHAR* str;
    };

    // Либо строчка, либо число
    class sz_Or_Ord
    {
        public:

            sz_Or_Ord(int i);
            sz_Or_Ord(const WCHAR* s);

            int size() const;
            const void* get() const;

        private:

            WORD    id[2];
            sz_Or_0 str;
    };

    //
    // Варианты класоов для стандартных контролов
    enum
    {
        Button = 0x0080,
        Edit = 0x0081,
        Static = 0x0082,
        ListBox = 0x0083,
        ScrollBar = 0x0084,
        ComboBox = 0x0085  
    };

    //
    // Шаблон диалога
    // Работать так:
    //      Window(с параметрами)
    //      если нужно, Font(с параметрами) 
    //      добавление контролов
    //      get
    class CTemplate
    {
        public:

            //
            // Основные параметры окна
            void Window(
                    DWORD dwExStyle,
                    sz_Or_Ord className,
                    const WCHAR* wndowName,
                    DWORD dwStyle,
                    short x = 0,
                    short y = 0,
                    short cx = 0,
                    short cy = 0,
                    sz_Or_Ord menu = 0);
            //
            // Шрифт
            void Font(
                    const WCHAR* str, 
                    WORD point);

            //
            // Добавление контролов
            void AddControl(
                    DWORD dwExStyle,
                    sz_Or_Ord className,
                    sz_Or_Ord title,
                    DWORD dwStyle,
                    WORD  id,
                    short x = 0,
                    short y = 0,
                    short cx = 0,
                    short cy = 0,
                    WORD  cwndExtra = 0,
                    const void* data = 0);

            //
            // Возвращает результат
            const DLGTEMPLATE* Get() const;

        private:

            std::vector<char> m_data;    
    };

    //
    // Расширенный шаблон диалога
    // Работать так:
    //      Window(с параметрами)
    //      если нужно, Font(с параметрами) 
    //      добавление контролов
    //      get
    class CTemplateEx
    {
        public:

            //
            // Основные параметры окна
            void Window(
                    DWORD dwExStyle,
                    sz_Or_Ord className,
                    const WCHAR* wndowName,
                    DWORD dwStyle,
                    short x = 0,
                    short y = 0,
                    short cx = 0,
                    short cy = 0,
                    sz_Or_Ord menu = 0,
                    DWORD helpID = 0);
            //
            // Шрифт
            void Font(
                    const WCHAR* str, 
                    WORD point, 
                    WORD weight, 
                    BYTE charset, 
                    bool italic = false);

            //
            // Добавление контролов
            void AddControl(
                    DWORD dwExStyle,
                    sz_Or_Ord className,
                    sz_Or_Ord title,
                    DWORD dwStyle,
                    WORD  id,
                    short x = 0,
                    short y = 0,
                    short cx = 0,
                    short cy = 0,
                    WORD  cwndExtra = 0,
                    const void* data = 0,
                    DWORD helpID = 0);

            //
            // Возвращает результат
            const DLGTEMPLATE* Get() const;

        private:

            std::vector<char> m_data;    
    };
};

#endif //DIALOGINDIRECT_H
