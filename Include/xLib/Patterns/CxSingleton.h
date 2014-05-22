/**
 * \file  CxSingleton.h
 * \brief singleton
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, patterns)

template <class T>
class CxSingleton
    /// singleton
{
public:
    static T &get() xWARN_UNUSED_RV
        ///< get object instance
    {
        static T object;

        return object;
    }

private:
    CxSingleton();
        ///< constructor
   ~CxSingleton();
        ///< destructor

    xNO_COPY_ASSIGN(CxSingleton)
};

xNAMESPACE_END2(xlib, patterns)
//-------------------------------------------------------------------------------------------------
