/**
 * \file   CxTest_CxVolume.h
 * \brief
 */


#ifndef CxTest_CxVolumeH
#define CxTest_CxVolumeH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxVolume.h>
//------------------------------------------------------------------------------
class CxTest_CxVolume :
    public CxTest
{
public:
                 CxTest_CxVolume();
    virtual     ~CxTest_CxVolume();

    virtual void_t unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxVolumeH
