/**
 * \file  CxSharedMemory.h
 * \brief share memory
 */


#ifndef xLib_Sync_CxSharedMemoryH
#define xLib_Sync_CxSharedMemoryH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxSharedMemory :
    public CxNonCopyable
    /// share memory
{
    public:
                 CxSharedMemory();
        virtual ~CxSharedMemory();

    private:

};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //CxSharedMemoryH
