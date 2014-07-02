/**
 * \file   Guid.h
 * \brief  GUID (globally unique identifier)
 */


#pragma once

#include <xLib/Core/xCore.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, crypt)

class Guid
    /// GUID (globally unique identifier)
{
public:
    enum ExType
    {
        tpUnknown     = 0,
        tpRandomBased = 1

    };
    typedef const ExType cExType;

                   Guid() {}
        ///< constructor
    virtual       ~Guid() {}
        ///< destructor

    std::tstring_t create(cExType &type) const xWARN_UNUSED_RV;
        ///< generate GUID

private:
    std::tstring_t _randomBased() const xWARN_UNUSED_RV;
        ///< random based GUID

    xNO_COPY_ASSIGN(Guid)

xPLATFORM:
    std::tstring_t _randomBased_impl() const;
};

xNAMESPACE_END2(xlib, crypt)
//---------------------------------------------------------------------------
#include <xLib/Crypt/Guid.inl>
