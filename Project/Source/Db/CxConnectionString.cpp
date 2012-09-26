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
/* static */
std::tstring_t
CxConnectionString::sMSJetOleDb40(
    const std::tstring_t &a_csDataSource,
    const std::tstring_t &a_csUserId,
    const std::tstring_t &a_csPassword,
    const std::tstring_t &a_csDatabasePassword
)
{
    /*DEBUG*/xASSERT_RET(false == CxString::sTrimSpace(a_csDataSource).empty(), std::tstring_t());
    /*DEBUG*/// csPassword         - n/a
    /*DEBUG*/// csUserId           - n/a
    /*DEBUG*/// csDatabasePassword - n/a

    std::tstring_t sRv;

    sRv =
        std::tstring_t() +
        xT("Provider                                 = Microsoft.Jet.OLEDB.4.0;")                               +
        xT("Data Source                              = ") + CxString::sTrimSpace(a_csDataSource) + xT(";")      +
        xT("Extended Properties                      = ;")                                                      +
        xT("Jet OLEDB:Compact Without Replica Repair = False;")                                                 +
        xT("Jet OLEDB:Create System Database         = False;")                                                 +
        xT("Jet OLEDB:Database Locking Mode          = 1;")                                                     +
        xT("Jet OLEDB:Database Password              = ") + CxString::sTrimSpace(a_csDatabasePassword) + xT(";")+
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
        xT("Password                                 = ") + CxString::sTrimSpace(a_csPassword) + xT(";")        +
        xT("Persist Security Info                    = False;")                                                 +
        xT("User ID                                  = ") + CxString::sTrimSpace(a_csUserId)   + xT(";");

    return sRv;
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
/* virtual */
CxConnectionString::~CxConnectionString() {

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
