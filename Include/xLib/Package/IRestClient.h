/**
 * \file  IRestClient.h
 * \brief REST API client
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, package)

class IRestClient
    ///< REST API client
{
public:
             IRestClient();
        ///< constructor
    virtual ~IRestClient();
        ///< destructor

	/// TODO: Version
	/// TODO: Credentials
	/// TODO: Config
	/// TODO: Log
	/// TODO: Temp dirs
	/// TODO: HttpClient
	/// TODO: DbClient
	/// TODO: IRequest / IResponse
	/// TODO: Json/Xml/Csv
	/// TODO: MailClient / SlackClient
	/// TODO: ErrorReport

private:
    xNO_COPY_ASSIGN(IRestClient)
};

xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------
