/****************************************************************************
* Class name:  CxTest_CxFile
* Description: test CxFile
* File name:   CxTest_CxFile.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxFileH
#define CxTest_CxFileH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/CxFile.h>
//---------------------------------------------------------------------------
class CxTest_CxFile :
    public CxTest
{
	public:
		               CxTest_CxFile();
		virtual       ~CxTest_CxFile();

		virtual  BOOL  bUnit        (const ULONGLONG cullBlockLoops);

	private:
        BOOL           bUnit1       (const ULONGLONG cullBlockLoops);
        BOOL           bUnitePrivate(const ULONGLONG cullBlockLoops);

};
//---------------------------------------------------------------------------
#endif //CxTest_CxFileH
