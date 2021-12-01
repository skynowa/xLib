/**
 * \file  Db.h
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
#include <xLib/Db/MySql/Options.h>
//-------------------------------------------------------------------------------------------------
namespace xl::db::mysql
{

class Db
    /// MySql DB
{
public:
///@name ctors, dtor
///@{
			 Db(cOptions &data);
	virtual ~Db() = default;

	xNO_COPY_ASSIGN(Db)
///@}

	bool_t isExists();
		///< check connection
	void_t create();
		///< create DB
	void_t drop();
		///< drop DB

private:
	cOptions _data; ///< Db data
};

} // namespace
//-------------------------------------------------------------------------------------------------
