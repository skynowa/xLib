/**
 * \file  CxType.h
 * \brief type info
 */


#ifndef xLib_Common_CxTypeH
#define xLib_Common_CxTypeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxType :
    private CxNonCopyable
    /// type info
{
    public:
        template<class T>
        static std::tstring_t sGetName   (const T &cObjectT);
            ///< get name

        template<class T>
        static std::tstring_t sGetRawName(const T &cObjectT);
            ///< get raw name

        template<class T1, class T2>
        static bool           bIsEquals  (const T1 &cObjectT1, const T2 &cObjectT2);
            ///< is equals
    private:
                              CxType     () {};
            ///< constructor
        virtual              ~CxType     () {};
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#include "CxType.inl"
//---------------------------------------------------------------------------
#endif //xLib_Common_CxTypeH
