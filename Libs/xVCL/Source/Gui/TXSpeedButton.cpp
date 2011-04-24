/****************************************************************************
* Class name:  TXSpeedButton
* Description:
* File name:   TXSpeedButton.cpp
* Compilers:   C++Builder 2010
* String type: Unicode
* Libraries:   VCL
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     23.10.2009 12:52:29
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xVCL/Gui/TXSpeedButton.h>
//---------------------------------------------------------------------------
__fastcall TXSpeedButton::TXSpeedButton(TComponent* Owner) :
	TSpeedButton(Owner),
	m_sFilePath  (_T("")),
	m_sParam     (_T("")),
	m_sIconPath  (_T(""))
{
	//
}
//---------------------------------------------------------------------------
__fastcall TXSpeedButton::~TXSpeedButton() {
	//
}
//---------------------------------------------------------------------------

