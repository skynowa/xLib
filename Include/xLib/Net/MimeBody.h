/**
 * \file  MimeBody.h
 * \brief MIME body (RFC 822)
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, net)

class MimeBody
    /// MIME body (RFC 822)
{
public:
            MimeBody();
   virtual ~MimeBody();

private:
    std::mmap_tstring_t _body;

    xNO_COPY_ASSIGN(MimeBody)
};

xNAMESPACE_END2(xl, net)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "MimeBody.cpp"
#endif
