/**
 * \file  CxConnectionString.cpp
 * \brief DB connection string
 */


#include <xLib/Db/CxConnectionString.h>

#include <xLib/Core/CxString.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
/* static */
std::tstring_t
CxConnectionString::msJetOleDb40(
    std::ctstring_t &a_csDataSource,
    std::ctstring_t &a_csUserId,
    std::ctstring_t &a_csPassword,
    std::ctstring_t &a_csDatabasePassword
)
{
    xTEST_EQ(false, CxString::trimSpace(a_csDataSource).empty());
    xTEST_NA(a_csPassword);
    xTEST_NA(a_csUserId);
    xTEST_NA(a_csDatabasePassword);

    std::tstring_t sRv;

    sRv =
        std::tstring_t() +
        xT("Provider                                 = Microsoft.Jet.OLEDB.4.0;")                               +
        xT("Data Source                              = ") + CxString::trimSpace(a_csDataSource) + xT(";")       +
        xT("Extended Properties                      = ;")                                                      +
        xT("Jet OLEDB:Compact Without Replica Repair = False;")                                                 +
        xT("Jet OLEDB:Create System Database         = False;")                                                 +
        xT("Jet OLEDB:Database Locking Mode          = 1;")                                                     +
        xT("Jet OLEDB:Database Password              = ") + CxString::trimSpace(a_csDatabasePassword) + xT(";") +
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
        xT("Password                                 = ") + CxString::trimSpace(a_csPassword) + xT(";")         +
        xT("Persist Security Info                    = False;")                                                 +
        xT("User ID                                  = ") + CxString::trimSpace(a_csUserId)   + xT(";");

    return sRv;
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    private
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxConnectionString::CxConnectionString() {

}
//------------------------------------------------------------------------------
/* virtual */
CxConnectionString::~CxConnectionString() {

}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
