/****************************************************************************
* Class name:  CxTest_CxDir
* Description: testing CxDir
* File name:   CxTest_CxDir.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxDirH
#define CxTest_CxDirH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxStdioFile.h>
//---------------------------------------------------------------------------
class CxTest_CxDir : public CxTest {
	public:
		CxTest_CxDir();
		virtual     ~CxTest_CxDir();

		virtual     BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//TODO: + CxTest_CxDir (comment)
CxTest_CxDir::CxTest_CxDir() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//TODO: + ~CxTest_CxDir (comment)
CxTest_CxDir::~CxTest_CxDir() {

}
//---------------------------------------------------------------------------
//TODO: - bUnit ()
/*virtual*/
BOOL CxTest_CxDir::bUnit() {
    const tString csTempScanDirPath = sGetWorkDirPath() + CxConst::xSLASH + xT("Scan");
    const tString csMask            = xT("*.txt");

#if defined(xOS_WIN)
    const tString csFilePath		= sGetWorkDirPath() + xT("\\Test.txt");
    const tString csRootTestDirPath = sGetWorkDirPath() + xT("\\Test_Dir");
    const tString csDirPath         = sGetWorkDirPath() + xT("\\Test_Dir\\1\\2\\3");
    const tString csDirPath2		= sGetWorkDirPath() + xT("\\Test_Dir\\1\\2\\3\\4");
    const tString csNewFilePath		= sGetWorkDirPath() + xT("\\New.Test.txt");
    const tString csBakFilePath		= sGetWorkDirPath() + xT("\\Test_Static.txt.bak");
    const tString csFilePathSt		= sGetWorkDirPath() + xT("\\Test_Static.txt");
#elif defined(xOS_LINUX)
    const tString csFilePath        = sGetWorkDirPath() + xT("/Test.txt");
    const tString csRootTestDirPath = sGetWorkDirPath() + xT("/Test_Dir");
    const tString csDirPath         = sGetWorkDirPath() + xT("/Test_Dir/1/2/3");
    const tString csDirPath2        = sGetWorkDirPath() + xT("/Test_Dir/1/2/3/4");
    const tString csNewFilePath     = sGetWorkDirPath() + xT("/New.Test.txt");
    const tString csBakFilePath     = sGetWorkDirPath() + xT("/Test_Static.txt.bak");
    const tString csFilePathSt      = sGetWorkDirPath() + xT("/Test_Static.txt");
#endif

	/****************************************************************************
	*	prepare
	*
	*****************************************************************************/

	{
		m_bRes = CxDir::bDeleteForce(csRootTestDirPath);
		xASSERT(FALSE != m_bRes);

		m_bRes = CxDir::bCreateForce(csDirPath);
		xASSERT(FALSE != m_bRes);
	}

	/****************************************************************************
	*	static
	*
	*****************************************************************************/

	//-------------------------------------
	//bCreate
    {
    	m_bRes = CxDir::bCreate(csDirPath2);
        xASSERT(FALSE != m_bRes);
    }

    //-------------------------------------
    //bIsDir
    {
        m_bRes = CxDir::bIsDir(csDirPath2);
        xASSERT_MSG(FALSE != m_bRes, csDirPath2.c_str());
    }

	//-------------------------------------
	//bIsExists
	{
		m_bRes = CxDir::bIsExists(csDirPath);
		xASSERT(FALSE != m_bRes);

		m_bRes = CxDir::bIsExists(xT("y:"));
		xASSERT(FALSE == m_bRes);

		m_bRes = CxDir::bIsExists(xT("sdfasdf:"));
		xASSERT(FALSE == m_bRes);

		m_bRes = CxDir::bIsExists(xT("C:\\WINDOWS\\NOTEPAD.EXE"));
		xASSERT(FALSE == m_bRes);

		m_bRes = CxDir::bIsExists(xT("C:\\pagefile.sys"));
		xASSERT(FALSE == m_bRes);
	}

	//-------------------------------------
	//bIsEmpty
	{
		m_bRes = CxDir::bIsEmpty(csDirPath, CxConst::xMASK_ALL);
		xASSERT(FALSE == m_bRes);

		m_bRes = CxDir::bIsEmpty(csDirPath2, CxConst::xMASK_ALL);
		xASSERT(TRUE == m_bRes);

		m_bRes = CxDir::bIsEmpty(sGetWorkDirPath(), CxConst::xMASK_ALL);
		xASSERT(FALSE == m_bRes);
	}

	//-------------------------------------
	//bSetCurrent

		m_sRes = CxDir::sGetCurrent();
		xASSERT(false == m_sRes.empty());
	{
		m_bRes = CxDir::bSetCurrent( sGetWorkDirPath() );
		xASSERT(FALSE != m_bRes);

	    m_bRes = CxDir::bSetCurrent(m_sRes);
		xASSERT(FALSE != m_bRes);
	}

	//-------------------------------------
	//sGetCurrent
	{
		tString sRes = CxDir::sGetCurrent();
		xASSERT(m_sRes == sRes);
	}

	//-------------------------------------
	//sGetTempPath
	{
		m_sRes = CxDir::sGetTempPath();
        #if defined(xOS_WIN)
        xASSERT(xT("C:\\Temp\\") == m_sRes);
        #elif defined(xOS_LINUX)
        xASSERT(xT("/tmp") == m_sRes);
        #endif
	}

	//-------------------------------------
	//bCreateForce
	{
		m_bRes = CxDir::bCreateForce(csDirPath);
		xASSERT(FALSE != m_bRes);
	}

	//-------------------------------------
	//
	//bMove
	{

	}

	//-------------------------------------
	//
	//bCopy
	{

	}

    //-------------------------------------
    //bFindDirs
    {
        //-------------------------------------
        //prepare for csTempScanDirPath (create dirs)
        const tString g_sDirPathes[] =
        {
            csTempScanDirPath + CxConst::xSLASH + xT("A"),
            csTempScanDirPath + CxConst::xSLASH + xT("B"),
            csTempScanDirPath + CxConst::xSLASH + xT("A") + CxConst::xSLASH + xT("AA"),
            csTempScanDirPath + CxConst::xSLASH + xT("A") + CxConst::xSLASH + xT("AA") + CxConst::xSLASH + xT("AAA")
        };

        for (size_t i = 0; i < xARRAY_SIZE(g_sDirPathes); ++ i) {
            m_bRes = CxDir::bCreateForce(g_sDirPathes[i]);
            xASSERT(FALSE != m_bRes);
        }

        //-------------------------------------
        //bFindDirs
        {
            m_vecsRes.clear();
            m_bRes = CxDir::bFindDirs(csTempScanDirPath, CxConst::xMASK_ALL, FALSE, &m_vecsRes);
            xASSERT(FALSE != m_bRes);
            //CxString::vStdVectorPrintT(m_vecsRes);

            xASSERT(2 == m_vecsRes.size());
        }

        //-------------------------------------
        //bFindDirs
        {
            m_vecsRes.clear();
            m_bRes = CxDir::bFindDirs(csTempScanDirPath, CxConst::xMASK_ALL, TRUE, &m_vecsRes);
            xASSERT(FALSE != m_bRes);
            //CxString::vStdVectorPrintT(m_vecsRes);

            xASSERT(xARRAY_SIZE(g_sDirPathes) == m_vecsRes.size());
        }
    }

    //-------------------------------------
    //bFindFiles
    {
        ////-------------------------------------
        ////prepare for csTempScanDirPath (create files)
        const tString g_sFilePathes[] =
        {
            csTempScanDirPath + CxConst::xSLASH + xT("File_1"),
            csTempScanDirPath + CxConst::xSLASH + xT("File_2"),
            csTempScanDirPath + CxConst::xSLASH + xT("A") + CxConst::xSLASH + xT("File_3"),
            csTempScanDirPath + CxConst::xSLASH + xT("B") + CxConst::xSLASH + xT("File_4"),
            csTempScanDirPath + CxConst::xSLASH + xT("A") + CxConst::xSLASH + xT("AA") + CxConst::xSLASH + xT("File_5"),
            csTempScanDirPath + CxConst::xSLASH + xT("A") + CxConst::xSLASH + xT("AA") + CxConst::xSLASH + xT("AAA") + CxConst::xSLASH + xT("File_6")
        };

        for (size_t i = 0; i < xARRAY_SIZE(g_sFilePathes); ++ i) {
            CxStdioFile sfFile;

            m_bRes = sfFile.bOpen(g_sFilePathes[i], CxStdioFile::CxOpenMode::omWrite);
            xASSERT(FALSE != m_bRes);
        }

        //-------------------------------------
        //bFindFiles
        {
            m_vecsRes.clear();
            m_bRes = CxDir::bFindFiles(csTempScanDirPath, CxConst::xMASK_ALL, FALSE, &m_vecsRes);
            xASSERT(FALSE != m_bRes);
            //CxString::vStdVectorPrintT(m_vecsRes);

            xASSERT(2 == m_vecsRes.size());
        }

        //-------------------------------------
        //bFindFiles
        {
            m_vecsRes.clear();
            m_bRes = CxDir::bFindFiles(csTempScanDirPath, CxConst::xMASK_ALL, TRUE, &m_vecsRes);
            xASSERT(FALSE != m_bRes);
            //CxString::vStdVectorPrintT(m_vecsRes);

            xASSERT(xARRAY_SIZE(g_sFilePathes) == m_vecsRes.size());
        }
    }

	//-------------------------------------
	//bClearForce
	{
		m_bRes = CxDir::bClearForce(csDirPath);
		xASSERT(FALSE != m_bRes);
	}

	//-------------------------------------
	//bDelete
	{
		m_bRes = CxDir::bDelete(csDirPath2);
		xASSERT(FALSE != m_bRes);
	}

	//-------------------------------------
	//bDeleteForce
	{
		m_bRes = CxDir::bCreate(csDirPath);
		xASSERT(FALSE != m_bRes);

		m_bRes = CxDir::bDeleteForce(csRootTestDirPath);
		xASSERT(FALSE != m_bRes);
	}

	return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxDirH

