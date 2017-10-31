/**
 * \file   CurlClient.h
 * \brief  CURL client
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, Package)

class CurlClient
    ///< CURL client
{
public:
             CurlClient();
        ///< constructor
    virtual ~CurlClient();
        ///< destructor

private:
    xNO_COPY_ASSIGN(CurlClient)
};

xNAMESPACE_END2(xl, Package)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "CurlClient.cpp"
#endif
