/**
 * \file  Singleton.h
 * \brief singleton
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, patterns)

template<typename T>
class Singleton
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
    xNO_INSTANCE(Singleton)
    xNO_COPY_ASSIGN(Singleton)
};

xNAMESPACE_END2(xl, patterns)
//-------------------------------------------------------------------------------------------------
