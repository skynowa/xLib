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
    static void_t         currentIds(std::vector<CxProcess::id_t> *ids);
        ///< get all IDs of current processes
    static ulong_t        cpuUsage(const CxProcess::id_t &id) xWARN_UNUSED_RV;
        ///< get CPU usage (percentage)
    static ulong_t        ramUsage(const CxProcess::id_t &id) xWARN_UNUSED_RV;
        ///< get RAM usage (percentage)
    static ulong_t        ioBytes(const CxProcess::id_t &id) xWARN_UNUSED_RV;
        ///< get total read and written bytes
    static std::tstring_t exeName(const CxProcess::id_t &id) xWARN_UNUSED_RV;
        ///< get exe name
    static ulong_t        parentId(const CxProcess::id_t &id) xWARN_UNUSED_RV;
        ///< get parent process id
    static std::tstring_t commandLine(const CxProcess::id_t &id) xWARN_UNUSED_RV;
        ///< get arguments

private:
                          CxProcessInfo();
        ///< constructor
    virtual              ~CxProcessInfo();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <System/CxProcessInfo.cpp>
#endif
