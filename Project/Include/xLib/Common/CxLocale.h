/**
 * \file  CxLocale.h
 * \brief locale
 */


#ifndef xLib_Common_CxLocaleH
#define xLib_Common_CxLocaleH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxLocale :
    private CxNonCopyable
    /// locale
{
    public:
       static std::tstring_t sGetCurrent();
              ///< get current
       static bool           bSetCurrent(const std::tstring_t &csLocale);
                 ///< set current
       static bool           bSetDefault();
                 ///< set default

    private:
                             CxLocale   ();
           ///< constructor
       virtual              ~CxLocale   ();
                 ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Common_CxLocaleH
