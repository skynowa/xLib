/**
 * \file  Type.h
 * \brief type info
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

class Type
    /// type info
{
public:
    template<typename T>
    static
    std::tstring_t name(const T &objT) xWARN_UNUSED_RV;
        ///< get name

    template<typename T>
    static
    std::tstring_t rawName(const T &objT) xWARN_UNUSED_RV;
        ///< get raw name

    template<typename T1, class T2>
    static
    bool_t         isEquals(const T1 &obj1T, const T2 &obj2T) xWARN_UNUSED_RV;
        ///< is equals

private:
                   Type();
        ///< constructor
    virtual       ~Type();
        ///< destructor

    xNO_COPY_ASSIGN(Type)
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#include "Type.inl"
