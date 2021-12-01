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
	cOptions &a_data
) :
	_data{a_data}
{
}
//-------------------------------------------------------------------------------------------------
bool_t
Db::isExists()
{
    bool_t bRv {};

    Options data = _data;
    data.db = {};

    Connection conn;
    {
        bRv = conn.get().isValid();
        xCHECK_RET(!bRv, false);

        conn.connect(data);
        conn.query(
            xT("SELECT IF (EXISTS(SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA "
               "WHERE SCHEMA_NAME = '%s'), 'true', 'false')"),
               data.db.c_str());
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
	std::ctstring_t db = _data.db;

	Options data = _data;
	data.db = {};

	Connection conn;
	conn.connect(data);
	conn.query(xT("CREATE DATABASE IF NOT EXISTS `%s` CHARACTER SET utf8"), db.c_str());
}
//-------------------------------------------------------------------------------------------------
void_t
Db::drop()
{
	Options data = _data;
	data.db = {};

	Connection conn;
	conn.connect(data);
	conn.query(xT("DROP DATABASE IF EXISTS `%s`"), _data.db.c_str());
}
//-------------------------------------------------------------------------------------------------

} // namespace
