/**
 * \file  Query.cpp
 * \brief SQL query
 */


#include "Query.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/Format.h>


namespace xl::db::mysql
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Query::Query(
	const Connection &a_conn
) :
	_conn{a_conn}
{
    xTEST(_conn.get().isValid());
}
//-------------------------------------------------------------------------------------------------
void_t
Query::exec(
	std::ctstring_t &a_sql
) const
{
    xTEST(_conn.get().isValid());

    std::cstring_t &asSql = xT2A(a_sql);

    int_t iRv = ::mysql_real_query(_conn.get().get(), asSql.data(),
        static_cast<ulong_t>( asSql.size() ));
    xTEST_EQ_MSG(iRv, 0, Error(_conn, a_sql).str());
}
//-------------------------------------------------------------------------------------------------
void_t
Query::exec(
    cptr_ctchar_t a_sqlFormat, ...
) const
{
	xTEST(_conn.get().isValid());
	xTEST_PTR(a_sqlFormat);

	std::tstring_t sql;
	{
		va_list args;
		xVA_START(args, a_sqlFormat);

		sql = FormatC::strV(a_sqlFormat, args);

		xVA_END(args);
	}

	return exec(sql);
}
//-------------------------------------------------------------------------------------------------
/**
 * If the ANSI_QUOTES SQL mode is enabled:
 *
 * string literals can be quoted only within single quotation marks because
 * a string quoted within double quotation marks is interpreted as an identifier.
 */
std::tstring_t
Query::escapeQuoted(
	std::ctstring_t &a_sqlValue,	///< SQL string value
	std::ctstring_t &a_forQuote		///< str (char) in which the escaped string is to be placed
									///< \note (maybe an empty)
) const
{
	xTESTS_NA(a_sqlValue);
	xTESTS_NA(a_forQuote);

	if ( a_sqlValue.empty() ) {
		return (a_forQuote + a_forQuote);
	}

	if (a_sqlValue == nullStr) {
	   /**
		* If the argument is NULL:
		*
		* the return value is the word “NULL” without enclosing single quotation marks
		*/
		return a_sqlValue;
	}

	// escape
	std::tstring_t sRv(a_sqlValue.size() * 2 + 1, xT('\0'));
	{
		culong_t quotedSize = ::mysql_real_escape_string_quote(_conn.get().get(), &sRv[0],
			a_sqlValue.data(), static_cast<ulong_t>(a_sqlValue.size()), xT2A(a_forQuote)[0]);
		xTEST_GR_MSG(quotedSize, 0UL, Error(_conn).str());

		sRv.resize(quotedSize * sizeof(std::tstring_t::value_type));
	}

	// quoted
	{
		sRv = a_forQuote + sRv + a_forQuote;
	}

	return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Query::escapeQuotedSqm(
	std::ctstring_t &a_sqlValue	///< SQL string value
) const
{
	return escapeQuoted(a_sqlValue, Const::sqm());
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Query::escapeQuotedDqm(
	std::ctstring_t &a_sqlValue	///< SQL string value
) const
{
	return escapeQuoted(a_sqlValue, Const::dqm());
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Query::escapeQuotedGa(
	std::ctstring_t &a_sqlValue	///< SQL string value
) const
{
	return escapeQuoted(a_sqlValue, Const::ga());
}
//-------------------------------------------------------------------------------------------------

} // namespace
