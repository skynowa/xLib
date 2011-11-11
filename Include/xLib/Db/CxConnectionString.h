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
    public CxNonCopyable
    /// DB connection string
{
    public:
        static std::string_t sMSJetOleDb40     (const std::string_t &csDataSource, const std::string_t &csUserId, const std::string_t &csPassword, const std::string_t &csDatabasePassword);
            ///< Microsoft.Jet.OLEDB.4.0

    private:
                            CxConnectionString();
            ///< constructor
        virtual            ~CxConnectionString();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Db_CxConnectionStringH
