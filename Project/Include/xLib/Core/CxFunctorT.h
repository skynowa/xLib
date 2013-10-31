/**
 * \file  CxFunctorT.h
 * \brief function object
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

template <class ClassT, class ReturnT, class ParamT>
class CxFunctorT
    /// function object
{
public:
    typedef   ReturnT (ClassT::*method_t)(ParamT);
        ///< return type

              CxFunctorT(ClassT *object, method_t method);
        ///< constructor
    virtual  ~CxFunctorT() {}
        ///< destructor

    ReturnT   operator()(ParamT param) xWARN_UNUSED_RV;
        ///< operator ()
    ReturnT   execute(ParamT param) xWARN_UNUSED_RV;
        ///< execute operator ()

private:
    ClassT   *_object;
    method_t  _method;
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#include "CxFunctorT.inl"

#if xXLIB_HEADER_ONLY

#endif


#if xTODO
    class thread_adapter {
        public:
            thread_adapter(void_t (*func)(void_t *), void_t *param) :
                _func (func),
                _param(param)
            {
            }

            void_t operator()() const {
                _func(_param);
            }

        private:
            void_t (*_func)(void_t *);
            void_t *_param;
    };

    //http://habrahabr.ru/blogs/cpp/111680/
#endif
