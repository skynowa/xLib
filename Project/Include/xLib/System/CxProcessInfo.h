/**
 * \file   CxProcessInfo.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Sync/CxProcess.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxProcessInfo :
    public CxNonCopyable
{
public:
                    CxProcessInfo() {}
        ///< constructor
    virtual        ~CxProcessInfo() {}
        ///< destructor

    void_t          setProcessId(const CxProcess::id_t &a_id);
        ///< set target process ID
    ulong_t         cpuUsage() xWARN_UNUSED_RV;
        ///< get CPU usage (percentage)
    ulong_t         ramUsage() xWARN_UNUSED_RV;
        ///< get RAM usage (percentage)
    ulong_t         ioBytes() xWARN_UNUSED_RV;
        ///< get total read and written bytes
    std::tstring_t  exeName() xWARN_UNUSED_RV;
        ///< get exe name
    ulong_t         parentId() xWARN_UNUSED_RV;
        ///< get parent process id
    void_t          commandLine(std::vec_tstring_t *args);
        ///< get arguments

    static long_t   commandLineArgsMax() xWARN_UNUSED_RV;
        ///< get maximum length of command line arguments (in chars)
    static void_t   currentIds(std::vector<CxProcess::id_t> *ids);
        ///< get all IDs of current processes
private:
    CxProcess::id_t _id;  ///< target process ID
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <System/CxProcessInfo.cpp>
#endif
