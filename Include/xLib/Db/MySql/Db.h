/**
 * \file  Db.h
 * \brief MySql DB
 */


#pragma once

#include <xLib/Db/MySql/Common.h>
//-------------------------------------------------------------------------------------------------
namespace xl::db::mysql
{

class Db
    /// MySql DB
{
public:
///@name ctors, dtor
///@{
			 Db(cOptions &options);
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
	cOptions _options; ///< Db data
};

} // namespace
//-------------------------------------------------------------------------------------------------
