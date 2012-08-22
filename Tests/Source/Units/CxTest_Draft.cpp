/**
 * \file   CxTest_Draft.cpp
 * \brief  draft for tests
 */


#include <Test/Units/CxTest_Draft.h>

#include <xLib/Filesystem/CxFile.h>



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
    const ulonglong_t cullCaseLoops
)
{
    //--------------------------------------------------
    //bool type
    xTEST_CASE(cullCaseLoops)
    {
        #if 0
            bool bVal = false;

            bVal = false;
            xTRACEV(xT("Expr: [bVal = false], bVal = %i"), bVal);

            bVal = true;
            xTRACEV(xT("Expr: [bVal = true],  bVal = %i"), bVal);

            bVal = - 2;
            xTRACEV(xT("Expr: [bVal = - 2],   bVal = %i"), bVal);

            bVal = - 1;
            xTRACEV(xT("Expr: [bVal = - 1],   bVal = %i"), bVal);

            bVal = 0;
            xTRACEV(xT("Expr: [bVal = 0],     bVal = %i"), bVal);

            bVal = 1;
            xTRACEV(xT("Expr: [bVal = 1],     bVal = %i"), bVal);

            bVal = 2;
            xTRACEV(xT("Expr: [bVal = 2],     bVal = %i"), bVal);

            /*
                Expr: [bVal = false], bVal = 0
                Expr: [bVal = true],  bVal = 1
                Expr: [bVal = - 2],   bVal = 1
                Expr: [bVal = - 1],   bVal = 1
                Expr: [bVal = 0],     bVal = 0
                Expr: [bVal = 1],     bVal = 1
                Expr: [bVal = 2],     bVal = 1
            */
        #endif
    }

    //--------------------------------------------------
    //int, not int
    xTEST_CASE(cullCaseLoops)
    {
        #if 0
            int iTest = - 2;

            xTRACEV("Expr: [i =  %i]: %i", iTest, iTest);
            xTRACEV("Expr: [i = !%i]: %i", iTest, !iTest);

            /*
                Expr: [i =  -2]: -2
                Expr: [i = !-2]: 0
            */
        #endif
    }

    //--------------------------------------------------
    //CxThread priority
    xTEST_CASE(cullCaseLoops)
    {
        #if 0
            int iMin = CxThread::_iGetPriorityMin();
            int iMax = CxThread::_iGetPriorityMax();

            xTRACEV("Tnread prior: %i ... %i", iMin, iMax);
        #endif
    }

    //--------------------------------------------------
    //std::tstring_t::operator=, std::tstring_t::assign, std::swap
    xTEST_CASE(1)
    {
        #if 0
            const size_t   cuiLoops = 1000000000;
            std::tstring_t csStr    = xT("qwertyuiop[]asdfghjkl;'zxcvbnm,.1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,.1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,.1234567890-=");
            std::tstring_t sRv     = xT(" qwertyuiop[]asdfghjkl;'zxcvbnm,.1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,.1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,.1234567890-= ");

            {
                xAUTO_PROFILER(xT("./__std_tstring.profile"), CxProfiler::pmStdClock, xT("%s"), xT("std::tstring_t::operator="));

                for (size_t i = 0; i < cuiLoops; ++ i) {
                    sRv = csStr;
                }
            }

            xTRACE(sRv);

            {
                xAUTO_PROFILER(xT("./__std_tstring.profile"), CxProfiler::pmStdClock, xT("%s"), xT("std::tstring_t::assign"));

                for (size_t i = 0; i < cuiLoops; ++ i) {
                    sRv.assign(csStr);
                }
            }

            xTRACE(sRv);

            {
                xAUTO_PROFILER(xT("./__std_tstring.profile"), CxProfiler::pmStdClock, xT("%s"), xT("std::tstring_t::swap"));

                for (size_t i = 0; i < cuiLoops; ++ i) {
                    sRv.swap(csStr);
                }
            }

            xTRACE(sRv);
        #endif
    }

    //--------------------------------------------------
    //xASSERT
    xTEST_CASE(1)
    {
        #if 0
            xASSERT(false);
        #endif
    }

    //--------------------------------------------------
    //bAccess
    xTEST_CASE(cullCaseLoops)
    {
    #if 0
        m_bRv = CxFile::bAccess(xT("G:"), CxFile::amWrite);
        xTEST_EQ(false, m_bRv);
    #endif
    }

    return true;
}
//---------------------------------------------------------------------------
