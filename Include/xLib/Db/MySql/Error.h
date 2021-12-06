/**
 * \file  Error.h
 * \brief MySql error
 */


#pragma once

#include <xLib/Db/MySql/Common.h>
//-------------------------------------------------------------------------------------------------
namespace xl::db::mysql
{

class Connection;

class Error :
	public xl::interface::ILastError<uint_t>
    /// MySql connection
{
public:
///@name ctors, dtor
///@{
			 Error(const Connection &conn);
	virtual ~Error();

	xNO_COPY_ASSIGN(Error)
///@}

    // errors
    uint_t         lastError() const override;
        ///< error code for the most recently invoked API function that can succeed or fail
    std::tstring_t lastErrorStr() const override;
        ///< error message for the most recently invoked API function that failed

private:
    const Connection &_conn; ///< handler for one database connection
};

} // namespace
//-------------------------------------------------------------------------------------------------

/**
 * TODO:
 *
 * - lastError -> code, lastErrorStr -> str
 * - Tests
 */
