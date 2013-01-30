/**
 * \file  CxConnectionString.h
 * \brief DB connection string
 */


#ifndef xLib_Db_CxConnectionStringH
#define xLib_Db_CxConnectionStringH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxConnectionString :
    private CxNonCopyable
    /// DB connection string
{
public:
    static std::tstring_t sMSJetOleDb40     (const std::tstring_t &csDataSource, const std::tstring_t &csUserId,
                                             const std::tstring_t &csPassword,   const std::tstring_t &csDatabasePassword);
        ///< Microsoft.Jet.OLEDB.4.0

private:
                          CxConnectionString();
        ///< constructor
    virtual              ~CxConnectionString();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Db_CxConnectionStringH
