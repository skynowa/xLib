/**
 * \file  CxNonCopyable.h
 * \brief non copyable class
 */


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
