/**
 * \file   IData.h
 * \brief  Data struct
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, package)

class xNO_VTABLE IData
    ///< Data struct
{
public:
                   IData();
        ///< constructor
    virtual       ~IData() = 0;
        ///< destructor

    virtual void_t clear() = 0;
        ///< clear data
    virtual void_t dump() = 0;
        ///< print data

private:
    xNO_COPY_ASSIGN(IData)
};

xNAMESPACE_END2(xlib, package)
//-------------------------------------------------------------------------------------------------
