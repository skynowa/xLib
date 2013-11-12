/**
 * \file  CxNonCopyable.h
 * \brief non copyable class
 */


#pragma once

#ifndef xLib_CxNonCopyableH
#define xLib_CxNonCopyableH
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxNonCopyable
    /// non copyable class
{
public:

protected:
             CxNonCopyable() { ; }
        ///< constructor
    virtual ~CxNonCopyable() { ; }
        ///< destructor

private:
             CxNonCopyable(const CxNonCopyable &);
        ///< constructor
    const CxNonCopyable &operator = (const CxNonCopyable &);
        ///< operator =
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxNonCopyableH
