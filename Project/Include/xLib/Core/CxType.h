/**
 * \file  CxType.h
 * \brief type info
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxType :
    public CxNonCopyable
    /// type info
{
public:
    template<class T>
    static std::tstring_t name(const T &objT) xWARN_UNUSED_RV;
        ///< get name

    template<class T>
    static std::tstring_t rawName(const T &objT) xWARN_UNUSED_RV;
        ///< get raw name

    template<class T1, class T2>
    static bool_t         isEquals(const T1 &obj1T, const T2 &obj2T) xWARN_UNUSED_RV;
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
