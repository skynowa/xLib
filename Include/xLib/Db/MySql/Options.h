/**
 * \file  Options.h
 * \brief Connection options
 */


#pragma once

#include <xLib/Db/MySql/Common.h>
//-------------------------------------------------------------------------------------------------
namespace xl::db::mysql
{

class Options
{
public:
///@name ctors, dtor
///@{
	Options() = default;
   ~Options() = default;
///@}

    std::tstring_t host;
        ///< host name or an IP address.
        ///< If host is empty (NULL or the empty string "") or the string "localhost",
        ///< a connection to the local host is assumed
    std::tstring_t user;
        ///< MySQL login ID. If user is empty string, the current user is assumed
    std::tstring_t password;
        ///< password
    std::tstring_t db;
        ///< DB name
    uint_t         port {};
        ///< If port is not 0, the value is used as the port number for the TCP/IP connection
    std::tstring_t unixSocket;
        ///< If unix_socket is not empty, the string specifies the socket or named pipe to use
    std::tstring_t charset;
        ///< specifies character name
    bool_t         isAutoCommit {};
        ///< sets autocommit mode on
    bool_t         isCompress {};
        ///< Use compression in the client/server protocol
    std::map<mysql_option, cptr_cvoid_t> options;
        ///< extra options
};

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * TODO:
 *
 * - IOptions (fromConfig(), ...)
 */
//-------------------------------------------------------------------------------------------------
