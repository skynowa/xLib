/**
 * \file  CxType.h
 * \brief type info
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxType :
    private CxNonCopyable
    /// type info
{
public:
    template<class T>
    static std::tstring_t name(const T &object) xWARN_UNUSED_RV;
        ///< get name

    template<class T>
    static std::tstring_t rawName(const T &object) xWARN_UNUSED_RV;
        ///< get raw name

    template<class T1, class T2>
    static bool_t         isEquals(const T1 &object1, const T2 &object2) xWARN_UNUSED_RV;
        ///< is equals
private:
                          CxType();
        ///< constructor
    virtual              ~CxType();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#include "CxType.inl"
