/**
 * \file  CxConnectionString.cpp
 * \brief DB connection string
 */


#include <xLib/Db/CxConnectionString.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
std::string_t
CxConnectionString::sMSJetOleDb40(
    const std::string_t &csDataSource,
    const std::string_t &csUserId,
    const std::string_t &csPassword,
    const std::string_t &csDatabasePassword
)
{
    /*DEBUG*/xASSERT_RET(false == CxString::sTrimSpace(csDataSource).empty(), std::string_t());
    /*DEBUG*/// csPassword         - n/a
    /*DEBUG*/// csUserId           - n/a
    /*DEBUG*/// csDatabasePassword - n/a

    std::string_t sRes;

    sRes =
        std::string_t() +
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

xNAMESPACE_END(NxLib)
