/**
 * \file   Guid.h
 * \brief  GUID (globally unique identifier)
 */


#pragma once

#include <xLib/Core/Core.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, crypt)

class Guid
    /// GUID (globally unique identifier)
{
public:
    enum class Type
    {
        tpUnknown     = 0,
        tpRandomBased = 1

    };
    xUSING_CONST(Type);

                   Guid() {}
        ///< constructor
    virtual       ~Guid() {}
        ///< destructor

    std::tstring_t create(cType &type) const xWARN_UNUSED_RV;
        ///< generate GUID

    xNO_COPY_ASSIGN(Guid)

xPLATFORM_IMPL:
    std::tstring_t _randomBased_impl() const;
        ///< random based GUID
};

xNAMESPACE_END2(xl, crypt)
//---------------------------------------------------------------------------
