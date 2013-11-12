/**
 * \file  CxNonAssignable.h
 * \brief non assignable class
 */


#pragma once

#ifndef xLib_CxNonAssignableH
#define xLib_CxNonAssignableH
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
#endif // xLib_CxNonAssignableH
