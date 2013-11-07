/**
 * \file  CxSingleton.h
 * \brief singleton
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

template <class T>
class CxSingleton :
    public CxNonCopyable
    /// singleton
{
public:
    static T &get() xWARN_UNUSED_RV
        ///< get object instance
    {
        static T singleton;

        return singleton;
    }

private:
    CxSingleton();
        ///< constructor
   ~CxSingleton();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
