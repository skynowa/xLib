/****************************************************************************
* Class name:  CxLayout
* Description: слой для размещения контролов
* File name:   CxLayout.cpp
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     11.03.2010 14:32:02
* Version:     1.0.0.0 Debug
*
*****************************************************************************/



#include <XLib/Gui/CxLayout.h>

/****************************************************************************
*    Public methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxLayout (comment)
CxLayout::CxLayout() {
	LOG();

	//-------------------------------------
	//переопределяем параметры окна
	_m_sClassName = xCXLAYOUT_CONTROL_CLASS + tString(_T("_")) + CxString::sCreateGUID();
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





/****************************************************************************
*    Protected methods                                                       
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------




/****************************************************************************
*    Private methods                                                         
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
