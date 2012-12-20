/**
 * \file  CxSingleton.h
 * \brief singleton
 */


#ifndef xLib_Patterns_CxSingletonH
#define xLib_Patterns_CxSingletonH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

template <typename T>
class CxSingleton :
    private CxNonCopyable
    /// singleton
{
    public:
        static T &get()
            ///< get object instance
        {
            static T singletonT;
            return singletonT;
        }

    private:
                 CxSingleton() { };
            ///< constructor
        virtual ~CxSingleton() { };
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Patterns_CxSingletonH


#if xTODO
    template <typename T>
    class CxSingleton {
        public:
            static CxSingleton &Instance();

        private:
            CxSingleton();
    };

    template <typename T>
    CxSingleton<T> &CxSingleton<T>::Instance() {
        static CxSingleton theSingleInstance;

        return theSingleInstance;
    }

    template <typename T>
    T &CxSingleton<T>::Instance() {
        Create();

        T *p;
        if (!Locked() && (p = Obj().p)) {
            return *p;
        }

        throw E_AccessViolation("Uutl::Singleton<T>::Instance");
    }
#endif
