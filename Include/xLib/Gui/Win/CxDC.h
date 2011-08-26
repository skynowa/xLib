/**
 * \file  CxDC.h
 * \brief DC
 */


#ifndef CxDCH
#define CxDCH
//---------------------------------------------------------------------------------------
#include <xLib/xCommon.h>
//---------------------------------------------------------------------------------------
class CxDC : 
    public CxNonCopyable 
    /// DC   
{
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
