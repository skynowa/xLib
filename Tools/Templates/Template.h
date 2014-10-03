/**
 * \file   [CLASS_NAME].h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, [NAMESPACE])

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
};

xNAMESPACE_END2(xlib, [NAMESPACE])
//-------------------------------------------------------------------------------------------------
#if xOPTION_HEADER_ONLY
    #include "[CLASS_NAME].cpp"
#endif
