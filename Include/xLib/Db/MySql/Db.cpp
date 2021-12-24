/**
 * \file  Db.cpp
 * \brief Database
 */


#include "Db.h"

#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Core/FormatC.h>
#include <xLib/Core/Format.h>
#include <xLib/System/User.h>

#include <xLib/Db/MySql/Result.h>

namespace xl::db::mysql
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
Db::Db(
	const Options &a_options
) :
	_options{a_options}
{
}
//-------------------------------------------------------------------------------------------------
void_t
Db::show(
	std::ctstring_t    &a_sqlLike,	///< simple regular expression (SQL LIKE)
	std::vec_tstring_t *out_dbNames	///< [out]
) const
{
	xTESTS_NA(a_sqlLike);
	xTEST_PTR(out_dbNames);

	out_dbNames->clear();

    bool_t bRv {};

    // Connection
    Connection conn(_options);
	{
		bRv = conn.get().isValid();
		xCHECK_DO(!bRv, return);

		conn.connect();
	}

	// Query
	std::ctstring_t &sql = a_sqlLike.empty() ?
		xT("SHOW DATABASES") :
		Format::str(xT("SHOW DATABASES LIKE '{}'"), a_sqlLike);

	// Result
	{
		StoreResult result = conn.query(sql).store();

		rows_t rows;
		result.fetchRows(&rows);

		// [out]
		for (const auto &it_row : rows) {
			out_dbNames->push_back(it_row[0]);
		}
	}
}
//-------------------------------------------------------------------------------------------------
void_t
Db::show(
	std::vec_tstring_t *out_dbNames	///< [out]
) const
{
	std::ctstring_t wildcard;

	return show(wildcard, out_dbNames);
}
//-------------------------------------------------------------------------------------------------
/**
 * \see https://stackoverflow.com/questions/275314/mysql-row-and-row0-to-string-type
 */
bool_t
Db::isExists() const
{
    bool_t bRv {};

    Connection conn(_options);
	bRv = conn.get().isValid();
	xCHECK_RET(!bRv, false);

	conn.connect();

	std::ctstring_t sql = Format::str(
		xT("SELECT count(*) FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = {}"),
		EscapeQuoted(conn, _options.db).forSqm());

	StoreResult result = conn.query(sql).store();

	rows_t rows;
	result.fetchRows(&rows);
	xTEST_EQ(rows.size(), static_cast<size_t>(1));
	xCHECK_RET(rows[0][0] == xT("0"), false);

	xTEST_EQ(rows[0][0], "1");

    return true;
}
//-------------------------------------------------------------------------------------------------
void_t
Db::create() const
{
   /**
	* \warning Only admin rights
	*/
	if ( !User().isAdmin() ) {
		xTEST_FAIL_MSG(xT("Only admin rights. Stop"));
		return;
	}

	std::ctstring_t db = _options.db;

	Options options = _options;
	options.db = {};

	Connection conn(options);
	conn.connect();

	std::ctstring_t sql = Format::str(xT("CREATE DATABASE IF NOT EXISTS `{}` CHARACTER SET {}"),
		db,
		EscapeQuoted(conn, _options.charset).forSqm());

	conn.query(sql).exec();
}
//-------------------------------------------------------------------------------------------------
void_t
Db::drop() const
{
   /**
	* \warning Only admin rights
	*/
	if ( !User().isAdmin() ) {
		xTEST_FAIL_MSG(xT("Only admin rights. Stop"));
		return;
	}

	Options options = _options;
	options.db = {};

	Connection conn(options);
	conn.connect();

	std::ctstring_t sql = Format::str(xT("DROP DATABASE IF EXISTS `{}`"),
		EscapeQuoted(conn, _options.db).forSqm());

	conn.query(sql).exec();
}
//-------------------------------------------------------------------------------------------------

} // namespace
