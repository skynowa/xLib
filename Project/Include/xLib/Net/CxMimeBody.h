/**
 * \file  CxMimeBody.h
 * \brief MIME body (RFC 822)
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxMimeBody :
    private CxNonCopyable
    /// MIME body (RFC 822)
{
public:
            CxMimeBody();
   virtual ~CxMimeBody();

private:
    std::mmap_tstring_t _body;
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY

#endif
