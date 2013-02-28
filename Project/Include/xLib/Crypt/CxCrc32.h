/**
 * \file  CxCrc32.h
 * \brief Crc32
 */


#ifndef xLib_Crypt_CxCrc32H
#define xLib_Crypt_CxCrc32H
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxCrc32 :
    private CxNonCopyable
    /// Crc32
{
public:
    static ulong_t        calc        (uchar_t *pucBuff, culong_t &culSize) xWARN_UNUSED_RV;
        ///< calculate
    static ulong_t        calcFile    (const std::tstring_t &csFilePath) xWARN_UNUSED_RV;
        ///< calculate

    static ulong_t        calcFast    (uchar_t *pucBuff, culong_t &culSize) xWARN_UNUSED_RV;
        ///< fast calculate
    static ulong_t        calcFileFast(const std::tstring_t &csFilePath) xWARN_UNUSED_RV;
        ///< fast calculate

    static std::tstring_t formatHex   (culong_t &culCrc32) xWARN_UNUSED_RV;
        ///< format Crc32 like "0AADDEA0"

private:
                          CxCrc32     ();
        ///< constructor
    virtual              ~CxCrc32     ();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Crypt_CxCrc32H
