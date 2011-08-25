/**
 * \file  sGetEan13BarCode.h
 * \brief code EAN-13
 */


#ifndef xLib_Units_sGetEan13BarCodeH
#define xLib_Units_sGetEan13BarCodeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
//NOTE: http://grandzebu.net/index.php?page=/informatique/codbar-en/ean13.htm

std::tstring sGetEan13BarCode(const std::tstring &csData);
std::tstring sGetEan13Code   (const std::tstring &csData);
//---------------------------------------------------------------------------
#endif //xLib_Units_sGetEan13BarCodeH


/*
  Parameters : a 12 digits length string
  Return     : a string which give the bar code when it is dispayed with EAN13.TTF font
               an empty string if the supplied parameter is no good
*/
