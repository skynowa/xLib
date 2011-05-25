/****************************************************************************
* Func name:   bGetUsbInfo
* Description: get USB info
* File name:   bGetUsbInfo.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:
*
*****************************************************************************/


#ifndef xLib_Units_bGetUsbInfoH
#define xLib_Units_bGetUsbInfoH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
BOOL bGetUsbInfo(const tString &csDrive, std::vector<tString> *pvecsInfo);
//---------------------------------------------------------------------------
#endif //xLib_Units_bGetUsbInfoH


//---------------------------------------------------------------------------
//int main(int argc, char* argv[]) {
//  BOOL                     bRes    = FALSE;
//  std::vector<tstring> vecsRes;
//
//  bRes = bGetUsbInfo("H:\\", &vecsRes);
//  XASSERT("\\??\\USB"                              == vecsRes.at(0));
//  XASSERT("Vid_058f&Pid_6387"                      == vecsRes.at(1));
//  XASSERT("3DH5R5EL"                               == vecsRes.at(2));
//  XASSERT("{a5dcbf10-6530-11d2-901f-00c04fb951ed}" == vecsRes.at(3));
//
//  //assert(sRes == "\\??\\USB#Vid_058f&Pid_6387#3DH5R5EL#{a5dcbf10-6530-11d2-901f-00c04fb951ed}");
//
//
//  //std::cout << "sGetFlashSerialFromDrive: " << sRes.c_str() << std::endl;
//
//  system("pause");
//  return 0;
//}
////---------------------------------------------------------------------------
