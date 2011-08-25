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
#if defined(xOS_WIN)
    BOOL bGetUsbInfo(const tString &csDrive, std::vector<tString> *pvsInfo);
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif //xLib_Units_bGetUsbInfoH


/**
 * \page    Samples
 * \section Units
 *
 * \code
 * #include <stdlib.h>
 * #include <stdio.h>
 *
 * int
 * main(
 *   int argc,
 *   char* argv[]
 * )
 * {
 *     BOOL                 bRes = FALSE;
 *     std::vector<tString> vsRes;
 *
 *     bRes = bGetUsbInfo("H:\\", &vsRes);
 *     xASSERT("\\??\\USB"                              == vsRes.at(0));
 *     xASSERT("Vid_058f&Pid_6387"                      == vsRes.at(1));
 *     xASSERT("3DH5R5EL"                               == vsRes.at(2));
 *     xASSERT("{a5dcbf10-6530-11d2-901f-00c04fb951ed}" == vsRes.at(3));
 *
 *     //assert(sRes == "\\??\\USB#Vid_058f&Pid_6387#3DH5R5EL#{a5dcbf10-6530-11d2-901f-00c04fb951ed}");
 *     std::cout << "bGetUsbInfo: " << sRes.c_str() << std::endl;
 *
 *     system("pause");
 *
 *     return 0;
 * }
 *
 * \endcode
 */







