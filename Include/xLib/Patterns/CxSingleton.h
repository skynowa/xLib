/**
 * \file  CxSingleton.h
 * \brief singleton
 */


#pragma once

#ifndef xLib_CxSingletonH
#define xLib_CxSingletonH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, patterns)

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

xNAMESPACE2_END(xlib, patterns)
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxSingletonH
