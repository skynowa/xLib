/**
 * \file  CxCom.h
 * \brief Component Object Model (COM)
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
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

#endif
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY

#endif
