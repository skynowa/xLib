/**
 * \file  sGetEan13BarCode.h
 * \brief code EAN-13
 */


#ifndef xLib_Units_sGetEan13BarCodeH
#define xLib_Units_sGetEan13BarCodeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

//NOTE: http://grandzebu.net/index.php?page=/informatique/codbar-en/ean13.htm

std::string_t sGetEan13BarCode(const std::string_t &csData);
    ///< code EAN-13
std::string_t sGetEan13Code   (const std::string_t &csData);
    ///< code EAN-13

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Units_sGetEan13BarCodeH
