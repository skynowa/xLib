/****************************************************************************
* Class name:  CxTest_CxStdioFile
* Description: test CxStdioFile
* File name:   CxTest_CxStdioFile.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxStdioFileH
#define CxTest_CxStdioFileH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/CxStdioFile.h>
//---------------------------------------------------------------------------
class CxTest_CxStdioFile :
    public CxTest
{
	public:
		         CxTest_CxStdioFile();
		virtual ~CxTest_CxStdioFile();

		virtual  BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxStdioFileH
