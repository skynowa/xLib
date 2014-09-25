/**
 * \file  MimeMessage.inl
 * \brief MIME message (RFC 822)
 */


#if !xOPTION_HEADER_ONLY
    #include "MimeMessage.h"
#endif

#include <xLib/Test/Test.h>
#include <xLib/Debug/Debug.h>
#include <xLib/Debug/NativeError.h>
#include <xLib/Debug/StdError.h>
#include <xLib/Debug/StackTrace.h>
#include <xLib/Debug/ErrorReport.h>
#include <xLib/Debug/Debugger.h>
#include <xLib/Log/Trace.h>
#include <xLib/Net/MimeHeader.h>
#include <xLib/Net/MimeBody.h>


xNAMESPACE_BEGIN2(xlib, net)

//-------------------------------------------------------------------------------------------------
inline
MimeMessage::MimeMessage() :
    _rawMessage()
{
}
//-------------------------------------------------------------------------------------------------
inline void_t
MimeMessage::parse(
    std::ctstring_t &a_rawMessage,
    MimeHeader    &a_header,
    MimeBody      &a_body
)
{
    xUNUSED(a_rawMessage);
    xUNUSED(a_header);
    xUNUSED(a_body);

    xNOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------
inline void_t
MimeMessage::loadFromRawFile(
    std::ctstring_t &a_filePath ///< raw msg
)
{
    xUNUSED(a_filePath);

    xNOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------
inline void_t
MimeMessage::saveToRawFile(
    std::ctstring_t &a_filePath ///< raw msg
)
{
    xUNUSED(a_filePath);

    xNOT_IMPLEMENTED
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, net)
