/**
 * \file   CxTest_CxGeoIp.h
 * \brief
 */


#ifndef CxTest_CxGeoIpH
#define CxTest_CxGeoIpH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Net/CxGeoIp.h>
//---------------------------------------------------------------------------
class CxTest_CxGeoIp :
    public CxTest
{
    public:
                 CxTest_CxGeoIp();
        virtual ~CxTest_CxGeoIp();

        virtual  bool bUnit(const ULONGLONG cullBlockLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxGeoIpH
