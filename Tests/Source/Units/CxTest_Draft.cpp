/**
 * \file   CxTest_Draft.cpp
 * \brief  draft for tests
 */


#include <Test/Units/CxTest_Draft.h>


//---------------------------------------------------------------------------
CxTest_Draft::CxTest_Draft() {

}
//---------------------------------------------------------------------------
CxTest_Draft::~CxTest_Draft() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_Draft::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    #if xTEMP_DISABLED
        {
            int iTest = - 2;

            xTRACEV("(i =  %i): %i", iTest, iTest);
            xTRACEV("(i = !%i): %i", iTest, !iTest);
        }
    #endif

    #if xTEMP_DISABLED
        {
            int iMin = CxThread::_iGetPriorityMin();
            int iMax = CxThread::_iGetPriorityMax();

            xTRACEV("Tnread prior: %i ... %i", iMin, iMax);
        }
    #endif

    //--------------------------------------------------
    //std::tstring::operator=, std::tstring::assign, std::swap
    #if xTEMP_DISABLED
        xTEST_CASE(cullBlockLoops)
        {
            const size_t cuiLoops = 1000000000;
            std::tstring csStr    = xT("qwertyuiop[]asdfghjkl;'zxcvbnm,.1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,.1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,.1234567890-=");
            std::tstring sRes     = xT(" qwertyuiop[]asdfghjkl;'zxcvbnm,.1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,.1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,.1234567890-= ");

            {
                xAUTO_PROFILER(xT("./__std_tstring.profile"), CxProfiler::pmStdClock, xT("%s"), xT("std::tstring::operator="));

                for (size_t i = 0; i < cuiLoops; ++ i) {
                    sRes = csStr;
                }
            }

            xTRACE(sRes.c_str());

            {
                xAUTO_PROFILER(xT("./__std_tstring.profile"), CxProfiler::pmStdClock, xT("%s"), xT("std::tstring::assign"));

                for (size_t i = 0; i < cuiLoops; ++ i) {
                    sRes.assign(csStr);
                }
            }

            xTRACE(sRes.c_str());

           {
                xAUTO_PROFILER(xT("./__std_tstring.profile"), CxProfiler::pmStdClock, xT("%s"), xT("std::tstring::swap"));

                for (size_t i = 0; i < cuiLoops; ++ i) {
                    sRes.swap(csStr);
                }
            }

            xTRACE(sRes.c_str());
        }
    #endif

    #if 0
        xASSERT(false);
    #endif

    return true;
}
//---------------------------------------------------------------------------
