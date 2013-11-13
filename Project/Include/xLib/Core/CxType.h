/**
 * \file  CxType.h
 * \brief type info
 */


#pragma once

#ifndef xLib_CxTypeH
#define xLib_CxTypeH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxType
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

xNO_COPY_ASSIGN(CxType)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxType.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxTypeH
