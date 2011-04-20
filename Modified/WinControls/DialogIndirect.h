/****************************************************************************
*   ������ ��� �������� ���������� ���� "������"
*
*
*   ��� ����� � API ���� ������� CreateDialogIndirect � DialogBoxIndirect. 
*   ��� ������� ������������ ��������, �� ����������� ������ ������� � �������� ��������� �������. 
*   
*   ������� �������� �������, �������� ��� ��������:
*   
*   � � ������� ������� ���������� ������
*   � �������� ��� � CreateDialogIndirect ��� DialogBoxIndirect
*   � ��������� 
*   
*   ���������� � ������� ������ ����� � dialog unit-��. 
*   � ����� ������������ ��� ������� � 0, 
*   � ����� ���������� �������� � ����������� WM_INITDIALOG.
*
*****************************************************************************/


//��������� DialogIndirect.h
#ifndef DIALOGINDIRECT_H
#define DIALOGINDIRECT_H

#include <vector>

namespace DialogIndirect {
    // ���� �������, ���� 0
    class sz_Or_0
    {
        public:

            sz_Or_0(const WCHAR* s);

            int size() const;
            const void* get() const;

        private:

            const WCHAR* str;
    };

    // ���� �������, ���� �����
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
    // �������� ������� ��� ����������� ���������
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
    // ������ �������
    // �������� ���:
    //      Window(� �����������)
    //      ���� �����, Font(� �����������) 
    //      ���������� ���������
    //      get
    class CTemplate
    {
        public:

            //
            // �������� ��������� ����
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
            // �����
            void Font(
                    const WCHAR* str, 
                    WORD point);

            //
            // ���������� ���������
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
            // ���������� ���������
            const DLGTEMPLATE* Get() const;

        private:

            std::vector<char> m_data;    
    };

    //
    // ����������� ������ �������
    // �������� ���:
    //      Window(� �����������)
    //      ���� �����, Font(� �����������) 
    //      ���������� ���������
    //      get
    class CTemplateEx
    {
        public:

            //
            // �������� ��������� ����
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
            // �����
            void Font(
                    const WCHAR* str, 
                    WORD point, 
                    WORD weight, 
                    BYTE charset, 
                    bool italic = false);

            //
            // ���������� ���������
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
            // ���������� ���������
            const DLGTEMPLATE* Get() const;

        private:

            std::vector<char> m_data;    
    };
};

#endif //DIALOGINDIRECT_H
