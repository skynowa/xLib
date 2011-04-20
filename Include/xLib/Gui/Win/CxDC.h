/****************************************************************************
* Class name:  CxDC
* Description: работа с контекстом устройства
* File name:   CxDC.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     18.06.2009 21:30:49
*
*****************************************************************************/


#ifndef CxDCH
#define CxDCH
//---------------------------------------------------------------------------------------
#include <xLib/xCommon.h>
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