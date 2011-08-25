/**
 * \file  CxConnectionString.h
 * \brief DB connection string
 */


#ifndef xLib_Db_CxConnectionStringH
#define xLib_Db_CxConnectionStringH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxConnectionString :
    public CxNonCopyable
{
    public:
        static std::tstring sMSJetOleDb40     (const std::tstring &csDataSource, const std::tstring &csUserId, const std::tstring &csPassword, const std::tstring &csDatabasePassword);

    private:
                       CxConnectionString();
        virtual       ~CxConnectionString();
};
//---------------------------------------------------------------------------
#endif //xLib_Db_CxConnectionStringH
