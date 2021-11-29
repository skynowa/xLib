/**
 * \file  MySqlDatabase.cpp
 * \brief MySql DB
 */


#include "MySqlDatabase.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/Format.h>

#include <xLib/Db/MySql/MySqlRecordset.h>


namespace xl::db
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
MySqlDatabase::MySqlDatabase(
	cMySqlConnectionData &a_data
) :
	_data{a_data}
{
}
//-------------------------------------------------------------------------------------------------
bool_t
MySqlDatabase::isExists()
{
    bool_t bRv {};

    MySqlConnectionData data = _data;
    data.db = {};

    MySqlConnection conn;
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
        MySqlRecordset rec(conn, false);

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
MySqlDatabase::create()
{
	std::ctstring_t db = _data.db;

	MySqlConnectionData data = _data;
	data.db = {};

	MySqlConnection conn;
	conn.connect(data);
	conn.query(xT("CREATE DATABASE IF NOT EXISTS `%s` CHARACTER SET utf8"), db.c_str());
}
//-------------------------------------------------------------------------------------------------
void_t
MySqlDatabase::drop()
{
	MySqlConnectionData data = _data;
	data.db = {};

	MySqlConnection conn;
	conn.connect(data);
	conn.query(xT("DROP DATABASE IF EXISTS `%s`"), _data.db.c_str());
}
//-------------------------------------------------------------------------------------------------

} // namespace
