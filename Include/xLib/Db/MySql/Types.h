/**
 * \file  Types.h
 * \brief
 */


#pragma once

#if xENV_WIN
	#include <mysql.h>
	#include <errmsg.h>
	#include <mysqld_error.h>
#else
	#include <mysql/mysql.h>
	#include <mysql/errmsg.h>
	#include <mysql/mysqld_error.h>
#endif
//-------------------------------------------------------------------------------------------------
namespace xl::db::mysql
{

using row_t  = std::vec_tstring_t;
using rows_t = std::vector<std::vec_tstring_t>;

} // namespace
//-------------------------------------------------------------------------------------------------
