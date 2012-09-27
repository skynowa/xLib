/**
 * \file  CxUtils.h
 * \brief functions like macroses
 */


#ifndef xLib_Common_CxUtilsH
#define xLib_Common_CxUtilsH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxDebugger;

class CxUtils :
    private CxNonCopyable
    /// help macroses
{
    public:
        template<class T>
        static inline void      ptrDeleteT         (T * &pPtrT);
            ///< delete object by pointer

        template<class T>
        static inline void      arrayDeleteT       (T * &pPtrT);
            ///< delete array by pointer

        template<class T>
        static inline void      ptrAssignT         (T * &pPtrT, const T &valueT);
            ///< assign pointer

        template <typename ArrayT, const size_t cuiArraySize>
        static inline size_t    arraySizeT         (const ArrayT (&)[cuiArraySize]);
            ///< get array size

        template <class T>
        static inline const T & maxT               (const T &cValue1T , const T &cValue2T);
            ///< get max value

        template <class T>
        static inline const T & minT               (const T &cValue1T , const T &cValue2T);
            ///< get min value

        template <class T>
        static inline void      swapT              (T &value1T, T &value2T);
            ///< swap variables

        // TODO: numericLimitsCheckT
        template <class T>
        static inline bool      numericLimitsCheckT(const T &cValueT);
            ///< check numeric limites for type

        template <class ToT, class FromT>
        static inline ToT       reinterpretCastT   (const FromT &pPtrT);
            ///< allows any pointer to be converted into any other pointer type

        static inline double    round              (const double &cdValue);
            ///< round double value to the integer part

        template <class T1, class T2>
        static inline double    safeDivT           (const T1 &cValue1T, const T2 &cValue2T);
            ///< safe division

    private:
                                CxUtils           ();
            ///< constructor
                               ~CxUtils           ();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#include "CxUtils.inl"
//---------------------------------------------------------------------------
#endif //xLib_Common_CxUtilsH
