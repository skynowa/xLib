/****************************************************************************
* Class name:  CxDC
* Description: работа с контекстом устройства
* File name:   CxDC.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     18.06.2009 21:30:49
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef CxDCH
#define CxDCH
//---------------------------------------------------------------------------------------
#include <XLib/xCommon.h>
//---------------------------------------------------------------------------------------
class CxDC : public CxNonCopyable {
	public:
		         CxDC    ();
		virtual ~CxDC    ();
		BOOL     bAttach (HDC hDC);
		HDC      hDetach ();
		BOOL     bTextOut(INT xStart, INT yStart, std::string &csText, INT iText);
		BOOL     bTextOut(INT xStart, INT yStart, std::string &csText);
		
	private:
		HDC      _m_hDC;
};
//---------------------------------------------------------------------------------------
#endif