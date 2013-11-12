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

class CxCom :
    private CxNonCopyable
    /// Component Object Model (COM)
{
public:
    explicit  CxCom(const COINIT &concurrencyModel);
        ///< constructor
    virtual  ~CxCom();
        ///< destructor
};

xNAMESPACE_END(NxLib)

#endif
//-------------------------------------------------------------------------------------------------
#include <Core/Win/CxCom.inl>
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxComH
