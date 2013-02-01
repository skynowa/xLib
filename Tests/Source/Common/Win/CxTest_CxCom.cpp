/**
 * \file   CxTest_CxCom.cpp
 * \brief
 */


#include <Test/Common/Win/CxTest_CxCom.h>


//---------------------------------------------------------------------------
CxTest_CxCom::CxTest_CxCom() {

}
//---------------------------------------------------------------------------
CxTest_CxCom::~CxTest_CxCom() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxCom::unit(
    const ulonglong_t &cullCaseLoops
)
{
#if xOS_ENV_WIN

    xTEST_CASE("CxCom::CxCom", cullCaseLoops)
    {
        const COINIT ccmModel[] = {
            COINIT_APARTMENTTHREADED,
            COINIT_MULTITHREADED,
            COINIT_DISABLE_OLE1DDE,
            COINIT_SPEED_OVER_MEMORY
        };

        for (size_t i = 0; i < xARRAY_SIZE(ccmModel) - 1; ++ i) {
            CxCom cmCom1(ccmModel[i]);
            CxCom cmCom2(ccmModel[i]);
            CxCom cmCom3(ccmModel[i]);
        }
    }

#endif
}
//---------------------------------------------------------------------------
