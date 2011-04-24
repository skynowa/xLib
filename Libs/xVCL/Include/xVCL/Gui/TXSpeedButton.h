/****************************************************************************
* Class name:  TXSpeedButton
* Description:
* File name:   TXSpeedButton.h
* Compilers:   C++Builder 2010
* String type: Unicode
* Libraries:   VCL
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     23.10.2009 12:52:29
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef XLCL_TXSpeedButtonH
#define XLCL_TXSpeedButtonH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <Classes.hpp>
#include <Controls.hpp>
#include <Buttons.hpp>
#include <xVCL/xCommon.h>
//---------------------------------------------------------------------------
class TXSpeedButton :
	public TSpeedButton
{
	public:
		String      m_sFilePath;
		String      m_sParam;
		String      m_sIconPath;

		__fastcall  TXSpeedButton(TComponent* Owner);
		__fastcall ~TXSpeedButton();
};
//---------------------------------------------------------------------------
#endif
