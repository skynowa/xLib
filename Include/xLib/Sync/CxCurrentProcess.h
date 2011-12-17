/**
 * \file   CxCurrentProcess.h
 * \brief
 */


#ifndef xLib_Sync_CxCurrentProcessH
#define xLib_Sync_CxCurrentProcessH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxProcess.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxCurrentProcess :
    private CxNonCopyable
{
	public:
        static CxProcess::TxId     ulGetId         ();
            ///< process ID of the calling process
        static CxProcess::TxId     ulGetParentId   ();
            ///< process ID of the parent of the calling process
        static CxProcess::TxHandle hGetHandle      ();
            ///< get pseudo handle for the calling process

    private:
				                   CxCurrentProcess();
            ///< constructor
		virtual                   ~CxCurrentProcess();
		    ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Sync_CxCurrentProcessH
