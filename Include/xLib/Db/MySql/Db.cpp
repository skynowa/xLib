/**
 * \file  Db.cpp
 * \brief Database
 */


#include "Db.h"

#include <xLib/Core/Format.h>
#include <xLib/System/User.h>


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
	xTEST_NA(a_sqlLike);
	xTEST_PTR(out_dbNames);

	out_dbNames->clear();

    // Connection
    Connection conn(_options);
	conn.connect();

	// Query
	std::tstring_t sql = xT("SHOW DATABASES");
	if ( !a_sqlLike.empty() ) {
		sql += Format::str(xT(" LIKE {}"), EscapeQuoted(conn, a_sqlLike).forSqm());
	}

	// Result
	{
		StoreResult result = conn.query(sql).store();

		rows_t rows;
		result.fetchRows(&rows);

		// [out]
		for (const auto &it_row : rows) {
			xTEST_EQ(it_row.size(), static_cast<std::size_t>(1));

			const auto &value = it_row.begin()->second;

			out_dbNames->emplace_back(value);
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
    // Connection
    Connection conn(_options);
	conn.connect();

	// Query
	std::ctstring_t sql = Format::str(
		xT("SELECT count(*) as dbCount FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME = {}"),
		EscapeQuoted(conn, _options.db).forSqm());

	// Result
	{
		StoreResult result = conn.query(sql).store();

		rows_t rows;
		result.fetchRows(&rows);

		xTEST_EQ(rows.size(), static_cast<size_t>(1));
		xCHECK_RET(rows[0]["dbCount"] == xT("0"), false);

		xTEST_EQ(rows[0]["dbCount"], "1");
	}

    return true;
}
//-------------------------------------------------------------------------------------------------
/**
 * \warning Only admin rights
 */
void_t
Db::create() const
{
	if ( !User().isAdmin() ) {
		xTEST_FAIL_MSG(xT("Only admin rights. Stop"));
		return;
	}

	std::ctstring_t db = _options.db;

	Options options = _options;
	options.db = {};

	// Connection
	Connection conn(options);
	conn.connect();

	// Query
	std::ctstring_t sql = Format::str(xT("CREATE DATABASE IF NOT EXISTS {} CHARACTER SET {}"),
		db,
		EscapeQuoted(conn, _options.charset).forSqm());

	conn.query(sql).exec();
}
//-------------------------------------------------------------------------------------------------
/**
 * \warning Only admin rights
 */
void_t
Db::drop() const
{
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
