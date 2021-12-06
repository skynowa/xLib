/**
 * \file  Error.cpp
 * \brief MySql error
 */


#include "Error.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/Format.h>

#include <xLib/Db/MySql/Recordset.h>


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
uint_t
Error::code() const
{
    xTEST(_conn.get().isValid());

    return ::mysql_errno( const_cast<Connection &>(_conn).get().get() );
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

    if (code_ == 0) {
        sRv = Format::str(xT("{} - \"{}\""), code_, xT("Success"));
    } else {
        sRv = Format::str(xT("{} - \"{}\""), code_, str);
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------


} // namespace
