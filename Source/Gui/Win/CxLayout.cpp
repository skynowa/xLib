/**
 * \file  CxLayout.cpp
 * \brief layout for controls
 */


#include <xLib/Gui/Win/CxLayout.h>

#if defined(xOS_ENV_WIN)
/****************************************************************************
*    Public methods
*
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxLayout (comment)
CxLayout::CxLayout() {
    LOG();

    //-------------------------------------
    //�������������� ��������� ����
    _m_sClassName = xCXLAYOUT_CONTROL_CLASS + tString(xT("_")) + CxString::sCreateGUID();
    _m_ulStyle    = xCXLAYOUT_DEFAULT_WINDOW_STYLE;
    _m_ulStyleEx  = xCXLAYOUT_DEFAULT_WINDOW_STYLE_EX;
    ////_m_ulStyle   = WS_CHILD | WS_TABSTOP | WS_CAPTION;
    ////_m_ulStyleEx = WS_EX_CONTROLPARENT;

    _m_iLeft      = CW_USEDEFAULT;
    _m_iTop       = CW_USEDEFAULT;
    _m_iWidth     = xCXLAYOUT_DEFAULT_WIDTH;
    _m_iHeight    = xCXLAYOUT_DEFAULT_HEIGHT;

    _m_bIsControl = TRUE;
}
//---------------------------------------------------------------------------
//TODO: - ~CxLayout (comment)
CxLayout::~CxLayout() {
    LOG();
}
//---------------------------------------------------------------------------
#endif
