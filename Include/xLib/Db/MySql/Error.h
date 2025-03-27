/**
 * \file  Error.h
 * \brief Error
 */


#pragma once

#include <xLib/Db/MySql/Common.h>
#include <xLib/Interface/IError.h>
//-------------------------------------------------------------------------------------------------
namespace xl::db::mysql
{

class Connection;

class Error final :
	public xl::interface_::IError<uint_t>
    /// MySql error
{
public:
///\name ctors, dtor
///\{
	explicit Error(const Connection &conn);
			 Error(const Connection &conn, std::ctstring_t &sql);
	virtual ~Error() = default;

	xNO_DEFAULT_CONSTRUCT(Error);
	xNO_COPY_ASSIGN(Error);
///\}

///\name Overrides
///\{
	uint_t         code() const final;
	bool_t         isOk() const final;
	std::tstring_t category() const final;
	std::tstring_t message() const final;
///\}

private:
    const Connection &_conn;   ///< handler for one database connection
    std::ctstring_t   _sql;    ///< SQL - extra message
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * \file  Error.h
 * \todo
 *
 * - Tests
 */
