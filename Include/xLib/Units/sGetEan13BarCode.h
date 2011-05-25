/****************************************************************************
* Func name:   sGetEan13BarCode
* Description: code EAN-13 (http://grandzebu.net/index.php?page=/informatique/codbar-en/ean13.htm)
* File name:   sGetEan13BarCode.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     19.05.2010 9:33:24
*
*****************************************************************************/



#ifndef xLib_Units_sGetEan13BarCodeH
#define xLib_Units_sGetEan13BarCodeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
tString sGetEan13BarCode(const tString &csData);
tString sGetEan13Code   (const tString &csData);
//---------------------------------------------------------------------------
#endif //xLib_Units_sGetEan13BarCodeH


/*
  Parameters : a 12 digits length string
  Return     : a string which give the bar code when it is dispayed with EAN13.TTF font
               an empty string if the supplied parameter is no good
*/
