/**
 * \file  CxConnectionString.cpp
 * \brief DB connection string
 */


#include <xLib/Db/CxConnectionString.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
std::tstring
CxConnectionString::sMSJetOleDb40(
    const std::tstring &csDataSource,
    const std::tstring &csUserId,
    const std::tstring &csPassword,
    const std::tstring &csDatabasePassword
)
{
    /*DEBUG*/xASSERT_RET(false == CxString::sTrimSpace(csDataSource).empty(), std::tstring());
    /*DEBUG*/// csPassword         - n/a
    /*DEBUG*/// csUserId           - n/a
    /*DEBUG*/// csDatabasePassword - n/a

    std::tstring sRes;

    sRes =
        std::tstring() +
        xT("Provider                                 = Microsoft.Jet.OLEDB.4.0;")                               +
        xT("Data Source                              = ") + CxString::sTrimSpace(csDataSource) + xT(";")        +
        xT("Extended Properties                      = ;")                                                      +
        xT("Jet OLEDB:Compact Without Replica Repair = False;")                                                 +
        xT("Jet OLEDB:Create System Database         = False;")                                                 +
        xT("Jet OLEDB:Database Locking Mode          = 1;")                                                     +
        xT("Jet OLEDB:Database Password              = ") + CxString::sTrimSpace(csDatabasePassword) + xT(";")  +
        xT("Jet OLEDB:Don't Copy Locale on Compact   = False;")                                                 +
        xT("Jet OLEDB:Encrypt Database               = False;")                                                 +
        xT("Jet OLEDB:Engine Type                    = 0;")                                                     +
        xT("Jet OLEDB:Global Bulk Transactions       = 1;")                                                     +
        xT("Jet OLEDB:Global Partial Bulk Ops        = 2;")                                                     +
        xT("Jet OLEDB:New Database Password          = ;")                                                      +
        xT("Jet OLEDB:Registry Path                  = ;")                                                      +
        xT("Jet OLEDB:SFP                            = False;")                                                 +
        xT("Jet OLEDB:System database                = ;")                                                      +
        xT("Locale Identifier                        = 1033;")                                                  +
        xT("Mode                                     = ReadWrite;")                                             +
        xT("Password                                 = ") + CxString::sTrimSpace(csPassword) + xT(";")          +
        xT("Persist Security Info                    = False;")                                                 +
        xT("User ID                                  = ") + CxString::sTrimSpace(csUserId)   + xT(";");

    return sRes;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxConnectionString::CxConnectionString() {

}
//---------------------------------------------------------------------------
/*virtual*/
CxConnectionString::~CxConnectionString() {

}
//---------------------------------------------------------------------------
