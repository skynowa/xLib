/**
 * \file  Error.cpp
 * \brief MySql error
 */


#include "Error.h"

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

    return ::mysql_errno( const_cast<Connection &>(_conn).get().get() );
}
//-------------------------------------------------------------------------------------------------
bool_t
Error::isOk() const
{
    return (code() == 0);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Error::str() const
{
    xTEST(_conn.get().isValid());

    std::tstring_t sRv;

    cuint_t    code_ = code();
    cptr_cchar str   = ::mysql_error(_conn.get().get());
    xTEST_PTR(str);

    if ( isOk() ) {
        sRv = Format::str(xT("{} - \"{}\""), code_, xT("Success"));
    } else {
        sRv = Format::str(xT("{} - \"{}\", SQL: \"{}\""), code_, str, _sql);
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------


} // namespace
