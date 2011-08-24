/****************************************************************************
* Class name:  CxLocale
* Description: locale
* File name:   CxLocale.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     09.08.2009 19:47:14
*
*****************************************************************************/


#ifndef xLib_Common_CxLocaleH
#define xLib_Common_CxLocaleH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxLocale :
    public CxNonCopyable
{
    public:
       static tString sGetCurrent();
       	   ///< get current
       static BOOL    bSetCurrent(const tString &csLocale);
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
