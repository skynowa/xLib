/****************************************************************************
* Class name:  CxConnectionString
* Description: DB connection string
* File name:   CxConnectionString.cpp
* Compilers:   Visual C++ 2010, C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     30.09.2010 9:30:14
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#include <xLib/Db/CxConnectionString.h>


/****************************************************************************
*    public                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: -  sMSJetOleDb40 (Microsoft.Jet.OLEDB.4.0)
/*static*/
tString CxConnectionString::sMSJetOleDb40(const tString &csDataSource, const tString &csUserId, const tString &csPassword, const tString &csDatabasePassword) {
    /*DEBUG*/xASSERT_RET(false == CxString::sTrimSpace(csDataSource).empty(), tString());
	/*DEBUG*/// csPassword         - n/a
	/*DEBUG*/// csUserId           - n/a
	/*DEBUG*/// csDatabasePassword - n/a
    
	tString sRes;

	sRes =
    	tString() +
		xT("Provider                                 = Microsoft.Jet.OLEDB.4.0;")               				+
		xT("Data Source                              = ") + CxString::sTrimSpace(csDataSource) + xT(";")       	+
		xT("Extended Properties                      = ;")                                     					+
		xT("Jet OLEDB:Compact Without Replica Repair = False;")                                 				+
		xT("Jet OLEDB:Create System Database         = False;")                                 				+
		xT("Jet OLEDB:Database Locking Mode          = 1;")                                    					+
		xT("Jet OLEDB:Database Password              = ") + CxString::sTrimSpace(csDatabasePassword) + xT(";") +
		xT("Jet OLEDB:Don't Copy Locale on Compact   = False;")                                 				+
		xT("Jet OLEDB:Encrypt Database               = False;")                                 				+
		xT("Jet OLEDB:Engine Type                    = 0;")                                     				+
		xT("Jet OLEDB:Global Bulk Transactions       = 1;")                                     				+
		xT("Jet OLEDB:Global Partial Bulk Ops        = 2;")                                     				+
		xT("Jet OLEDB:New Database Password          = ;")                                      				+
		xT("Jet OLEDB:Registry Path                  = ;")                                      				+
		xT("Jet OLEDB:SFP                            = False;")                                 				+
		xT("Jet OLEDB:System database                = ;")                                      				+
		xT("Locale Identifier                        = 1033;")                                  				+
		xT("Mode                                     = ReadWrite;")   			                +
		xT("Password                                 = ") + CxString::sTrimSpace(csPassword) + xT(";")         	+
		xT("Persist Security Info                    = False;")                                 				+
		xT("User ID                                  = ") + CxString::sTrimSpace(csUserId)   + xT(";");

    return sRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private                                                         
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: - CxConnectionString (comment)
CxConnectionString::CxConnectionString() {
	
}
//---------------------------------------------------------------------------
//TODO: - ~CxConnectionString (comment)
/*virtual*/
CxConnectionString::~CxConnectionString() {
	
}
//---------------------------------------------------------------------------




