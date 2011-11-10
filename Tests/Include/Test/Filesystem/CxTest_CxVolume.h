/****************************************************************************
* Class name:  CxTest_CxVolume
* Description: test CxVolume
* File name:   CxTest_CxVolume.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxVolumeH
#define CxTest_CxVolumeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/CxVolume.h>
//---------------------------------------------------------------------------
class CxTest_CxVolume : public CxTest {
    public:
                     CxTest_CxVolume();
        virtual     ~CxTest_CxVolume();

        virtual BOOL bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxVolumeH
