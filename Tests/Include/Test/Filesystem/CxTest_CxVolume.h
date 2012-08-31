/**
 * \file   CxTest_CxVolume.h
 * \brief
 */


#ifndef CxTest_CxVolumeH
#define CxTest_CxVolumeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxVolume.h>
//---------------------------------------------------------------------------
class CxTest_CxVolume :
    public CxTest
{
    public:
                     CxTest_CxVolume();
        virtual     ~CxTest_CxVolume();

        virtual bool bUnit(const ulonglong_t cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxVolumeH
