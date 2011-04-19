/****************************************************************************
* Class name:  CxNonCopyable
* Description: non copyable class
* File name:   CxNonCopyable.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     02.09.2009 9:07:38
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
