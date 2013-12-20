/**
 * \file   CxGuid.h
 * \brief
 */


#pragma once

#ifndef xLib_CxGuidH
#define xLib_CxGuidH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxGuid
    /// GUID (globally unique identifier)
{
public:
    enum ExType
    {
        tpUnknown     = 0,
        tpRandomBased = 1

    };
    typedef const ExType cExType;

                   CxGuid() {}
        ///< constructor
    virtual       ~CxGuid() {}
        ///< destructor

    std::tstring_t create(cExType &type) const xWARN_UNUSED_RV;
        ///< generate GUID

private:
    std::tstring_t _randomBased() const xWARN_UNUSED_RV;
        ///< random based GUID

    xNO_COPY_ASSIGN(CxGuid)
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#include <xLib/Crypt/CxGuid.inl>
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxGuidH
