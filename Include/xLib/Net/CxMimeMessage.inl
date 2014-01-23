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
#include <xLib/Log/CxTrace.h>
#include <xLib/Net/CxMimeHeader.h>
#include <xLib/Net/CxMimeBody.h>


xNAMESPACE2_BEGIN(xlib, net)

//-------------------------------------------------------------------------------------------------
inline
CxMimeMessage::CxMimeMessage() :
    _rawMessage()
{
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMimeMessage::parse(
    std::ctstring_t &a_rawMessage,
    CxMimeHeader    &a_header,
    CxMimeBody      &a_body
)
{
    xUNUSED(a_rawMessage);
    xUNUSED(a_header);
    xUNUSED(a_body);

    xNOT_IMPLEMENTED;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMimeMessage::loadFromRawFile(
    std::ctstring_t &a_filePath ///< raw msg
)
{
    xUNUSED(a_filePath);

    xNOT_IMPLEMENTED;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxMimeMessage::saveToRawFile(
    std::ctstring_t &a_filePath ///< raw msg
)
{
    xUNUSED(a_filePath);

    xNOT_IMPLEMENTED;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, net)
