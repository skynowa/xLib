/**
 * \file   CxCurrentProcess.h
 * \brief
 */


#ifndef xLib_Sync_CxCurrentProcessH
#define xLib_Sync_CxCurrentProcessH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Sync/CxProcess.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxCurrentProcess :
    private CxNonCopyable
{
public:
    static bool_t                isCurrent      (const CxProcess::id_t &culId) xWARN_UNUSED_RV;
        ///< is current id
    static CxProcess::id_t     id              () xWARN_UNUSED_RV;
        ///< process ID of the calling process
    static CxProcess::id_t     parentId        () xWARN_UNUSED_RV;
        ///< process ID of the parent of the calling process
    static CxProcess::handle_t handle          () xWARN_UNUSED_RV;
        ///< get pseudo handle for the calling process
    static void                exit            (cuint_t &cuiExitCode);
        ///< ends the calling process and all its threads

private:
                               CxCurrentProcess();
        ///< constructor
    virtual                   ~CxCurrentProcess();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Sync_CxCurrentProcessH
