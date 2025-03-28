/**
 * \file  Error.cpp
 * \brief Error
 */


#include "Error.h"

namespace xl::db::mysql
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Error::Error(
	const Connection &a_conn
) :
	_conn{a_conn}
{
}
//-------------------------------------------------------------------------------------------------
Error::Error(
	const Connection &a_conn,
	std::ctstring_t  &a_sql
) :
	_conn{a_conn},
	_sql {a_sql}
{
}
//-------------------------------------------------------------------------------------------------
uint_t
Error::code() const
{
    xTEST(_conn.get().isValid());

    return ::mysql_errno( _conn.get().get() );
}
//-------------------------------------------------------------------------------------------------
bool_t
Error::isOk() const
{
    return (code() == 0);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Error::category() const
{
    return xT("xl::db::mysql::Error");
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Error::message() const
{
    xTEST(_conn.get().isValid());

    if ( isOk() ) {
        return {};
    }

    std::tstring_t sRv;

    cptr_cchar_t descr = ::mysql_error(_conn.get().get());
    xTEST_PTR(descr);

    sRv = Format::str(xT("{}, SQL: \"{}\""), descr, _sql);

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
