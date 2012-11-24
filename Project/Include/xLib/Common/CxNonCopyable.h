/**
 * \file  CxNonCopyable.h
 * \brief non copyable class
 */


#ifndef xLib_Common_CxNonCopyableH
#define xLib_Common_CxNonCopyableH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxNonCopyable
    /// non copyable class
{
    public:

    protected:
                 CxNonCopyable() { ; }
            ///< constructor
        virtual ~CxNonCopyable() { ; }
            ///< dectructor

    private:
                 CxNonCopyable(const CxNonCopyable &);
            ///< constructor
        const CxNonCopyable &operator = (const CxNonCopyable &);
            ///< operator =
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    // xLib_Common_CxNonCopyableH
