/**
 * \file  CxNonAssignable.h
 * \brief non assignable class
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxNonAssignable
    /// non assignable class
{
public:

protected:
             CxNonAssignable() { ; }
        ///< constructor
    virtual ~CxNonAssignable() { ; }
        ///< dectructor

private:
    const CxNonAssignable &operator = (const CxNonAssignable &);
        ///< operator =
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
