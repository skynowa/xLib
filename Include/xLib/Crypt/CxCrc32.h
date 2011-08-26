/**
 * \file  CxCrc32.h
 * \brief Crc32
 */


#ifndef xLib_Crypt_CxCrc32H
#define xLib_Crypt_CxCrc32H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxCrc32 :
    public CxNonCopyable
    /// Crc32
{
    public:
        static ULONG   ulCalc        (UCHAR *pucBuff, const ULONG culSize);
        static ULONG   ulCalcFile    (const std::tstring &csFilePath);

        static ULONG   ulCalcFast    (UCHAR *pucBuff, const ULONG culSize);
        static ULONG   ulCalcFileFast(const std::tstring &csFilePath);

        static std::tstring sFormatHex    (const ULONG culCrc32);

    private:
                       CxCrc32       ();
        virtual       ~CxCrc32       ();
};
//---------------------------------------------------------------------------
#endif //xLib_Crypt_CxCrc32H
