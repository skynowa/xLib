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
xNAMESPACE_BEGIN2(xlib, crypt)

class CxCrc32
    /// Crc32
{
public:
                   CxCrc32();
        ///< constructor
    virtual       ~CxCrc32() {};
        ///< destructor

    ulong_t        calc(uchar_t *buff, culong_t &buffSize) xWARN_UNUSED_RV;
        ///< fast calculate
    ulong_t        calcFile(std::ctstring_t &filePath) xWARN_UNUSED_RV;
        ///< fast calculate

    std::tstring_t formatHex() const xWARN_UNUSED_RV;
        ///< format Crc32 like "0AADDEA0"

private:
    ulong_t        _crc32;

    xNO_COPY_ASSIGN(CxCrc32)
};

xNAMESPACE_END2(xlib, crypt)
//-------------------------------------------------------------------------------------------------
#include "CxCrc32.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxCrc32H
