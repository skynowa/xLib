/**
 * \file  CxMimeMessage.cpp
 * \brief MIME message (RFC 822)
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Log/CxTracer.h>
#include <xLib/Net/CxMimeHeader.h>
#include <xLib/Net/CxMimeBody.h>


xNAMESPACE_BEGIN(NxLib)

//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxMimeMessage::parse(
    std::ctstring_t &a_rawMessage,
    CxMimeheader    &a_header,
    CxMimebody      &a_body
)
{
    xNOT_IMPLEMENTED;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxMimeMessage::loadFromRawFile(
    std::ctstring_t &a_filePath
)
{
    xNOT_IMPLEMENTED;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxMimeMessage::saveToRawFile(
    std::ctstring_t &a_filePath
)
{
    xNOT_IMPLEMENTED;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

