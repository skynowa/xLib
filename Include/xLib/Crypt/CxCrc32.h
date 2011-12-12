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
        static ulong_t        ulCalc        (uchar_t *pucBuff, const ulong_t culSize);
            ///< calculate
        static ulong_t        ulCalcFile    (const std::tstring_t &csFilePath);
            ///< calculate

        static ulong_t        ulCalcFast    (uchar_t *pucBuff, const ulong_t culSize);
            ///< fast calculate
        static ulong_t        ulCalcFileFast(const std::tstring_t &csFilePath);
            ///< fast calculate

        static std::tstring_t sFormatHex    (const ulong_t culCrc32);
            ///< format Crc32 like "0AADDEA0"

    private:
                              CxCrc32       ();
            ///< constructor
        virtual              ~CxCrc32       ();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Crypt_CxCrc32H
