/**
 * \file   CxTest_CxPath.h
 * \brief
 */


#ifndef CxTest_CxPathH
#define CxTest_CxPathH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/CxPath.h>
//---------------------------------------------------------------------------
class CxTest_CxPath :
    public CxTest
{
    public:
                     CxTest_CxPath();
        virtual     ~CxTest_CxPath();

        virtual bool bUnit(const ulonglong_t cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxPathH
