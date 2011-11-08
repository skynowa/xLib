/****************************************************************************
* Class name:  CxTest_CxDir
* Description: testing CxDir
* File name:   CxTest_CxDir.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Filesystem/CxTest_CxDir.h>


//---------------------------------------------------------------------------
CxTest_CxDir::CxTest_CxDir() {

}
//---------------------------------------------------------------------------
CxTest_CxDir::~CxTest_CxDir() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxDir::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    const std::tstring csTempScanDirPath = sGetWorkDirPath() + CxConst::xSLASH + xT("Scan");
    const std::tstring csMask            = xT("*.txt");

#if defined(xOS_ENV_WIN)
    const std::tstring csFilePath		= sGetWorkDirPath() + xT("\\Test.txt");
    const std::tstring csRootTestDirPath = sGetWorkDirPath() + xT("\\Test_Dir");
    const std::tstring csDirPath         = sGetWorkDirPath() + xT("\\Test_Dir\\1\\2\\3");
    const std::tstring csDirPath2		= sGetWorkDirPath() + xT("\\Test_Dir\\1\\2\\3\\4");
    const std::tstring csNewFilePath		= sGetWorkDirPath() + xT("\\New.Test.txt");
    const std::tstring csBakFilePath		= sGetWorkDirPath() + xT("\\Test_Static.txt.bak");
    const std::tstring csFilePathSt		= sGetWorkDirPath() + xT("\\Test_Static.txt");
#elif defined(xOS_ENV_UNIX)
    const std::tstring csFilePath        = sGetWorkDirPath() + xT("/Test.txt");
    const std::tstring csRootTestDirPath = sGetWorkDirPath() + xT("/Test_Dir");
    const std::tstring csDirPath         = sGetWorkDirPath() + xT("/Test_Dir/1/2/3");
    const std::tstring csDirPath2        = sGetWorkDirPath() + xT("/Test_Dir/1/2/3/4");
    const std::tstring csNewFilePath     = sGetWorkDirPath() + xT("/New.Test.txt");
    const std::tstring csBakFilePath     = sGetWorkDirPath() + xT("/Test_Static.txt.bak");
    const std::tstring csFilePathSt      = sGetWorkDirPath() + xT("/Test_Static.txt");
#endif

	/****************************************************************************
	*	prepare
	*
	*****************************************************************************/

	{
		m_bRes = CxDir::bDeleteForce(csRootTestDirPath);
		xASSERT_DIFF(FALSE, m_bRes);

		m_bRes = CxDir::bCreateForce(csDirPath);
		xASSERT_DIFF(FALSE, m_bRes);
	}

	/****************************************************************************
	*	static
	*
	*****************************************************************************/

	//-------------------------------------
	//bCreate
    xTEST_BLOCK(cullBlockLoops)
    {
    	m_bRes = CxDir::bCreate(csDirPath2);
        xASSERT_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bIsDir
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxDir::bIsDir(csDirPath2);
        xASSERT_DIFF(FALSE, m_bRes);
    }

	//-------------------------------------
	//bIsExists
    xTEST_BLOCK(cullBlockLoops)
	{
		m_bRes = CxDir::bIsExists(csDirPath);
		xASSERT_DIFF(FALSE, m_bRes);

		m_bRes = CxDir::bIsExists(xT("y:"));
		xASSERT_EQ(FALSE, m_bRes);

		m_bRes = CxDir::bIsExists(xT("sdfasdf:"));
		xASSERT_EQ(FALSE, m_bRes);

		m_bRes = CxDir::bIsExists(xT("C:\\WINDOWS\\NOTEPAD.EXE"));
		xASSERT_EQ(FALSE, m_bRes);

		m_bRes = CxDir::bIsExists(xT("C:\\pagefile.sys"));
		xASSERT_EQ(FALSE, m_bRes);
	}

	//-------------------------------------
	//bIsEmpty
    xTEST_BLOCK(cullBlockLoops)
	{
		m_bRes = CxDir::bIsEmpty(csDirPath, CxConst::xMASK_ALL);
		xASSERT_EQ(FALSE, m_bRes);

		m_bRes = CxDir::bIsEmpty(csDirPath2, CxConst::xMASK_ALL);
		xASSERT_DIFF(FALSE, m_bRes);

		m_bRes = CxDir::bIsEmpty(sGetWorkDirPath(), CxConst::xMASK_ALL);
		xASSERT_EQ(FALSE, m_bRes);
	}

    //--------------------------------------------------
    //bIsRoot
    xTEST_BLOCK(cullBlockLoops)
    {
        #if defined(xOS_ENV_WIN)
            const std::tstring sTestData[][2] = {
                {xT("TEST_STRING_1"), xT("FALSE")},
                {xT(""),              xT("FALSE")},
                {xT("/"),             xT("FALSE")},
                {xT("\\"),            xT("FALSE")},
                {xT("A:\\"),          xT("TRUE")},
                {xT("D:\\"),          xT("TRUE")},
                {xT("A:/"),           xT("TRUE")},
                {xT("D:/"),           xT("TRUE")},
                {xT("Z::"),           xT("FALSE")},
                {xT("\\\\"),          xT("FALSE")},
                {xT("B:"),            xT("FALSE")},
                {xT("B"),             xT("FALSE")}
            };
        #elif defined(xOS_ENV_UNIX)
            const std::tstring sTestData[][2] = {
                {xT("TEST_STRING_1"), xT("FALSE")},
                {xT(""),              xT("FALSE")},
                {xT("/"),             xT("TRUE")},
                {xT("\\"),            xT("FALSE")},
                {xT("A:"),            xT("FALSE")},
                {xT("D:/"),           xT("FALSE")}
            };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            BOOL bRes1 = CxDir::bIsRoot(sTestData[i][0]);
            BOOL bRes2 = CxString::bStrToBool(sTestData[i][1]);
            xASSERT_EQ(bRes1, bRes2);
        }
    }

	//-------------------------------------
	//bSetCurrent
    xTEST_BLOCK(cullBlockLoops)
    {
		m_sRes = CxDir::sGetCurrent();
		xASSERT_EQ(false, m_sRes.empty());

		m_bRes = CxDir::bSetCurrent( sGetWorkDirPath() );
		xASSERT_DIFF(FALSE, m_bRes);

	    m_bRes = CxDir::bSetCurrent(m_sRes);
		xASSERT_DIFF(FALSE, m_bRes);
	}

	//-------------------------------------
	//sGetCurrent
    xTEST_BLOCK(cullBlockLoops)
	{
		std::tstring sRes = CxDir::sGetCurrent();
		xASSERT_EQ(m_sRes, sRes);
	}

	//-------------------------------------
	//sGetTempPath
    xTEST_BLOCK(cullBlockLoops)
	{
		m_sRes = CxDir::sGetTemp();
        #if xTEST_IGNORE
            xTRACEV(xT("\tCxDir::sGetTemp(): %s"), m_sRes.c_str());
        #endif
        xASSERT_EQ(false, m_sRes.empty());
	}

	//-------------------------------------
	//bCreateForce
    xTEST_BLOCK(cullBlockLoops)
	{
		m_bRes = CxDir::bCreateForce(csDirPath);
		xASSERT_DIFF(FALSE, m_bRes);
	}

	//-------------------------------------
    //bCopy
    xTEST_BLOCK(cullBlockLoops)
    {
        //-------------------------------------
        //prepare for csTempScanDirPath (create dirs)
        const std::tstring csDirSource = sGetWorkDirPath() + CxConst::xSLASH + xT("Source");
        const std::tstring csDirDest   = sGetWorkDirPath() + CxConst::xSLASH + xT("Dest");

        const std::tstring sDirPathes[] =
        {
            csDirSource,
            csDirSource + CxConst::xSLASH + xT("AA"),
            csDirSource + CxConst::xSLASH + xT("AA") + CxConst::xSLASH + xT("AAA")
        };

        for (size_t i = 0; i < xARRAY_SIZE(sDirPathes); ++ i) {
            m_bRes = CxDir::bCreateForce(sDirPathes[i]);
            xASSERT_DIFF(FALSE, m_bRes);
        }

        m_bRes = CxDir::bDeleteForce(csDirDest);
        xASSERT_DIFF(FALSE, m_bRes);

        //-------------------------------------
        //bCopy
        m_bRes = CxDir::bCopy(csDirSource, csDirDest, TRUE);
        xASSERT_DIFF(FALSE, m_bRes);

        m_bRes = CxDir::bDelete(csDirDest);
        xASSERT_DIFF(FALSE, m_bRes);

        m_bRes = CxDir::bCopy(csDirSource, csDirDest, FALSE);
        xASSERT_DIFF(FALSE, m_bRes);

        m_bRes = CxDir::bDeleteForce(csDirDest);
        xASSERT_DIFF(FALSE, m_bRes);

        m_bRes = CxDir::bDeleteForce(csDirSource);
        xASSERT_DIFF(FALSE, m_bRes);
    }

	//-------------------------------------
	//bMove
    xTEST_BLOCK(cullBlockLoops)
	{
        //-------------------------------------
        //prepare for csTempScanDirPath (create dirs)
        const std::tstring csDirSource = sGetWorkDirPath() + CxConst::xSLASH + xT("Source");
        const std::tstring csDirDest   = sGetWorkDirPath() + CxConst::xSLASH + xT("Dest");

        const std::tstring sDirPathes[] =
        {
            csDirSource,
            csDirSource + CxConst::xSLASH + xT("dd"),
            csDirSource + CxConst::xSLASH + xT("XX") + CxConst::xSLASH + xT("111")
        };

        for (size_t i = 0; i < xARRAY_SIZE(sDirPathes); ++ i) {
            m_bRes = CxDir::bCreateForce(sDirPathes[i]);
            xASSERT_DIFF(FALSE, m_bRes);
        }

        //-------------------------------------
        //bMove
        m_bRes = CxDir::bMove(csDirSource, csDirDest, TRUE);
        xASSERT_DIFF(FALSE, m_bRes);

        m_bRes = CxDir::bDelete(csDirDest);
        xASSERT_DIFF(FALSE, m_bRes);
	}

    //-------------------------------------
    //bFindDirs
    xTEST_BLOCK(cullBlockLoops)
    {
        //-------------------------------------
        //prepare for csTempScanDirPath (create dirs)
        const std::tstring sDirPathes[] =
        {
            csTempScanDirPath + CxConst::xSLASH + xT("A"),
            csTempScanDirPath + CxConst::xSLASH + xT("B"),
            csTempScanDirPath + CxConst::xSLASH + xT("A") + CxConst::xSLASH + xT("AA"),
            csTempScanDirPath + CxConst::xSLASH + xT("A") + CxConst::xSLASH + xT("AA") + CxConst::xSLASH + xT("AAA")
        };

        for (size_t i = 0; i < xARRAY_SIZE(sDirPathes); ++ i) {
            m_bRes = CxDir::bCreateForce(sDirPathes[i]);
            xASSERT_DIFF(FALSE, m_bRes);
        }

        //-------------------------------------
        //bFindDirs
        {
            m_vsRes.clear();
            m_bRes = CxDir::bFindDirs(csTempScanDirPath, CxConst::xMASK_ALL, FALSE, &m_vsRes);
            xASSERT_DIFF(FALSE, m_bRes);
            //CxString::vStdVectorPrintT(m_vsRes);

            xASSERT_EQ((size_t)2, m_vsRes.size());
        }

        //-------------------------------------
        //bFindDirs
        {
            m_vsRes.clear();
            m_bRes = CxDir::bFindDirs(csTempScanDirPath, CxConst::xMASK_ALL, TRUE, &m_vsRes);
            xASSERT_DIFF(FALSE, m_bRes);
            //CxString::vStdVectorPrintT(m_vsRes);

            xASSERT_EQ(xARRAY_SIZE(sDirPathes), m_vsRes.size());
        }
    }

    //-------------------------------------
    //bFindFiles
    xTEST_BLOCK(cullBlockLoops)
    {
        //-------------------------------------
        //prepare for csTempScanDirPath (create files)
        const std::tstring g_sFilePathes[] =
        {
            csTempScanDirPath + CxConst::xSLASH + xT("File_1"),
            csTempScanDirPath + CxConst::xSLASH + xT("File_2"),
            csTempScanDirPath + CxConst::xSLASH + xT("A") + CxConst::xSLASH + xT("File_3"),
            csTempScanDirPath + CxConst::xSLASH + xT("B") + CxConst::xSLASH + xT("File_4"),
            csTempScanDirPath + CxConst::xSLASH + xT("A") + CxConst::xSLASH + xT("AA") + CxConst::xSLASH + xT("File_5"),
            csTempScanDirPath + CxConst::xSLASH + xT("A") + CxConst::xSLASH + xT("AA") + CxConst::xSLASH + xT("AAA") + CxConst::xSLASH + xT("File_6")
        };

        for (size_t i = 0; i < xARRAY_SIZE(g_sFilePathes); ++ i) {
            CxFile sfFile;

            m_bRes = sfFile.bCreate(g_sFilePathes[i], CxFile::omWrite, TRUE);
            xASSERT_DIFF(FALSE, m_bRes);
        }

        //-------------------------------------
        //bFindFiles
        {
            m_vsRes.clear();
            m_bRes = CxDir::bFindFiles(csTempScanDirPath, CxConst::xMASK_ALL, FALSE, &m_vsRes);
            xASSERT_DIFF(FALSE, m_bRes);
            //CxString::vStdVectorPrintT(m_vsRes);

            xASSERT_EQ((size_t)2, m_vsRes.size());
        }

        //-------------------------------------
        //bFindFiles
        {
            m_vsRes.clear();
            m_bRes = CxDir::bFindFiles(csTempScanDirPath, CxConst::xMASK_ALL, TRUE, &m_vsRes);
            xASSERT_DIFF(FALSE, m_bRes);
            //CxString::vStdVectorPrintT(m_vsRes);

            xASSERT_EQ(xARRAY_SIZE(g_sFilePathes), m_vsRes.size());
        }
    }

	//-------------------------------------
	//bClearForce
    xTEST_BLOCK(cullBlockLoops)
	{
		m_bRes = CxDir::bClearForce(csDirPath);
		xASSERT_DIFF(FALSE, m_bRes);
	}

    //-------------------------------------
    //bDelete
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxDir::bDelete(csDirPath2);
        xASSERT_DIFF(FALSE, m_bRes);
    }

    //-------------------------------------
    //bTryDelete
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = CxDir::bCreateForce(csDirPath2);
        xASSERT_DIFF(FALSE, m_bRes);

        m_bRes = CxDir::bTryDelete(csDirPath2, 10, 5);
        xASSERT_DIFF(FALSE, m_bRes);
    }

	//-------------------------------------
	//bDeleteForce
    xTEST_BLOCK(cullBlockLoops)
	{
		m_bRes = CxDir::bCreateForce(csDirPath);
		xASSERT_DIFF(FALSE, m_bRes);

		m_bRes = CxDir::bDeleteForce(csDirPath);
		xASSERT_DIFF(FALSE, m_bRes);
	}

	return TRUE;
}
//---------------------------------------------------------------------------
