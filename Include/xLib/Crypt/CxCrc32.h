/**
 * \file  CxCrc32.h
 * \brief Crc32
 */


#ifndef xLib_Crypt_CxCrc32H
#define xLib_Crypt_CxCrc32H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxCrc32 :
    public CxNonCopyable
    /// Crc32
{
    public:
        static ULONG        ulCalc        (UCHAR *pucBuff, const ULONG culSize);
            ///< calculate
        static ULONG        ulCalcFile    (const std::string_t &csFilePath);
            ///< calculate

        static ULONG        ulCalcFast    (UCHAR *pucBuff, const ULONG culSize);
            ///< fast calculate
        static ULONG        ulCalcFileFast(const std::string_t &csFilePath);
            ///< fast calculate

        static std::string_t sFormatHex    (const ULONG culCrc32);
            ///< format Crc32 like "0AADDEA0"

    private:
                            CxCrc32       ();
            ///< constructor
        virtual            ~CxCrc32       ();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Crypt_CxCrc32H
