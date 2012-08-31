/**
 * \file   CxProcessInfo.h
 * \brief
 */


#ifndef xLib_CxProcessInfoH
#define xLib_CxProcessInfoH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxProcess.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxProcessInfo :
    public CxNonCopyable
{
    public:
        static ulong_t        ulGetCpuUsage(const CxProcess::id_t &cidId);
            ///< get CPU usage (percentage)
        static ulong_t        ulGetRamUsage(const CxProcess::id_t &cidId);
            ///< get RAM usage (percentage)
        static ulong_t        ulGetIOBytes (const CxProcess::id_t &cidId);
            ///< get total read and written bytes
        static std::tstring_t sGetExeName  (const CxProcess::id_t &cidId);
            ///< get exe name
        static ulong_t        ulGetParentId(const CxProcess::id_t &cidId);
            ///< get parent process id

    private:
                              CxProcessInfo();
            ///< constructor
        virtual              ~CxProcessInfo();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_CxProcessInfoH
