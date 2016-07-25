/**
 * \file   [Class].h
 * \brief  [Comments]
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, [XLIB_NS])

class [Class]
    ///< [Comments]
{
public:
             [Class]();
        ///< constructor
    virtual ~[Class]();
        ///< destructor

private:
    xNO_COPY_ASSIGN([Class])

xPLATFORM_IMPL:
    void_t   _construct_impl();
    void_t   _destruct_impl();
};

xNAMESPACE_END2(xlib, [XLIB_NS])
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "[Class].cpp"
#endif
