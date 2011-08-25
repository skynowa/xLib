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
{
    public:
       static std::tstring sGetCurrent();
       	   ///< get current
       static BOOL    bSetCurrent(const std::tstring &csLocale);
   	   	   ///< set current
       static BOOL    bSetDefault();
   	   	   ///< set default

    private:
                      CxLocale   ();
           ///< constructor
       virtual       ~CxLocale   ();
   	   	   ///< destructor
};
//---------------------------------------------------------------------------
#endif    //xLib_Common_CxLocaleH
