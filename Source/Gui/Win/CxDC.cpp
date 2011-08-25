/**
 * \file  CxDC.cpp
 * \brief DC
 */


#include <xLib/Gui/CxDC.h>
//---------------------------------------------------------------------------------------
CxDC::CxDC() :
    _m_hDC(NULL)
{
}
//---------------------------------------------------------------------------
CxDC::~CxDC() {
    if (_m_hDC) {
        ::DeleteDC(_m_hDC);
    }
}
//---------------------------------------------------------------------------
BOOL CxDC::bAttach(HDC hdc) {
    if (_m_hDC) {
        return FALSE;
    }

    _m_hDC = hdc;

    return TRUE;
}
//---------------------------------------------------------------------------
HDC CxDC::hDetach() {
    HDC RetDc = _m_hDC;
    _m_hDC = NULL;

    return RetDc;
}
//---------------------------------------------------------------------------
BOOL CxDC::bTextOut(INT xStart, INT yStart, std::string &csText, INT iText) {
    if (!_m_hDC) {
        return FALSE;
    }

    return ::TextOut(_m_hDC, xStart, yStart, csText.c_str(), iText);
}
//---------------------------------------------------------------------------
BOOL CxDC::bTextOut(INT xStart, INT yStart, std::string &csText) {
    if (!_m_hDC) {
        return FALSE;
    }

    return ::TextOut(_m_hDC, xStart, yStart, csText.c_str(), csText.size());
}
//---------------------------------------------------------------------------------------
