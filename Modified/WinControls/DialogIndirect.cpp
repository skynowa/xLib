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


// Основной файл DialogIndirect.cpp
#include <XLib/DialogIndirect.h>

namespace DialogIndirect
{

#pragma pack(push, 1)

    //////////////////////////////////////////////////////////////////////////
    //
    // Структуры для обычного шаблона
    //
    //////////////////////////////////////////////////////////////////////////
    
    struct font_data
    {
        WORD  m_pointsize; 
        //WCHAR m_typeface[1]; // anysize array
    };

/*
 typedef struct {  
  DWORD     style; 
  DWORD     exStyle; 
  WORD      cDlgItems; 
  short     x; 
  short     y; 
  short     cx; 
  short     cy; 
  sz_Or_Ord menu; 
  sz_Or_Ord windowClass; 
  WCHAR     title[titleLen]; 
// The following members exist only if the style member is 
// set to DS_SETFONT or DS_SHELLFONT.
  WORD     pointsize; 
  WCHAR    typeface[stringLen];  
} DLGTEMPLATEEX; 
 
 */
    struct window_data
    {
        DWORD     style; 
        DWORD     exStyle; 
        WORD      cDlgItems; 
        short     x; 
        short     y; 
        short     cx; 
        short     cy; 
        // sz_Or_Ord menu; 
        // sz_Or_Ord windowClass; 
        // WCHAR     title[titleLen]; 
        // font_data font     
    };

/*
typedef struct { 
  DWORD  style; 
  DWORD  exStyle; 
  short  x; 
  short  y; 
  short  cx; 
  short  cy; 
  WORD   id; 
  sz_Or_Ord windowClass; 
  sz_Or_Ord title; 
  WORD   extraCount; 
  char   extraData[extraCount];
} DLGITEMTEMPLATEEX; 
*/

    struct item_data
    {
        DWORD  style; 
        DWORD  exStyle; 
        short  x; 
        short  y; 
        short  cx; 
        short  cy; 
        WORD   id; 
        //sz_Or_Ord windowClass; 
        //sz_Or_Ord title; 
        //WORD   extraCount; 
        //char   extraData[extraCount];
    };

#pragma pack(pop)
}

//////////////////////////////////////////////////////////////////////////
//
// Реализация CTemplate
//
//////////////////////////////////////////////////////////////////////////

//
// Основные параметры окна
void DialogIndirect::CTemplate::Window(
        DWORD dwExStyle,
        sz_Or_Ord className,
        const WCHAR* windowName,
        DWORD dwStyle,
        short x,
        short y,
        short cx,
        short cy,
        sz_Or_Ord menu)
{
    sz_Or_0 title(windowName);

    m_data.resize(sizeof(window_data) + menu.size() + className.size() + title.size());

    window_data* p = reinterpret_cast<window_data*>(m_data.begin());

    p->style = dwStyle;
    p->exStyle = dwExStyle;
    p->cDlgItems = 0;
    p->x = x;
    p->y = y;
    p->cx = cx;
    p->cy = cy;

    char* tmp = reinterpret_cast<char*>(p + 1);

    memcpy(tmp, menu.get(), menu.size());
    tmp += menu.size();

    memcpy(tmp, className.get(), className.size());
    tmp += className.size();
    
    memcpy(tmp, title.get(), title.size());
}

//
// Шрифт
void DialogIndirect::CTemplate::Font(const WCHAR* str, WORD point)
{
    sz_Or_0 face(str);

    int begin = m_data.size();
    m_data.resize(begin + sizeof(font_data) + face.size());

    font_data* p = reinterpret_cast<font_data*>(m_data.begin() + begin);

    p->m_pointsize = point;

    char* tmp = reinterpret_cast<char*>(p + 1);

    memcpy(tmp, face.get(), face.size());
}

//
// Добавление контролов
void DialogIndirect::CTemplate::AddControl(
        DWORD dwExStyle,
        sz_Or_Ord className,
        sz_Or_Ord title,
        DWORD dwStyle,
        WORD  id,
        short x,
        short y,
        short cx,
        short cy,
        WORD  cwndExtra,
        const void* data)
{
    if (m_data.size() % sizeof(DWORD))
    {
        // Должен быть выровнен
        while (m_data.size() % sizeof(DWORD)) m_data.push_back(0);
    }

    int begin = m_data.size();
    m_data.resize(begin + sizeof(item_data) + className.size() + title.size() + sizeof(cwndExtra) + cwndExtra);

    item_data* p = reinterpret_cast<item_data*>(m_data.begin() + begin);

    p->style   = dwStyle;
    p->exStyle = dwExStyle;
    p->x       = x;
    p->y       = y;
    p->cx      = cx;
    p->cy      = cy;
    p->id      = id;
    
    char* tmp = reinterpret_cast<char*>(p + 1);

    memcpy(tmp, className.get(), className.size());
    tmp += className.size();

    memcpy(tmp, title.get(), title.size());
    tmp += title.size();

    memcpy(tmp, &cwndExtra, sizeof(cwndExtra));
    tmp += sizeof(cwndExtra);

    if (cwndExtra)
    {
        memcpy(tmp, data, cwndExtra);
    }

    window_data* wnd = reinterpret_cast<window_data*>(m_data.begin());
    wnd->cDlgItems++;
}

//
// Возвращает результат
const DLGTEMPLATE* DialogIndirect::CTemplate::Get() const
{
    if (!m_data.size()) return 0;
    return reinterpret_cast<const DLGTEMPLATE*>(&m_data[0]);
}

//////////////////////////////////////////////////////////////////////////
//
// Реализация CTemplateEx
//
//////////////////////////////////////////////////////////////////////////

namespace DialogIndirect
{

#pragma pack(push, 1)

    //////////////////////////////////////////////////////////////////////////
    //
    // Структуры для расширенного шаблона
    //
    //////////////////////////////////////////////////////////////////////////

    struct font_ex_data
    {
        WORD  m_pointsize; 
        WORD  m_weight; 
        BYTE  m_italic;
        BYTE  m_charset; 
        //WCHAR m_typeface[1]; // anysize array
    };

/*
 typedef struct {  
  WORD      dlgVer; 
  WORD      signature; 
  DWORD     helpID; 
  DWORD     exStyle; 
  DWORD     style; 
  WORD      cDlgItems; 
  short     x; 
  short     y; 
  short     cx; 
  short     cy; 
  sz_Or_Ord menu; 
  sz_Or_Ord windowClass; 
  WCHAR     title[titleLen]; 
// The following members exist only if the style member is 
// set to DS_SETFONT or DS_SHELLFONT.
  WORD     pointsize; 
  WORD     weight; 
  BYTE     italic;
  BYTE     charset; 
  WCHAR    typeface[stringLen];  
} DLGTEMPLATEEX; 
 
 */
    struct window_ex_data
    {
        WORD      dlgVer; 
        WORD      signature; 
        DWORD     helpID; 
        DWORD     exStyle; 
        DWORD     style; 
        WORD      cDlgItems; 
        short     x; 
        short     y; 
        short     cx; 
        short     cy; 
        // sz_Or_Ord menu; 
        // sz_Or_Ord windowClass; 
        // WCHAR     title[titleLen]; 
        // font_data font     
    };

/*
typedef struct { 
  DWORD  helpID; 
  DWORD  exStyle; 
  DWORD  style; 
  short  x; 
  short  y; 
  short  cx; 
  short  cy; 
  WORD   id; 
  WORD   dummy; - не указан в MSDN, но без него не работает
  sz_Or_Ord windowClass; 
  sz_Or_Ord title; 
  WORD   extraCount; 
  char   extraData[extraCount];
} DLGITEMTEMPLATEEX; 
*/

    struct item_ex_data
    {
        DWORD  helpID; 
        DWORD  exStyle; 
        DWORD  style; 
        short  x; 
        short  y; 
        short  cx; 
        short  cy; 
        WORD   id; 
        WORD   dummy;
        //sz_Or_Ord windowClass; 
        //sz_Or_Ord title; 
        //WORD   extraCount; 
        //char   extraData[extraCount];
    };

#pragma pack(pop)
}


//
// Основные параметры окна
void DialogIndirect::CTemplateEx::Window(
        DWORD dwExStyle,
        sz_Or_Ord className,
        const WCHAR* windowName,
        DWORD dwStyle,
        short x,
        short y,
        short cx,
        short cy,
        sz_Or_Ord menu,
        DWORD helpID)
{
    sz_Or_0 title(windowName);

    m_data.resize(sizeof(window_ex_data) + menu.size() + className.size() + title.size());

    window_ex_data* p = reinterpret_cast<window_ex_data*>(m_data.begin());

    p->dlgVer = 1;
    p->signature = 0xffff;
    p->helpID = helpID;
    p->exStyle = dwExStyle;
    p->style = dwStyle;
    p->cDlgItems = 0;
    p->x = x;
    p->y = y;
    p->cx = cx;
    p->cy = cy;

    char* tmp = reinterpret_cast<char*>(p + 1);

    memcpy(tmp, menu.get(), menu.size());
    tmp += menu.size();

    memcpy(tmp, className.get(), className.size());
    tmp += className.size();
    
    memcpy(tmp, title.get(), title.size());
}

//
// Шрифт
void DialogIndirect::CTemplateEx::Font(
        const WCHAR* str, 
        WORD point, 
        WORD weight, 
        BYTE charset, 
        bool italic)
{
    sz_Or_0 face(str);

    int begin = m_data.size();
    m_data.resize(begin + sizeof(font_ex_data) + face.size());

    font_ex_data* p = reinterpret_cast<font_ex_data*>(m_data.begin() + begin);

    p->m_charset = charset;
    p->m_pointsize = point;
    p->m_italic = italic;
    p->m_weight = weight;

    char* tmp = reinterpret_cast<char*>(p + 1);

    memcpy(tmp, face.get(), face.size());
}

//
// Добавление контролов
void DialogIndirect::CTemplateEx::AddControl(
        DWORD dwExStyle,
        sz_Or_Ord className,
        sz_Or_Ord title,
        DWORD dwStyle,
        WORD  id,
        short x,
        short y,
        short cx,
        short cy,
        WORD  cwndExtra,
        const void* data,
        DWORD helpID)
{
    if (m_data.size() % sizeof(DWORD))
    {
        // Должен быть выровнен
        while (m_data.size() % sizeof(DWORD)) m_data.push_back(0);
    }

    int begin = m_data.size();
    m_data.resize(begin + sizeof(item_ex_data) 
                + className.size() 
                + title.size() 
                + sizeof(cwndExtra) + cwndExtra);

    item_ex_data* p = reinterpret_cast<item_ex_data*>(m_data.begin() + begin);

    p->helpID  = helpID;
    p->exStyle = dwExStyle;
    p->style   = dwStyle;
    p->x       = x;
    p->y       = y;
    p->cx      = cx;
    p->cy      = cy;
    p->id      = id;
    
    char* tmp = reinterpret_cast<char*>(p + 1);

    memcpy(tmp, className.get(), className.size());
    tmp += className.size();

    memcpy(tmp, title.get(), title.size());
    tmp += title.size();

    memcpy(tmp, &cwndExtra, sizeof(cwndExtra));
    tmp += sizeof(cwndExtra);

    if (cwndExtra)
    {
        memcpy(tmp, data, cwndExtra);
    }

    window_ex_data* wnd = reinterpret_cast<window_ex_data*>(m_data.begin());
    wnd->cDlgItems++;
}

//
// Возвращает результат
const DLGTEMPLATE* DialogIndirect::CTemplateEx::Get() const
{
    if (!m_data.size()) return 0;
    return reinterpret_cast<const DLGTEMPLATE*>(&m_data[0]);
}

//////////////////////////////////////////////////////////////////////////
//
// Реализация вспомогательных классов
//
//////////////////////////////////////////////////////////////////////////

//
// Строчка или 0
//

DialogIndirect::sz_Or_0::sz_Or_0(const WCHAR* s)
{
    str = s;
}

int DialogIndirect::sz_Or_0::size() const
{
    if (str == 0)
    {
        return sizeof(WCHAR);
    }

    return (wcslen(str) + 1) * sizeof(WCHAR);
}

const void* DialogIndirect::sz_Or_0::get() const
{
    if (str == 0)
    {
        static WCHAR zero = 0;
        return &zero;
    }

    return str;
}

//
// Строчка или 0 или число
//

DialogIndirect::sz_Or_Ord::sz_Or_Ord(int i) : str(0)
{
    if (i == 0)
    {
        id[0] = 0;
        id[1] = 0;
    }
    else
    {
        id[0] = 0xffff;
        id[1] = static_cast<WORD>(i);
    }
}

DialogIndirect::sz_Or_Ord::sz_Or_Ord(const WCHAR* s) : str(s)
{
    if ((s == 0) || (reinterpret_cast<unsigned int>(s) > 0xffff))
    {
        id[0] = 0;
        id[1] = 0;
    }
    else
    {
        id[0] = 0xffff;
        id[1] = reinterpret_cast<unsigned int>(s);
    }
}

int DialogIndirect::sz_Or_Ord::size() const
{
    if (id[0] == 0xffff)
    {
        return sizeof(WORD) * 2;
    }
    
    return str.size();
}

const void* DialogIndirect::sz_Or_Ord::get() const
{
    if (id[0] == 0xffff)
    {
        return id;
    }
    
    return str.get();
}
