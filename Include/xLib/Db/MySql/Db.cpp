/**
 * \file  Db.cpp
 * \brief MySql DB
 */


#include "Db.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/Format.h>

#include <xLib/Db/MySql/Connection.h>
#include <xLib/Db/MySql/Recordset.h>


namespace xl::db::mysql
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Db::Db(
	cOptions &a_options
) :
	_options{a_options}
{
}
//-------------------------------------------------------------------------------------------------
bool_t
Db::isExists()
{
    bool_t bRv {};

    Options options = _options;
    options.db = {};

    Connection conn;
    {
        bRv = conn.get().isValid();
        xCHECK_RET(!bRv, false);

        conn.connect(options);
        conn.query(
            xT("SELECT IF (EXISTS(SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA "
               "WHERE SCHEMA_NAME = '%s'), 'true', 'false')"),
			   options.db.c_str());
    }

    {
        Recordset rec(conn, false);

        bRv = rec.get().isValid();
        xTEST(bRv);
        xTEST_EQ(rec.rows(), std::size_t(1));

        std::vec_tstring_t row;
        rec.fetchRow(&row);
        xTEST_EQ(row.size(), static_cast<size_t>(1));
        xCHECK_RET(StringCI::compare(xT("false"), row[0]), false);
        xTEST_EQ(StringCI::compare(xT("true"), row[0]), true);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
void_t
Db::create()
{
	std::ctstring_t db = _options.db;

	Options options = _options;
	options.db = {};

	Connection conn;
	conn.connect(options);
	conn.query(xT("CREATE DATABASE IF NOT EXISTS `%s` CHARACTER SET utf8"), db.c_str());
}
//-------------------------------------------------------------------------------------------------
void_t
Db::drop()
{
	Options options = _options;
	options.db = {};

	Connection conn;
	conn.connect(options);
	conn.query(xT("DROP DATABASE IF EXISTS `%s`"), _options.db.c_str());
}
//-------------------------------------------------------------------------------------------------

} // namespace
