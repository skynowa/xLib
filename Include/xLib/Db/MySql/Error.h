/**
 * \file  Error.h
 * \brief MySql error
 */


#pragma once

#include <xLib/Db/MySql/Common.h>
#include <xLib/Interface/ILastError.h>
//-------------------------------------------------------------------------------------------------
namespace xl::db::mysql
{

class Connection;

class Error :
	public xl::interface_::ILastError<uint_t>
    /// MySql connection
{
public:
///\name ctors, dtor
///\{
	explicit Error(const Connection &conn);
			 Error(const Connection &conn, std::ctstring_t &sql);
	virtual ~Error() = default;

	xNO_DEFAULT_CONSTRUCT(Error)
	xNO_COPY_ASSIGN(Error)
///\}

///\name Overrides
///\{
	uint_t         code() const final;
		///< error code for the most recently invoked API function that can succeed or fail
	bool_t         isOk() const final;
		///<
	std::tstring_t description() const final;
		///< error message for the most recently invoked API function that failed
///\}

private:
    const Connection &_conn;   ///< handler for one database connection
    std::ctstring_t   _sql;    ///< SQL - extra message
};

} // namespace
//-------------------------------------------------------------------------------------------------

/**
 * TODO:
 *
 * - Tests
 */
