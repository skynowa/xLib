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
    m_uiRes        (0U),
    m_stRes        (0),
    m_liRes        (0L),
    m_ulRes        (0),
    m_llRes        (0LL),
    m_ullRes       (0UL),
    m_fRes         (0.0f),
    m_dRes         (0.0f),
    m_sRes         (),
    m_usRes        (),
    m_vecsRes      (),
    m_msRes        (),
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
    const ULONGLONG cullUnitLoops,
    const ULONGLONG cullBlockLoops
)
{
    /*DEBUG*/

    try {
        for (ULONGLONG i = 0ULL; i < cullUnitLoops; ++ i) {
            _m_bRes = bUnit(cullBlockLoops);
            /*DEBUG*/xASSERT_MSG_RET(FALSE != _m_bRes, sGetName() + xT(": fail"), FALSE);
        }
    }
    catch (const CxException &e) {
        /*DEBUG*/xASSERT_MSG_RET(FALSE, sGetName() + xT(": ") + e.sGetWhat(), FALSE);
    }
    catch (const std::exception &cexE) {
        std::string asMsg = cexE.what();

        /*DEBUG*/xASSERT_MSG_RET(FALSE, sGetName() + xT(": ") + xS2TS(asMsg), FALSE);
    }
    catch (...) {
        /*DEBUG*/xASSERT_MSG_RET(FALSE, sGetName() + xT(": Unknown test error"), FALSE);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bUnit (unit)
/*virtual*/
BOOL
CxTest::bUnit(
    const ULONGLONG cullBlockLoops
) /*= 0*/ 
{
    /*DEBUG*/// n/a

    #if xTODO
        //-------------------------------------
        //[FUNCTION_NAME]
        xTEST_BLOCK(cullBlockLoops)
        {
            const tString casData[][2] = {
                {xT("TEST_STRING_1"), xT("MUST_BE_1")},
                {xT("TEST_STRING_2"), xT("MUST_BE_2")},
                {xT("TEST_STRING_3"), xT("MUST_BE_3")},
                {xT("TEST_STRING_4"), xT("MUST_BE_4")}
            };

            for (size_t i = 0; i < xARRAY_SIZE(casData); ++ i) {

            }
        }
    #endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetWorkDirPath (get work dir path)
const tString &
CxTest::sGetWorkDirPath() const {
    /*DEBUG*/xASSERT(false == _m_sWorkDirPath.empty());

    return _m_sWorkDirPath;
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
        _m_sWorkDirPath = CxDir::sGetTemp();
    } else {
        _m_sWorkDirPath = CxPath::sGetExeDir() + CxConst::xSLASH + csDirName;

        _m_bRes = CxDir::bCreateForce(_m_sWorkDirPath);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetName ()
const tString &
CxTest::sGetName() const {
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
