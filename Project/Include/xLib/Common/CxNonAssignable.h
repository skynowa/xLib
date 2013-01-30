/**
 * \file  CxNonAssignable.h
 * \brief non assignable class
 */


#ifndef xLib_Common_CxNonAssignableH
#define xLib_Common_CxNonAssignableH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
#endif // xLib_Common_CxNonAssignableH
