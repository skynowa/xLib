/**
 * \file  Translate.h
 * \brief Translate text
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Package/IRestClient.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, package)

class Translate :
	public IRestClient
    ///< Translate text
{
public:
             Translate();
        ///< constructor
    virtual ~Translate();
        ///< destructor

private:
    xNO_COPY_ASSIGN(Translate)
};

xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------
