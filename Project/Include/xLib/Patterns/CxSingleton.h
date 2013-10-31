/**
 * \file  CxSingleton.h
 * \brief singleton
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

template <class T>
class CxSingleton :
    private CxNonCopyable
    /// singleton
{
public:
    static T &get() xWARN_UNUSED_RV
        ///< get object instance
    {
        static T singletonT;
        return singletonT;
    }

private:
             CxSingleton();
        ///< constructor
    virtual ~CxSingleton();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY

#endif


#if xTODO
    template <class T>
    class CxSingleton {
    public:
        static CxSingleton &Instance();

    private:
        CxSingleton();
    };

    template <class T>
    CxSingleton<T> &CxSingleton<T>::Instance() {
        static CxSingleton theSingleInstance;

        return theSingleInstance;
    }

    template <class T>
    T &CxSingleton<T>::Instance() {
        Create();

        T *p;
        if (!Locked() && (p = Obj().p)) {
            return *p;
        }

        throw E_AccessViolation("Uutl::Singleton<T>::Instance");
    }
#endif
