/****************************************************************************
* Class name:  CxTest_CxGeoIp
* Description: test CxGeoIp
* File name:   CxGeoIp.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:
*
*****************************************************************************/


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

	    virtual  BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxGeoIpH
