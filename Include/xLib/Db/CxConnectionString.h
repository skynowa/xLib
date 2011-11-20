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
        static std::tstring sMSJetOleDb40     (const std::tstring &csDataSource, const std::tstring &csUserId, const std::tstring &csPassword, const std::tstring &csDatabasePassword);
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
