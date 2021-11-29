/**
 * \file  MySqlDatabase.h
 * \brief MySql DB
 */


#pragma once

#include <xLib/Core/Core.h>

#if xENV_WIN
	#include <mysql.h>
	#include <errmsg.h>
	#include <mysqld_error.h>
#else
	#include <mysql/mysql.h>
	#include <mysql/errmsg.h>
	#include <mysql/mysqld_error.h>
#endif

#include <xLib/Core/Handle.h>
#include <xLib/Db/MySql/MySqlConnection.h>
//-------------------------------------------------------------------------------------------------
namespace xl::db
{

class MySqlDatabase
    /// MySql DB
{
public:
///@name ctors, dtor
///@{
			 MySqlDatabase(cMySqlConnectionData &data);
	virtual ~MySqlDatabase() = default;

	xNO_COPY_ASSIGN(MySqlDatabase)
///@}

	bool_t isExists();
		///< check connection
	void_t create();
		///< create DB
	void_t drop();
		///< drop DB

private:
	cMySqlConnectionData _data; ///< MySqlDatabase data
};

} // namespace
//-------------------------------------------------------------------------------------------------
