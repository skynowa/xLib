/****************************************************************************
* Class name:  CxSharedMemory
* Description: share memory
* File name:   CxSharedMemory.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     15.02.2011 21:44:10
*
*****************************************************************************/


#ifndef xLib_Sync_CxSharedMemoryH
#define xLib_Sync_CxSharedMemoryH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
class CxSharedMemory :
    public CxNonCopyable
{
    public:
                 CxSharedMemory();
        virtual ~CxSharedMemory();

    private:
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif //CxSharedMemoryH
