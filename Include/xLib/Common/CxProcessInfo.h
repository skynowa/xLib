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
class CxProcessInfo :
    public CxNonCopyable
{
	public:
        static ulong_t        ulGetCpuUsage(const CxProcess::TxId cidId);
            ///< get CPU usage (percentage)
        static ulong_t        ulGetRamUsage(const CxProcess::TxId cidId);
            ///< get RAM usage (percentage)
        static ulong_t        ulGetIOBytes (const CxProcess::TxId cidId);
            ///< get total read and written bytes
        static std::tstring_t sGetExeName  (const CxProcess::TxId cidId);
            ///< get exe name
        static ulong_t        ulGetParentId(const CxProcess::TxId cidId);
            ///< get parent process id

    private:
    			              CxProcessInfo();
            ///< constructor
		virtual              ~CxProcessInfo();
		    ///< destructor

};
//---------------------------------------------------------------------------
#endif //xLib_CxProcessInfoH
