/****************************************************************************
* Class name:  CxTest
* Description: code testing
* File name:   CxTest.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 9:29:52
*
*****************************************************************************/


#include <xLib/Debug/CxTest.h>

#include <xLib/Common/CxException.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxEnvironment.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxTest
CxTest::CxTest() :
    m_pvRes        (NULL),
    m_chRes        (0),
    m_blRes        (false),
    m_bRes         (FALSE),
    m_iRes         (- 1),
    m_siRes        (0),
    m_usiRes       (0),
    m_uiRes        (0),
    m_liRes        (0L),
    m_ulRes        (0),
    m_llRes        (0LL),
    m_ullRes       (0UL),
    m_fRes         (0.0f),
    m_dRes         (0.0f),
    m_sRes         (),
    m_usRes        (),
    m_vecsRes      (),
    m_mapsRes      (),
#if defined(xOS_WIN)
    m_hRes         (INVALID_HANDLE_VALUE),
    m_hwndRes      (NULL),
#endif
    _m_bRes        (FALSE),
    _m_sWorkDirPath(),
    _m_sName       ()
{
    _m_bRes = bCreateWorkDir(xT("Temp for tests"));
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest
/*virtual*/
CxTest::~CxTest() /* = 0*/ {
    _m_bRes = CxDir::bDeleteForce( sGetWorkDirPath() );
    /*DEBUG*/xASSERT_DO(FALSE != _m_bRes, return);
}
//---------------------------------------------------------------------------
//DONE: bRun (run in some loops)
BOOL
CxTest::bRun(
    const ULONGLONG cullLoops
)
{
    /*DEBUG*/

    //xTRACEV("Test (%s) begin.", sGetName().c_str());

    const ULONGLONG cullInfiniteLoops = 0;

    try {
        tString sStr;   sStr.at(0);

        //throw CxException() << "xxxxxx";

        if (cullInfiniteLoops == cullLoops) {
            //infinite
            for ( ;  ; ) {
                _m_bRes = bUnit();
                /*DEBUG*/xASSERT_MSG_RET(FALSE != _m_bRes, sGetName() + xT(": fail"), FALSE);
            }
        } else {
            //in some loops
            for (ULONGLONG i = 0; i < cullLoops; ++ i) {
                _m_bRes = bUnit();
                /*DEBUG*/xASSERT_MSG_RET(FALSE != _m_bRes, sGetName() + xT(": fail"), FALSE);
            }
        }
    }
    catch (const std::exception &cexException) {
        std::string asRes = cexException.what();

        tString sMsg = tString(asRes.begin(), asRes.end());

        /*DEBUG*/xASSERT_MSG_RET(FALSE, sGetName() + xT(": ") + sMsg, FALSE);
    }
//    catch (const CxException &cexException) {
//        std::string asRes = cexException.what();
//
//        tString sMsg = tString(asRes.begin(), asRes.end());
//
//        /*DEBUG*/xASSERT_MSG_RET(FALSE, sGetName() + xT(": ") + sMsg, FALSE);
//    }
    catch (...) {
        /*DEBUG*/xASSERT_MSG_RET(FALSE, sGetName() + xT(": Unknown test error"), FALSE);
    }

    //xTRACEV("Test (%s) end.\n", sGetName().c_str());

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bUnit (unit)
/*virtual*/
BOOL
CxTest::bUnit() /*= 0*/  {
    /*DEBUG*/// n/a

    #if xTEMP_DISABLED
        //-------------------------------------
        //[FUNCTION_NAME]
        {
            const tString sTestData[][2] = {
                {xT("TEST_STRING_1"),         xT("MUST_BE_1")},
                {xT("TEST_STRING_2"),         xT("MUST_BE_2")},
                {xT("TEST_STRING_3"),         xT("MUST_BE_3")},
                {xT("TEST_STRING_4"),         xT("MUST_BE_4")}
            };

            for (std::size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
                tString sStr1 = [FUNCTION_NAME](sTestData[i][0]);
                tString sStr2 = [FUNCTION_NAME](sTestData[i][1]);
                xASSERT_EQUAL(sStr1 == sStr2);

                tString sStr3 = [FUNCTION_NAME](sTestData[i][0]);
                tString sStr4 = sTestData[i][1];
                xASSERT_EQUAL(sStr3 == sStr4);
            }
        }
    #endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bCreateWorkDir (create work dir)
BOOL
CxTest::bCreateWorkDir(
    const tString &csDirName
)
{
    /*DEBUG*/// n/a

    if (true == csDirName.empty()) {
        _m_sWorkDirPath = CxEnvironment::sGetVar(xT("tmp"));    //tmp - linux (printenv), temp - windows
    } else {
        _m_sWorkDirPath = CxPath::sGetExeDir() + CxConst::xSLASH + csDirName;

        _m_bRes = CxDir::bCreateForce(_m_sWorkDirPath);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetWorkDirPath (get work dir path)
tString
CxTest::sGetWorkDirPath() {
    /*DEBUG*/xASSERT(false == _m_sWorkDirPath.empty());

    return _m_sWorkDirPath;
}
//---------------------------------------------------------------------------
//DONE: sGetName ()
tString
CxTest::sGetName() {
    /*DEBUG*/

    return _m_sName;
}
//---------------------------------------------------------------------------
//DONE: bSetName ()
BOOL
CxTest::bSetName(
    const tString &csTestName
)
{
    /*DEBUG*/

    _m_sName = csTestName;

    return TRUE;
}
//---------------------------------------------------------------------------
