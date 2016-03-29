/**
 * \file   [CLASS_NAME].h
 * \brief  [CLASS_COMMENTS]
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, [XLIB_NS])

class [CLASS_NAME]
    ///<
{
public:
             [CLASS_NAME]() {}
        ///< constructor
    virtual ~[CLASS_NAME]() {}
        ///< destructor

private:
    xNO_COPY_ASSIGN([CLASS_NAME])

xPLATFORM_IMPL:
    void_t   _construct_impl();
    void_t   _destruct_impl();
};

xNAMESPACE_END2(xlib, [XLIB_NS])
//-------------------------------------------------------------------------------------------------
#if xOPTION_PROJECT_HEADER_ONLY
    #include "[CLASS_NAME].cpp"
#endif
