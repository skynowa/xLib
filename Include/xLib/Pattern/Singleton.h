/**
 * \file  Singleton.h
 * \brief singleton
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::patterns
{

template<typename T>
class Singleton
    /// singleton
{
public:
///@name ctors, dtor
///@{
	xNO_DEFAULT_CONSTRUCT(Singleton)
	xNO_COPY_ASSIGN(Singleton)
///@}

    static T &get()
        ///< get object instance
    {
        static T object;

        return object;
    }
};

} // namespace
//-------------------------------------------------------------------------------------------------
