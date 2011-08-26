/**
 * \file   CxTest_CxMsgBoxT.h
 * \brief  test CxMsgBoxT
 */


#ifndef CxTest_CxMsgBoxTH
#define CxTest_CxMsgBoxTH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Gui/Dialogs/CxMsgBoxT.h>
//---------------------------------------------------------------------------
class CxTest_CxMsgBoxT :
    public CxTest
{
	public:
		              CxTest_CxMsgBoxT();
		    ///< constructor
	    virtual      ~CxTest_CxMsgBoxT();
	        ///< destructor

	    virtual BOOL  bUnit(const ULONGLONG cullBlockLoops);
	        ///< test unit

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxMsgBoxTH
