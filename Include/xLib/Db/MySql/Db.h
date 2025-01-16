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
///\name ctors, dtor
///\{
	explicit  Db(const Options &options);
	virtual  ~Db() = default;

	xNO_DEFAULT_CONSTRUCT(Db);
	xNO_COPY_ASSIGN(Db);
///\}

	void_t show(std::ctstring_t &sqlLike, std::vec_tstring_t *dbNames) const;
		///< list DB names
	void_t show(std::vec_tstring_t *dbNames) const;
		///< list DB names
	bool_t isExists() const;
		///< check connection
	void_t create() const;
		///< create DB
	void_t drop() const;
		///< drop DB

private:
	const Options &_options; ///< Db data
};

} // namespace
//-------------------------------------------------------------------------------------------------
