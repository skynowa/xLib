/**
 * \file  CxFunctorT.h
 * \brief function object
 */


#ifndef xLib_Common_CxFunctorH
#define xLib_Common_CxFunctorH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

template <class ClassT, typename ReturnT, typename ParamT>
class CxFunctorT
    /// function object
{
    public:
        typedef  ReturnT   (ClassT::*Method)(ParamT);
            ///< return type

                 CxFunctorT(ClassT *pObject, Method method);
            ///< constructor
        virtual ~CxFunctorT();
            ///< destructor

        ReturnT  operator()(ParamT Param);
            ///< operator ()
        ReturnT  Execute   (ParamT Param);
            ///< execute operator ()

    private:
        ClassT  *_m_pObject;
        Method   _m_Method;
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#include <Common/CxFunctorT.inl>
//---------------------------------------------------------------------------
#endif //xLib_Common_CxFunctorH


#if xTODO
    class thread_adapter {
        public:
            thread_adapter(void (*func)(void *), void *param) :
                _func (func),
                _param(param)
            {
            }

            void operator()() const {
                _func(_param);
            }

        private:
            void (*_func)(void *);
            void *_param;
    };

    //http://habrahabr.ru/blogs/cpp/111680/
#endif
