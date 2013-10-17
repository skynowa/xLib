/**
 * \file  CxTcpClient.h
 * \brief client socket
 */


#pragma once

#include <xLib/Net/CxSocket.h>
#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxTcpClient :
    public CxSocket
    /// client socket
{
public:
                  CxTcpClient();
        ///< constructor
    virtual      ~CxTcpClient();
        ///< constructor

    bool_t        isReadable() xWARN_UNUSED_RV;
        ///< checking for readability
    bool_t        isWritable() xWARN_UNUSED_RV;
        ///< checking for writability
    void_t        connect(std::ctstring_t &ip, cushort_t &port);
        ///< connecting

    void_t        ioctl(clong_t &command, ulong_t *args);
        ///< controls the i/o mode
    void_t        setNonBlockingMode(cbool_t &flag);
        ///< set nonblocking mode
    void_t        timeout(long_t *seconds, long_t *microsec);
        ///< get timeout
    void_t        setTimeout(clong_t &seconds, clong_t &microsec);
        ///< set timeout

    static bool_t isServerAlive(std::ctstring_t &ip, cushort_t &port) xWARN_UNUSED_RV;
        ///< is sever socket available

protected:
    timeval       _timeout;    ///< timeout
};

//TODO: bIsWritable repeats from CxSocket
//TODO: bIsReadable repeats from CxSocket

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <Net/CxTcpClient.cpp>
#endif


/*
Client

Initialize Winsock.
Create a socket.
Connect to the server.
Send and receive data.
Disconnect.
*/

