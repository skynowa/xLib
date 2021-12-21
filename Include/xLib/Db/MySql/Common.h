/**
 * \file  Common.h
 * \brief MySql client
 *
 * https://dev.mysql.com/doc/c-api/5.7/en/
 * https://dev.mysql.com/doc/c-api/5.7/en/c-api-basic-function-reference.html
 *
 * \see MySQL libraries:
 * - https://github.com/mysql/mysql-connector-cpp
 * - https://tangentsoft.com/mysqlpp/
 * - https://libtabula.org/
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
#include <xLib/Interface/ILastError.h>

#if xENV_WIN
	#include <mysql.h>
	#include <errmsg.h>
	#include <mysqld_error.h>
#else
	#include <mysql/mysql.h>
	#include <mysql/errmsg.h>
	#include <mysql/mysqld_error.h>
#endif

#include <xLib/Db/MySql/Types.h>
#include <xLib/Db/MySql/Error.h>
#include <xLib/Db/MySql/Options.h>
#include <xLib/Db/MySql/Connection.h>
#include <xLib/Db/MySql/Query.h>
// #include <xLib/Db/MySql/IResult.h>
// #include <xLib/Db/MySql/StoreResult.h>
// #include <xLib/Db/MySql/UseResult.h>
#include <xLib/Db/MySql/Db.h>
//-------------------------------------------------------------------------------------------------
namespace xl::db::mysql
{

std::ctstring_t nullStr {xT("NULL")};
	///< "NULL" string constant

}
//-------------------------------------------------------------------------------------------------
/**
 * TODO:
 *
 * - Info
 * + Options
 * + Db
 * 	- mysql_create_db()
 * 	- mysql_drop_db()
 * 	- mysql_list_dbs()
 * 	- mysql_select_db()
 *
 * + Connection
 * + Query / RealQuery
 * + UseResult / StoreResult
 * - Row
 * - Field
 * - Exception
 * + Error
 */
//-------------------------------------------------------------------------------------------------
