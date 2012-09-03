/**
 * \file  bGetUsbInfo.h
 * \brief get USB info
 */


#ifndef xLib_Units_bGetUsbInfoH
#define xLib_Units_bGetUsbInfoH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

    xNAMESPACE_BEGIN(NxLib)

        bool bGetUsbInfo(const std::tstring_t &csDrive, std::vec_tstring_t *pvsInfo);
            ///< get USB info

    xNAMESPACE_END(NxLib)

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
 *     bool                 bRv = false;
 *     std::vec_tstring_t vsRes;
 *
 *     bRv = bGetUsbInfo("H:\\", &vsRes);
 *     xASSERT("\\??\\USB"                              == vsRes.at(0));
 *     xASSERT("Vid_058f&Pid_6387"                      == vsRes.at(1));
 *     xASSERT("3DH5R5EL"                               == vsRes.at(2));
 *     xASSERT("{a5dcbf10-6530-11d2-901f-00c04fb951ed}" == vsRes.at(3));
 *
 *     //assert(sRv == "\\??\\USB#Vid_058f&Pid_6387#3DH5R5EL#{a5dcbf10-6530-11d2-901f-00c04fb951ed}");
 *     std::cout << "bGetUsbInfo: " << sRv.c_str() << std::endl;
 *
 *     system("pause");
 *
 *     return 0;
 * }
 *
 * \endcode
 */







