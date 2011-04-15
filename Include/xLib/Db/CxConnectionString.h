/****************************************************************************
* Class name:  CxConnectionString
* Description: DB connection string
* File name:   CxConnectionString.h
* Compilers:   Visual C++ 2010, C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     30.09.2010 9:30:14
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Db_CxConnectionStringH
#define xLib_Db_CxConnectionStringH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxConnectionString : public CxNonCopyable {
	public:
		static tString sMSJetOleDb40     (const tString &csDataSource, const tString &csUserId, const tString &csPassword, const tString &csDatabasePassword);

	private:
				       CxConnectionString();
		virtual       ~CxConnectionString();
};
//---------------------------------------------------------------------------
#endif //xLib_Db_CxConnectionStringH
