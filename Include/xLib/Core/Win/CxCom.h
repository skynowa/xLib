/**
 * \file  CxCom.h
 * \brief Component Object Model (COM)
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
#if xENV_WIN

xNAMESPACE_BEGIN2(xlib, core)

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

xNAMESPACE_END2(xlib, core)

#endif
//-------------------------------------------------------------------------------------------------
#include "CxCom.inl"
