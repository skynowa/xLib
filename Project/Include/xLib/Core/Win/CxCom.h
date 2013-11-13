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

xNAMESPACE_BEGIN(NxLib)

class CxCom
    /// Component Object Model (COM)
{
public:
    explicit  CxCom(const COINIT &concurrencyModel);
        ///< constructor
    virtual  ~CxCom();
        ///< destructor

xNO_COPY_ASSIGN(CxCom)
};

xNAMESPACE_END(NxLib)

#endif
//-------------------------------------------------------------------------------------------------
#include <Core/Win/CxCom.inl>
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxComH
