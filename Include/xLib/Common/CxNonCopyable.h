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
   public:

   protected:
              CxNonCopyable() { }
              	  ///< constructor
             ~CxNonCopyable() { }
         	  	  ///< dectructor
   private:
              CxNonCopyable(const CxNonCopyable &);
          	  	  ///< constructor
        const CxNonCopyable &operator = (const CxNonCopyable &);
    	  	  	  ///< operator =
};
//---------------------------------------------------------------------------
#endif    //xLib_Common_CxNonCopyableH
