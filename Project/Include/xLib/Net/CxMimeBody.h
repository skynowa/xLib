/**
 * \file  CxMimeBody.h
 * \brief MIME body (RFC 822)
 */


#pragma once

#ifndef xLib_CxMimeBodyH
#define xLib_CxMimeBodyH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMimeBody :
    public CxNonCopyable
    /// MIME body (RFC 822)
{
public:
            CxMimeBody();
   virtual ~CxMimeBody();

private:
    std::mmap_tstring_t _body;
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include <Net/CxMimeBody.inl>
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxMimeBodyH
