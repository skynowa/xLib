/**
 * \file  CxSharedMemory.h
 * \brief share memory
 */


#ifndef xLib_Sync_CxSharedMemoryH
#define xLib_Sync_CxSharedMemoryH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxSharedMemory :
    public CxNonCopyable
{
    public:
                 CxSharedMemory();
        virtual ~CxSharedMemory();

    private:
};
//---------------------------------------------------------------------------
#endif //CxSharedMemoryH
