/****************************************************************************
* Class name:  CxNonAssignable
* Description: non assignable class
* File name:   CxNonAssignable.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     09.11.2009 11:11::00
*
*****************************************************************************/


#ifndef xLib_Common_CxNonAssignableH
#define xLib_Common_CxNonAssignableH
//---------------------------------------------------------------------------
class CxNonAssignable {
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
