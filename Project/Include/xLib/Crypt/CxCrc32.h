/**
 * \file  CxCrc32.h
 * \brief Crc32
 */


#pragma once

#ifndef xLib_CxCrc32H
#define xLib_CxCrc32H
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxCrc32
    /// Crc32
{
public:
    static ulong_t        calc(uchar_t *buff, culong_t &size) xWARN_UNUSED_RV;
        ///< calculate
    static ulong_t        calcFile(std::ctstring_t &filePath) xWARN_UNUSED_RV;
        ///< calculate

    static ulong_t        calcFast(uchar_t *buff, culong_t &size) xWARN_UNUSED_RV;
        ///< fast calculate
    static ulong_t        calcFileFast(std::ctstring_t &filePath) xWARN_UNUSED_RV;
        ///< fast calculate

    static std::tstring_t formatHex(culong_t &crc32) xWARN_UNUSED_RV;
        ///< format Crc32 like "0AADDEA0"

private:
                          CxCrc32();
        ///< constructor
    virtual              ~CxCrc32();
        ///< destructor

xNO_COPY_ASSIGN(CxCrc32)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include <Crypt/CxCrc32.inl>
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxCrc32H
