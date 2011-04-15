/****************************************************************************
* Class name:  CxNonAssignable
* Description: non assignable class
* File name:   CxNonAssignable.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     09.11.2009 11:11::00
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Common_CxNonAssignableH
#define xLib_Common_CxNonAssignableH
//---------------------------------------------------------------------------
class CxNonAssignable {
   protected:
       CxNonAssignable() {}
      ~CxNonAssignable() {}
      
   private:  
       const CxNonAssignable &operator = (const CxNonAssignable &);
};
//---------------------------------------------------------------------------
#endif	//xLib_CxNonAssignableH
