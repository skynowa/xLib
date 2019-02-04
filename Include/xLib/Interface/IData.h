/**
 * \file   IData.h
 * \brief  Data struct
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, interface)

class xNO_VTABLE IData
    ///< Data struct
{
public:
                   IData() = default;
        ///< constructor
    virtual       ~IData() = default;
        ///< destructor

    virtual bool_t isValid() = 0;
        ///< check validness
    virtual void_t clear() = 0;
        ///< clear data
    virtual void_t dump() = 0;
        ///< print data

private:
    xNO_COPY_ASSIGN(IData)
};

xNAMESPACE_END2(xl, interface)
//-------------------------------------------------------------------------------------------------
