/**
 * \file  Db.cpp
 * \brief MySql DB
 */


#include "Db.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/Format.h>

#include <xLib/Db/MySql/StoreResult.h>

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
Db::isExists() const
{
    bool_t bRv {};

    Connection conn(_options);
    {
        bRv = conn.get().isValid();
        xCHECK_RET(!bRv, false);

        conn.connect();

        std::tstring_t sql = Format::str(
            xT("SELECT count(*) FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = '{}'"),
			_options.db);

        Query query(conn);
        query.exec(sql);
    }

    {
        StoreResult result(conn);

        bRv = result.get().isValid();
        xTEST(bRv);
        xTEST_EQ(result.rows(), uint64_t(1));

        std::vector<std::vec_tstring_t> rows;
        result.fetchRows(&rows);
        xTEST_EQ(rows.size(), static_cast<size_t>(1));
        xCHECK_RET(rows[0][0] == xT("0"), false);

        xTEST_EQ(rows[0][0], "1");
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
void_t
Db::create() const
{
	std::ctstring_t db = _options.db;

	Options options = _options;
	options.db = {};

	Connection conn(options);
	conn.connect();

	Query query(conn);
	query.exec( Format::str(xT("CREATE DATABASE IF NOT EXISTS `{}` CHARACTER SET utf8"), db) );
}
//-------------------------------------------------------------------------------------------------
void_t
Db::drop() const
{
	Options options = _options;
	options.db = {};

	Connection conn(options);
	conn.connect();

	Query query(conn);
	query.exec( Format::str(xT("DROP DATABASE IF EXISTS `{}`"), _options.db) );
}
//-------------------------------------------------------------------------------------------------

} // namespace
