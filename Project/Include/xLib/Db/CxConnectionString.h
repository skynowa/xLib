/**
 * \file  CxConnectionString.h
 * \brief DB connection string
 */


#pragma once

#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxConnectionString :
    private CxNonCopyable
    /// DB connection string
{
public:
    static std::tstring_t msJetOleDb40      (std::ctstring_t &csDataSource, std::ctstring_t &csUserId,
                                             std::ctstring_t &csPassword,   std::ctstring_t &csDatabasePassword) xWARN_UNUSED_RV;
        ///< Microsoft.Jet.OLEDB.4.0

private:
                          CxConnectionString();
        ///< constructor
    virtual              ~CxConnectionString();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
