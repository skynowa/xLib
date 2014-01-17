/**
 * \file  CxFunctorT.h
 * \brief function object
 */


#pragma once

#ifndef xLib_CxFunctorTH
#define xLib_CxFunctorTH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(xlib)

template <class ClassT, class ReturnT, class ParamT>
class CxFunctorT
    /// function object
{
public:
    typedef   ReturnT (ClassT::*method_t)(ParamT);
        ///< return type

              CxFunctorT(ClassT *object, const method_t &method);
        ///< constructor
    virtual  ~CxFunctorT() {}
        ///< destructor

    ReturnT   operator () (const ParamT &param) const xWARN_UNUSED_RV;
        ///< operator ()
    ReturnT   execute(const ParamT &param) const xWARN_UNUSED_RV;
        ///< execute operator ()

private:
    ClassT   *_object;
    method_t  _method;

    xNO_COPY_ASSIGN(CxFunctorT)
};

xNAMESPACE_END(xlib)
//-------------------------------------------------------------------------------------------------
#include "CxFunctorT.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxFunctorTH
