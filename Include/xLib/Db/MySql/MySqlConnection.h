/**
 * \file  MySql.h
 * \brief MySql client
 */


#pragma once

#include <mysql/mysql.h>
#include <mysql/errmsg.h>
#include <mysql/mysqld_error.h>

#include <xLib/Core/Core.h>
#include <xLib/Core/Handle.h>
#include <xLib/Interface/ILastError.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, db)

struct MySqlConnectionData
    /// MySqlConnection data
{
    std::tstring_t host;
    std::tstring_t user;
    std::tstring_t password;
    std::tstring_t db;
    uint_t         port {};
    std::tstring_t unixSocket;
    ulong_t        clientFlag {};
};
xTYPEDEF_CONST(MySqlConnectionData);

class MySqlConnection :
	public xl::interface::ILastError<uint_t>
    /// MySql connection
{
public:
                   MySqlConnection();
        ///< constructor
    virtual       ~MySqlConnection();
        ///< destructor

    HandleMySqlConn &get() xWARN_UNUSED_RV;
        ///< get handle
    void_t         setOption(const mysql_option &option, cptr_cvoid_t arg) const;
        ///< set extra connect options and affect behavior
    void_t         setOptions(const std::map<mysql_option, cptr_cvoid_t> &options) const;
        ///< set extra connect options and affect behavior
    bool_t         ping(int_t *errorCode = xPTR_NULL) const xWARN_UNUSED_RV;
        ///< checks whether the connection to the server is working
    static
    bool_t         isExists(cMySqlConnectionData &data) xWARN_UNUSED_RV;
        ///< check connection
    void_t         connect(cMySqlConnectionData &data);
        ///< attempts to establish a connection to a MySql database engine running on host
	std::tstring_t quoted(std::ctstring_t &sql) const xWARN_UNUSED_RV;
		///< creates a legal SQL string for use in an SQL statement:
		///<
		///< Double quotes turn into: \"
		///< single quotes turn into: \'
		///< Single slashes turn into: \\ (double slashes)
		///< Note unescaped: spaces, |, ?, <, >, {, }, :, ~, @, !, (,), `, #, %,,,;, &, - and _, etc

    void_t         query(cptr_ctchar_t sqlFormat, ...) const;
        ///< executes the SQL statement
    uint_t         fieldCount() const xWARN_UNUSED_RV;
        ///< number of columns in a result set
    void_t         close();
        ///< closes a previously opened connection

    // errors
    uint_t         lastError() const xOVERRIDE xWARN_UNUSED_RV;
        ///< error code for the most recently invoked API function that can succeed or fail
    std::tstring_t lastErrorStr() const xOVERRIDE xWARN_UNUSED_RV;
        ///< error message for the most recently invoked API function that failed

private:
    HandleMySqlConn _conn;
        ///< pointer to connection

    xNO_COPY_ASSIGN(MySqlConnection)
};

xNAMESPACE_END2(xl, db)
//-------------------------------------------------------------------------------------------------
