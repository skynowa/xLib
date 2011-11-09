/**
 * \file  CxLocale.h
 * \brief locale
 */


#ifndef xLib_Common_CxLocaleH
#define xLib_Common_CxLocaleH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxLocale :
    public CxNonCopyable
    /// locale
{
    public:
       static std::string_t sGetCurrent();
              ///< get current
       static BOOL         bSetCurrent(const std::string_t &csLocale);
                 ///< set current
       static BOOL         bSetDefault();
                 ///< set default

    private:
                           CxLocale   ();
           ///< constructor
       virtual            ~CxLocale   ();
                 ///< destructor
};
//---------------------------------------------------------------------------
#endif    //xLib_Common_CxLocaleH
