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
    ///< code EAN-13
std::tstring sGetEan13Code   (const std::tstring &csData);
    ///< code EAN-13
//---------------------------------------------------------------------------
#endif //xLib_Units_sGetEan13BarCodeH
