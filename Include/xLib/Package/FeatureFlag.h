/**
 * \file  FeatureFlag.h
 * \brief Feature flag / toggle
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, package)

class FeatureFlag
    ///< Feature flag / toggle
{
public:
             FeatureFlag();
        ///< constructor
    virtual ~FeatureFlag();
        ///< destructor

private:
    xNO_COPY_ASSIGN(FeatureFlag)

xPLATFORM_IMPL:
    void_t   _construct_impl();
    void_t   _destruct_impl();
};

xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------
