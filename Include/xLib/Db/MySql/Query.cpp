/**
 * \file  Query.cpp
 * \brief SQL query
 */


#include "Query.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/Format.h>
#include <xLib/Db/MySql/Result.h>


namespace xl::db::mysql
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Query::Query(
	const Connection &a_conn,
	std::ctstring_t  &a_sql
) :
	_conn{a_conn},
	_sql {a_sql}
{
    xTEST(_conn.get().isValid());
}
//-------------------------------------------------------------------------------------------------
void_t
Query::exec() const
{
    xTEST(_conn.get().isValid());

    std::cstring_t &asSql = xT2A(_sql);

    int_t iRv = ::mysql_real_query(_conn.get().get(), asSql.data(),
        static_cast<ulong_t>( asSql.size() ));
    xTEST_EQ_MSG(iRv, 0, Error(_conn, _sql).str());
}
//-------------------------------------------------------------------------------------------------
StoreResult
Query::store() const
{
	exec();

	return StoreResult( const_cast<Connection &>(_conn) );
}
//-------------------------------------------------------------------------------------------------
UseResult
Query::use() const
{
	exec();

	return UseResult( const_cast<Connection &>(_conn) );
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
EscapeQuoted::EscapeQuoted(
	const Connection &a_conn,		///<
	std::ctstring_t  &a_sqlValue	///< SQL string value
) :
	_conn    {a_conn},
	_sqlValue{a_sqlValue}
{
    xTEST(_conn.get().isValid());
}
//-------------------------------------------------------------------------------------------------
/**
 * If the ANSI_QUOTES SQL mode is enabled:
 *
 * string literals can be quoted only within single quotation marks because
 * a string quoted within double quotation marks is interpreted as an identifier.
 *
 * \see https://dev.mysql.com/doc/c-api/8.0/en/mysql-real-escape-string-quote.html
 */
std::tstring_t
EscapeQuoted::forQuote(
	std::ctstring_t &a_quote	///< Quote str (char)
) const
{
	xTEST(!a_quote.empty());

	if ( _sqlValue.empty() ) {
		return (a_quote + a_quote);
	}

	if (_sqlValue == nullStr) {
	   /**
		* If the argument is NULL:
		*
		* the return value is the word “NULL” without enclosing single quotation marks
		*/
		return _sqlValue;
	}

	// escape
	std::tstring_t sRv(_sqlValue.size() * 2 + 1, xT('\0'));
	{
		cchar forQuote {xT2A(a_quote)[0]};
			///< String (char) in which the escaped string is to be placed

		culong_t quotedSize = ::mysql_real_escape_string_quote(_conn.get().get(), &sRv[0],
			_sqlValue.data(), static_cast<ulong_t>(_sqlValue.size()), forQuote);
		xTEST_GR_MSG(quotedSize, 0UL, Error(_conn).str());

		sRv.resize(quotedSize * sizeof(std::tstring_t::value_type));
	}

	// quoted
	{
		sRv = a_quote + sRv + a_quote;
	}

	return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
EscapeQuoted::forSqm() const
{
	return forQuote(Const::sqm());
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
EscapeQuoted::forDqm() const
{
	return forQuote(Const::dqm());
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
EscapeQuoted::forGa() const
{
	return forQuote(Const::ga());
}
//-------------------------------------------------------------------------------------------------

} // namespace
