/**
 * \file  CxCom.h
 * \brief Component Object Model (COM)
 */


#pragma once

#ifndef xLib_CxComH
#define xLib_CxComH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(xlib)

class CxCom
    /// Component Object Model (COM)
{
public:
    explicit  CxCom(const COINIT &concurrencyModel);
        ///< constructor
    virtual  ~CxCom();
        ///< destructor

private:
    xNO_COPY_ASSIGN(CxCom)
};

xNAMESPACE_END(xlib)

#endif
//-------------------------------------------------------------------------------------------------
#include "CxCom.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxComH
