/****************************************************************************
* Class name:  CxNonCopyable
* Description: non copyable class
* File name:   CxNonCopyable.h
* Compilers:   Visual C++ 2008
* String type: Ansi
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     02.09.2009 9:07:38
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Common_CxNonCopyableH
#define xLib_Common_CxNonCopyableH
//---------------------------------------------------------------------------
class CxNonCopyable {
   protected:
			  CxNonCopyable() /*throw ()*/ {}
			 ~CxNonCopyable() /*throw ()*/ {}
      
   private: 
		      //--CxNonCopyable(      CxNonCopyable &);
		      CxNonCopyable(const CxNonCopyable &);

		      //--CxNonCopyable &operator = (      CxNonCopyable &);
		const CxNonCopyable &operator = (const CxNonCopyable &);
};
//---------------------------------------------------------------------------
#endif	//xLib_Common_CxNonCopyableH
