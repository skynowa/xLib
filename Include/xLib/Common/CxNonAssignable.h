/**
 * \file  CxNonAssignable.h
 * \brief non assignable class
 */


#ifndef xLib_Common_CxNonAssignableH
#define xLib_Common_CxNonAssignableH
//---------------------------------------------------------------------------
class CxNonAssignable {
    /// non assignable class
    
	public:

	protected:
		 CxNonAssignable() { }
			///< constructor
		~CxNonAssignable() { }
			///< dectructor

	private:
		const CxNonAssignable &operator = (const CxNonAssignable &);
			///< operator =
};
//---------------------------------------------------------------------------
#endif    //xLib_CxNonAssignableH
