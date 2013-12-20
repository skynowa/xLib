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

class CxMimeBody
    /// MIME body (RFC 822)
{
public:
            CxMimeBody();
   virtual ~CxMimeBody();

private:
    std::mmap_tstring_t _body;

    xNO_COPY_ASSIGN(CxMimeBody)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxMimeBody.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxMimeBodyH
