/**
 * \file  CxException.h
 * \brief exception
 */


#ifndef xLib_Debug_CxExceptionH
#define xLib_Debug_CxExceptionH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxException
    /// exception
{
public:
                           CxException ();
        ///< constructor
    virtual               ~CxException ();
        ///< destructor

    const std::tstring_t & what        () const xWARN_UNUSED_RV;
        ///< get message
    template<typename T>
    CxException &          operator << (const T &cMessageT);
        ///< put message

private:
    std::tstring_t         _m_sMessage;
        ///< message
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#include "CxException.inl"
//------------------------------------------------------------------------------
#endif // xLib_Debug_CxExceptionH
