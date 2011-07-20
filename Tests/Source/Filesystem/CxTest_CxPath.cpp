/****************************************************************************
* Class name:  CxTest_CxPath
* Description: test CxPath
* File name:   CxTest_CxPath.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Filesystem/CxTest_CxPath.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxPath
CxTest_CxPath::CxTest_CxPath() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxPath
CxTest_CxPath::~CxTest_CxPath() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxPath::bUnit() {
	//-------------------------------------
	//vars
	tString       sRes          = xT("");
	std::vector<tString> vecsRes;

    #if defined(xOS_WIN)
    const tString csFilePath    = xT("C:\\Test.txt");
    const tString csNewFilePath = xT("C:\\New.Test.txt");
    const tString csBakFilePath = xT("C:\\Test_Static.txt.bak");
    const tString csFilePathSt  = xT("C:\\Test_Static.txt");
    const tString csFileName    = xT("TestName");
    const tString csFileExt     = xT("doc");
    #elif defined(xOS_LINUX)
    const tString csFilePath    = xT("/home/user/Soft/eclipse/workspace/xLib.test/Debug/filename");
    const tString csNewFilePath = xT("/home/user/Soft/New.Test.txt");
    const tString csBakFilePath = xT("/home/user/Soft/Test_Static.txt.bak");
    const tString csFilePathSt  = xT("/home/user/Soft/Test_Static.txt");
    const tString csFileName    = xT("TestName");
    const tString csFileExt     = xT("doc");
    #endif



	/****************************************************************************
	*	����
	*
	*****************************************************************************/

	//-------------------------------------
	//sGetExe
    {
    	sRes = CxPath::sGetExe();
        #if defined(xOS_WIN)
        xASSERT(sRes == xT("D:\\xLib\\Contrib\\VC++ 2010\\Debug\\Test.VC++ 2010.exe"));
        #elif defined(xOS_LINUX)
        //TODO: sGetExe
        #endif
    }

    //-------------------------------------
    //sGetDll
    {
        sRes = CxPath::sGetDll();
        #if xTODO
            xASSERT(false == sRes.empty());
        #endif
    }

	//-------------------------------------
	//sGetExeDir
    {
    	sRes = CxPath::sGetExeDir();
        #if defined(xOS_WIN)
        xASSERT(sRes == xT("D:\\xLib\\Contrib\\VC++ 2010\\Debug"));
        #elif defined(xOS_LINUX)
        //TODO: sGetExeDir
        #endif
    }

    //-------------------------------------
    //sGetDrive
    {
        #if defined(xOS_WIN)
        sRes    = CxPath::sGetDrive(csFilePath);
        xASSERT(sRes == xT("C:"));
        #endif
    }

    //-------------------------------------
    //sGetDir
    {
        #if defined(xOS_WIN)
        const tString sData[][2] = {
            {xT("C:\\Test111\\Test.txt"),                            xT("C:\\Test111")},
            {xT("C:\\Test.txt"),                                     xT("C:")},
            {xT("Test.txt"),                                         xT("")},
            {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("D:\\My projects\\Borland C++")}
        };
        #elif defined(xOS_LINUX)
        const tString sData[][2] = {
            {xT("/home/user/Soft/eclipse/Test.txt"),           xT("/home/user/Soft/eclipse")},
            {xT("/home/Test.txt"),                             xT("/home")},
            {xT("Test.txt"),                                   xT("")},
            {xT("/home/user/Soft/eclipse/pLaunchProject.exe"), xT("/home/user/Soft/eclipse")}
        };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            tString sStr1 = CxPath::sGetDir(sData[i][0]);
            tString sStr2 = sData[i][1];
            xASSERT(sStr1 == sStr2);
        }
    }

    //-------------------------------------
    //sGetDirName
    {
        #if defined(xOS_WIN)
        const tString sData[][2] = {
            {xT("C:\\Test111\\Test.txt"),                            xT("Test111")},
            {xT("C:\\Test.txt"),                                     xT("C:")},
            {xT("Test.txt"),                                         xT("")},
            {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("Borland C++")}
        };
        #elif defined(xOS_LINUX)
        const tString sData[][2] = {
            {xT("/home/user/Soft/eclipse/Test.txt"),           xT("eclipse")},
            {xT("/home/Test.txt"),                             xT("home")},
            {xT("Test.txt"),                                   xT("")},
            {xT("/home/user/Soft/eclipse/pLaunchProject.exe"), xT("eclipse")}
        };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            tString sStr1 = CxPath::sGetDirName(sData[i][0]);
            tString sStr2 = sData[i][1];
            xASSERT(sStr1 == sStr2);
        }
    }

	//-------------------------------------
	//sGetFullName
    {
        #if defined(xOS_WIN)
        const tString sData[][2] = {
            {xT("C:\\Test111\\Test.txt"),                            xT("Test.txt")},
            {xT("C:\\Test"),                                         xT("Test")},
            {xT("Test.txt"),                                         xT("Test.txt")},
            {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("pLaunchProject.exe")}
        };
        #elif defined(xOS_LINUX)
        const tString sData[][2] = {
            {xT("/home/Test111/Test.txt"),                           xT("Test.txt")},
            {xT("/home/Test"),                                       xT("Test")},
            {xT("Test.txt"),                                         xT("Test.txt")},
            {xT("/home/My projects/Borland C++/pLaunchProject.exe"), xT("pLaunchProject.exe")}
        };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            tString sStr1 = CxPath::sGetFullName(sData[i][0]);
            tString sStr2 = sData[i][1];
            xASSERT(sStr1 == sStr2);
        }
    }

	//-------------------------------------
	//sGetName
    {
        #if defined(xOS_WIN)
        const tString sData[][2] = {
            {xT("C:\\Test111\\Test.txt"),                            xT("Test")},
            {xT("C:\\Test"),                                         xT("Test")},
            {xT("Test.txt"),                                         xT("Test")},
            {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("pLaunchProject")}
        };
        #elif defined(xOS_LINUX)
        const tString sData[][2] = {
            {xT("/home/Test111/Test.txt"),                           xT("Test")},
            {xT("/home/Test"),                                       xT("Test")},
            {xT("Test.txt"),                                         xT("Test")},
            {xT("/home/My projects/Borland C++/pLaunchProject.exe"), xT("pLaunchProject")}
        };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            tString sStr1 = CxPath::sGetName(sData[i][0]);
            tString sStr2 = sData[i][1];
            xASSERT(sStr1 == sStr2);
        }
    }

	//-------------------------------------
	//sGetExt
    {
        #if defined(xOS_WIN)
        const tString sData[][2] = {
            {xT("C:\\Test111\\Test.txt"),                            xT("txt")},
            {xT("C:\\Test"),                                         xT("")},
            {xT("Test.txt"),                                         xT("txt")},
            {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("exe")},
            {xT("D:\\My projects\\Borlan.d C++\\pLaunchProject"),    xT("")},
        };
        #elif defined(xOS_LINUX)
        const tString sData[][2] = {
            {xT("/home/Test111/Test.txt"),                           xT("txt")},
            {xT("/home/Test"),                                       xT("")},
            {xT("Test.txt"),                                         xT("txt")},
            {xT("/home/My projects/Borland C++/pLaunchProject.exe"), xT("exe")},
            {xT("/home/My projects/Borlan.d C++/pLaunchProject"),    xT("")}
        };
        #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            tString sStr1 = CxPath::sGetExt(sData[i][0]);
            tString sStr2 = sData[i][1];
            xASSERT_MSG(sStr1 == sStr2, (sStr2 + xT(" == ") + sStr1).c_str() );
        }
    }

    //-------------------------------------
    //sGetStandartExt
    {
	    m_sRes = CxPath::sGetStandartExt(CxPath::seExe);
        #if defined(xOS_WIN)
            xASSERT(xT("exe") == m_sRes);
        #elif defined(xOS_LINUX)
            xASSERT(xT("")    == m_sRes);
        #endif

        m_sRes = CxPath::sGetStandartExt(CxPath::seDll);
        #if defined(xOS_WIN)
            xASSERT(xT("dll") == m_sRes);
        #elif defined(xOS_LINUX)
            xASSERT(xT("so")  == m_sRes);
        #endif

        m_sRes = CxPath::sGetStandartExt(CxPath::seLib);
        #if defined(xOS_WIN)
            xASSERT(xT("lib") == m_sRes);
        #elif defined(xOS_LINUX)
            xASSERT(xT("a")   == m_sRes);
        #endif
    }

	//-------------------------------------
	//sSetDrive
	{
        #if defined(xOS_WIN)
        const tString sData[][3] = {
            {xT("C:\\Test.doc"),                  xT("F:"),	xT("F:\\Test.doc")},
            {xT("Z:\\okoval@winnerauto.ua.info"), xT("T:"),	xT("T:\\okoval@winnerauto.ua.info")},
            ////{xT("TEST_STRING_3.doc"),             xT("R:"),	xT("")},
            {xT("D:\\Test.config"),               xT("A:"),	xT("A:\\Test.config")},
            ////{xT("TEST_STRING_3.f"),               xT("B:"),	xT("")}
        };

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            tString sStr1 = CxPath::sSetDrive(sData[i][0], sData[i][1]);
            tString sStr2 = CxPath::sSetDrive(sData[i][2], sData[i][1]);
            xASSERT(sStr1 == sStr2);

            tString sStr3 = CxPath::sSetDrive(sData[i][0], sData[i][1]);
            tString sStr4 = sData[i][2];
            xASSERT(sStr3 == sStr4);
        }
        #endif
	}

	//-------------------------------------
	//sSetDir
	{
        #if defined(xOS_WIN)
            const tString sData[][3] = {
                {xT("C:\\Test.doc"),                  xT("F:\\"),	  xT("F:\\Test.doc")},
                {xT("Z:\\okoval@winnerauto.ua.info"), xT("T:\\"),	  xT("T:\\okoval@winnerauto.ua.info")},
                ////{xT("TEST_STRING_3.doc"),         xT("R:\\"),	  xT("")},
                {xT("D:\\Test.config"),               xT("A:\\"),	  xT("A:\\Test.config")},
                ////{xT("TEST_STRING_3.f"),           xT("B:\\"),	  xT("")}
                {xT("D:\\Test\\Test.config"),         xT("A:\\"),	  xT("A:\\Test.config")},
                {xT("D:\\Test\\Test.config"),         xT("A:\\1\\2"), xT("A:\\1\\2\\Test.config")}

            };
        #elif defined(xOS_LINUX)
            const tString sData[][3] = {
                {xT("/home/Test.doc"),                  xT("/job"),              xT("/job/Test.doc")},
                {xT("/home/okoval@winnerauto.ua.info"), xT("/job/room"),         xT("/job/room/okoval@winnerauto.ua.info")},
                ////{xT("TEST_STRING_3.doc"),           xT("R:\\"),              xT("")},
                {xT("/home/Test.config"),               xT("/school/class/305"), xT("/school/class/305/Test.config")},
                ////{xT("TEST_STRING_3.f"),             xT("B:\\"),              xT("")}
                {xT("/home/Test/Test.config"),          xT("/factory/"),         xT("/factory/Test.config")},
                {xT("/home/Test/Test.config"),          xT("/xxx"),              xT("/xxx/Test.config")}
            };
        #endif

		for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
			//tString sStr1 = CxPath::sSetDir(sData[i][0], sData[i][1]);
			//tString sStr2 = CxPath::sSetDir(sData[i][2], sData[i][1]);
			//xASSERT_MSG(sStr1 == sStr2, (sStr1 + xT(" == ") + sStr2).c_str());

			tString sStr3 = CxPath::sSetDir(sData[i][0], sData[i][1]);
			tString sStr4 = sData[i][2];
			xASSERT_MSG(sStr3 == sStr4, (sStr3 + xT(" == ") + sStr4).c_str());
		}
	}

	//-------------------------------------
	//sSetFullName
	{
        #if defined(xOS_WIN)
        const tString sData[][3] = {
            /*FilePath*/						  /*NewFileName*/   /*MustBe*/
            {xT("C:\\Test.doc"),                  xT("aaaa.xls"),	xT("C:\\aaaa.xls")},
            {xT("Z:\\okoval@winnerauto.ua.info"), xT("qwerty.fdm"),	xT("Z:\\qwerty.fdm")},
            ////{xT("TEST_STRING_3.doc"),         xT("xxxxxx.c"),	xT("xxxxxx.c")},
            {xT("D:\\Test.config"),               xT("r.txt"),		xT("D:\\r.txt")},
            ////{xT("TEST_STRING_3.f"),           xT("fff.qq"),		xT("fff.qq")}
        };
        #elif defined(xOS_LINUX)
        const tString sData[][3] = {
            /*FilePath*/                            /*NewFileName*/   /*MustBe*/
            {xT("/home/Test.doc"),                  xT("aaaa.xls"),   xT("/home/aaaa.xls")},
            {xT("/home/okoval@winnerauto.ua.info"), xT("qwerty.fdm"), xT("/home/qwerty.fdm")},
            ////{xT("TEST_STRING_3.doc"),           xT("xxxxxx.c"),   xT("xxxxxx.c")},
            {xT("/home/Test.config"),               xT("r.txt"),      xT("/home/r.txt")},
            ////{xT("TEST_STRING_3.f"),             xT("fff.qq"),     xT("fff.qq")}
        };
        #endif

		for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
			tString sStr1 = CxPath::sSetFullName(sData[i][0], sData[i][1]);
			tString sStr2 = CxPath::sSetFullName(sData[i][2], sData[i][1]);
			xASSERT(sStr1 == sStr2);

			tString sStr3 = CxPath::sSetFullName(sData[i][0], sData[i][1]);
			tString sStr4 = sData[i][2];
			xASSERT(sStr3 == sStr4);
		}
	}

	//-------------------------------------
	//sSetName
	{
        #if defined(xOS_WIN)
            const tString sData[][3] = {
                {xT("C:\\Test.doc"),                  xT("xxx"),	  xT("C:\\xxx.doc")},
                {xT("Z:\\okoval@winnerauto.ua.info"), xT("qwerty"),	  xT("Z:\\qwerty.info")},
                ////{xT("TEST_STRING_3.doc"),         xT(""),	      xT("")},
                ////{xT("D:\\Test.config"),               xT(""),	      xT("D:\\.config")},
                ////{xT("TEST_STRING_3.f"),           xT("B:\\"),	  xT("")}
                {xT("D:\\Test\\Test.config"),         xT("rrr"),	  xT("D:\\Test\\rrr.config")},
                {xT("D:\\1\\2\\Test\\Test.config"),   xT("yyyyyyyy"), xT("D:\\1\\2\\Test\\yyyyyyyy.config")}

            };
        #elif defined(xOS_LINUX)
            const tString sData[][3] = {
                {xT("/home/Test.doc"),                  xT("xxx"),      xT("/home/xxx.doc")},
                {xT("/home/okoval@winnerauto.ua.info"), xT("qwerty"),   xT("/home/qwerty.info")},
                ////{xT("TEST_STRING_3.doc"),           xT(""),           xT("")},
                ////{xT("D:\\Test.config"),             xT(""),       xT("xxxxxxxxxxxxx")},
                ////{xT("TEST_STRING_3.f"),             xT("B:\\"),       xT("")}
                {xT("/home/Test/Test.config"),         xT("rrr"),      xT("/home/Test/rrr.config")},
                {xT("/home/1/2/Test/Test.config"),     xT("yyyyyyyy"), xT("/home/1/2/Test/yyyyyyyy.config")}
            };
        #endif

		for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
			tString sStr1 = CxPath::sSetName(sData[i][0], sData[i][1]);
			tString sStr2 = CxPath::sSetName(sData[i][2], sData[i][1]);
			xASSERT(sStr1 == sStr2);

			tString sStr3 = CxPath::sSetName(sData[i][0], sData[i][1]);
			tString sStr4 = sData[i][2];
			xASSERT(sStr3 == sStr4);
		}
	}


	//-------------------------------------
	//sSetExt
	{
        const tString sData[][3] = {
            {xT("C:\\Test.doc"),                  xT("xls"),    xT("C:\\Test.xls")},
            {xT("C:\\Test"),                      xT("xls"),    xT("C:\\Test.xls")},
            {xT("Z:\\okoval@winnerauto.ua.info"), xT("fdm"),	xT("Z:\\okoval@winnerauto.ua.fdm")},
            {xT("TEST_STRING_3.doc"),             xT("xxxxxx"),	xT("TEST_STRING_3.xxxxxx")},
            {xT("D:\\Test.config"),               xT("txt"),	xT("D:\\Test.txt")},
            {xT("TEST_STRING_3.f"),               xT("fff"),	xT("TEST_STRING_3.fff")},
            {xT("TEST_STRING_4"),                 xT("fff"),	xT("TEST_STRING_4.fff")}
        };

		for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
			tString sStr1 = CxPath::sSetExt(sData[i][0], sData[i][1]);
			tString sStr2 = CxPath::sSetExt(sData[i][2], sData[i][1]);
			xASSERT(sStr1 == sStr2);

			tString sStr3 = CxPath::sSetExt(sData[i][0], sData[i][1]);
			tString sStr4 = sData[i][2];
			xASSERT(sStr3 == sStr4);
		}
	}



	//-------------------------------------
	//sRemoveExt
    {
    #if defined(xOS_WIN)
        const tString sData[][2] = {
            {xT("C:\\Test.111\\Test.txt"),                            xT("C:\\Test.111\\Test")},
            {xT("C:\\Test"),                                         xT("C:\\Test")},
            {xT("Test.txt"),                                         xT("Test")},
            {xT("D:\\My projects\\Borland C++\\pLaunchProject.exe"), xT("D:\\My projects\\Borland C++\\pLaunchProject")}
        };
    #elif defined(xOS_LINUX)
        const tString sData[][2] = {
            {xT("/home/Test.111/Test.txt"),                           xT("/home/Test.111/Test")},
            {xT("/home/Test"),                                       xT("/home/Test")},
            {xT("Test.txt"),                                         xT("Test")},
            {xT("/home/My projects/Borland C++/pLaunchProject.exe"), xT("/home/My projects/Borland C++/pLaunchProject")}
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            tString sStr1 = CxPath::sRemoveExt(sData[i][0]);
            tString sStr2 = sData[i][1];
            xASSERT_MSG(sStr1 == sStr2, (sStr1 + xT(" == ") + sStr2).c_str());
        }
    }

	//-------------------------------------
	//sSetValidName
	{
    #if defined(xOS_WIN)
        const tString sTestData[][2] =
        {
            {xT("CLOCK$"),		 xT("")},
            {xT("AUX"),			 xT("")},
            {xT("CON"),			 xT("")},
            {xT("NUL"),			 xT("")},
            {xT("PRN"),			 xT("")},
            {xT("COM1"),		 xT("")},
            {xT("COM2"),		 xT("")},
            {xT("COM3"),		 xT("")},
            {xT("COM4"),		 xT("")},
            {xT("COM5"),		 xT("")},
            {xT("COM6"),		 xT("")},
            {xT("COM7"),		 xT("")},
            {xT("COM8"),		 xT("")},
            {xT("COM9"),		 xT("")},
            {xT("LPT1"),		 xT("")},
            {xT("LPT2"),		 xT("")},
            {xT("LPT3"),		 xT("")},
            {xT("LPT4"),		 xT("")},
            {xT("LPT5"),		 xT("")},
            {xT("LPT6"),		 xT("")},
            {xT("LPT7"),		 xT("")},
            {xT("LPT8"),		 xT("")},
            {xT("LPT9"),		 xT("")},
            {xT("clock$"),		 xT("")},
            {xT("aux"),			 xT("")},
            {xT("con"),			 xT("")},
            {xT("nul"),			 xT("")},
            {xT("prn"),			 xT("")},
            {xT("com1"),		 xT("")},
            {xT("com2"),		 xT("")},
            {xT("com3"),		 xT("")},
            {xT("com4"),		 xT("")},
            {xT("com5"),		 xT("")},
            {xT("com6"),		 xT("")},
            {xT("com7"),		 xT("")},
            {xT("com8"),		 xT("")},
            {xT("com9"),		 xT("")},
            {xT("LPT1"),		 xT("")},
            {xT("LPT2"),		 xT("")},
            {xT("LPT3"),		 xT("")},
            {xT("LPT4"),		 xT("")},
            {xT("LPT5"),		 xT("")},
            {xT("LPT6"),		 xT("")},
            {xT("LPT7"),		 xT("")},
            {xT("LPT8"),		 xT("")},
            {xT("LPT9"),		 xT("")},
            {xT("clock$.txt"),	 xT("")},
            {xT("aux.txt"),		 xT("")},
            {xT("con.txt"),		 xT("")},
            {xT("nul.txt"),		 xT("")},
            {xT("prn.txt"),		 xT("")},
            {xT("com1.txt"),	 xT("")},
            {xT("com2.txt"),	 xT("")},
            {xT("com3.txt"),	 xT("")},
            {xT("com4.txt"),	 xT("")},
            {xT("com5.txt"),	 xT("")},
            {xT("com6.txt"),	 xT("")},
            {xT("com7.txt"),	 xT("")},
            {xT("com8.txt"),	 xT("")},
            {xT("com9.txt"),	 xT("")},
            {xT("LPT1.txt"),	 xT("")},
            {xT("LPT2.txt"),	 xT("")},
            {xT("LPT3.txt"),	 xT("")},
            {xT("LPT4.txt"),	 xT("")},
            {xT("LPT5.txt"),	 xT("")},
            {xT("LPT6.txt"),	 xT("")},
            {xT("LPT7.txt"),	 xT("")},
            {xT("LPT8.txt"),	 xT("")},
            {xT("LPT9.txt"),	 xT("")},
            {xT("T\t"),			 xT("T")},
            {xT("T\n"),			 xT("T")},
            {xT("T\r"),			 xT("T")},
            {xT("T<"),			 xT("T")},
            {xT("T>"),			 xT("T")},
            {xT("T:"),			 xT("T")},
            {xT("T\""),			 xT("T")},
            {xT("T\\"),			 xT("T")},
            {xT("T/"),			 xT("T")},
            {xT("T*"),			 xT("T")},
            {xT("T?"),			 xT("T")},
            {xT("T|"),			 xT("T")},
            {xT("..."),		     xT("")},
            {xT("Good Data"),	 xT("Good Data")},
            {xT("commit"),		 xT("commit")},
            {xT("console"),		 xT("console")},
            {xT("LPT10"),		 xT("LPT10")},
            {xT("clock"),		 xT("clock")},
            {xT(".aux.txt"),	 xT("")},
            {xT("auxx.aux.txt"), xT("auxx.aux.txt")},
            {xT("NULL"),         xT("NULL")},
            {xT("?V|||/:*?\"<>|||a:l/:*?\"<>|/:*?\"<>|/:*?\"<>|\\i?dT*e/:*?\"<>|stN////:*?\"<>|///ame"), xT("ValidTestName")},
        };
    #elif defined(xOS_LINUX)
        const tString sTestData[][2] =
        {
            {xT("xxxx"),       xT("xxxx")},
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sTestData); ++ i) {
            tString sStr1 = CxPath::sSetValidName(sTestData[i][0]);
            tString sStr2 = CxPath::sSetValidName(sTestData[i][1]);
            xASSERT(sStr1 == sStr2);

            tString sStr3 = CxPath::sSetValidName(sTestData[i][0]);
            tString sStr4 = sTestData[i][1];
            xASSERT(sStr3 == sStr4);
        }
	}

	//-------------------------------------
	//sToWin
	{
	    const tString csUnixPath = xT("C:/TestDir");
	    const tString csWinPath  = xT("C:\\TestDir");

	    sRes    = CxPath::sToWin(csUnixPath, FALSE);
		xASSERT(sRes == xT("C:\\TestDir"));

		sRes    = CxPath::sToWin(csUnixPath, TRUE);
		xASSERT(sRes == xT("C:\\TestDir\\"));

		sRes    = CxPath::sToWin(csWinPath, TRUE);
		xASSERT(sRes == xT("C:\\TestDir\\"));

		sRes    = CxPath::sToWin(csWinPath, FALSE);
		xASSERT(sRes == xT("C:\\TestDir"));
	}

	//-------------------------------------
	//sToNix
	{
        const tString csUnixPath = xT("/home/user/Soft/TestDir");
        const tString csWinPath  = xT("\\home\\user\\Soft\\TestDir");

		sRes    = CxPath::sToNix(csUnixPath,  FALSE);
		xASSERT(sRes == xT("/home/user/Soft/TestDir"));

		sRes    = CxPath::sToNix(csUnixPath,  TRUE);
		xASSERT(sRes == xT("/home/user/Soft/TestDir/"));

		sRes    = CxPath::sToNix(csWinPath,  TRUE);
		xASSERT(sRes == xT("/home/user/Soft/TestDir/"));

		sRes    = CxPath::sToNix(csWinPath,  FALSE);
		xASSERT(sRes == xT("/home/user/Soft/TestDir"));
	}

	//--------------------------------------------------
    //sToCurrentOs
    {
    #if defined(xOS_WIN)
        const tString csUnixPath = xT("C:/TestDir");
        const tString csWinPath  = xT("C:\\TestDir");

        sRes = CxPath::sToCurrentOs(csWinPath,  FALSE);
        xASSERT(sRes == xT("C:\\TestDir"));

        sRes = CxPath::sToCurrentOs(csWinPath,  TRUE);
        xASSERT(sRes == xT("C:\\TestDir\\"));

        sRes = CxPath::sToCurrentOs(csWinPath,  TRUE);
        xASSERT(sRes == xT("C:\\TestDir\\"));

        sRes = CxPath::sToCurrentOs(csWinPath,  FALSE);
        xASSERT(sRes == xT("C:\\TestDir"));
    #elif defined(xOS_LINUX)
        const tString csUnixPath = xT("/home/user/Soft/TestDir");
        const tString csWinPath  = xT("\\home\\user\\Soft\\TestDir");

        sRes = CxPath::sToCurrentOs(csWinPath,  FALSE);
        xASSERT(sRes == xT("/home/user/Soft/TestDir"));

        sRes = CxPath::sToCurrentOs(csWinPath,  TRUE);
        xASSERT(sRes == xT("/home/user/Soft/TestDir/"));

        sRes = CxPath::sToCurrentOs(csWinPath,  TRUE);
        xASSERT(sRes == xT("/home/user/Soft/TestDir/"));

        sRes = CxPath::sToCurrentOs(csWinPath,  FALSE);
        xASSERT(sRes == xT("/home/user/Soft/TestDir"));
    #endif
    }

	//-------------------------------------
	//TODO: sMinimizeName
	{
        const tString sData[][2] = {
            {xT("Name"),                   xT("Name")},
            {xT("full name"),              xT("ful~")},
            {xT("file name with ext"),     xT("fil~")},
            {xT("comment"),                xT("com~")},

            {xT("Name.exe"),               xT("Name")},
            {xT("full name.txt"),          xT("full")},
            {xT("file name with ext.doc"), xT("file")},
            {xT("comment.pdfx"),           xT("comm")},
        };

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            tString sStr1 = CxPath::sMinimizeName(sData[i][0], 4);
            tString sStr2 = sData[i][1];
            xASSERT_MSG(sStr1 == sStr2, (sStr1 + xT(" == ") + sStr2).c_str());
        }
	}

	//-------------------------------------
	//sMinimize
	{
    #if defined(xOS_WIN)
        sRes    = CxPath::sMinimize(csFilePath, 4);
        // n/a

        tString sFilePath = xT("D:/xVCL/Include\\xVCL/Units/Gui/vSpeedButton_LoadDrives.cpp");
        sRes    = CxPath::sMinimize(sFilePath, 45);
        // n/a
    #elif defined(xOS_LINUX)
        //TODO: sMinimize
    #endif
	}

	//-------------------------------------
	//sSlashAppend
	{
    #if defined(xOS_WIN)
        const tString sData[][3] = {
            {xT("C:\\Test.doc"),                  xT("C:\\Test.doc\\")},
            {xT("Z:\\okoval@winnerauto.ua.info"), xT("Z:\\okoval@winnerauto.ua.info\\")},
            {xT("TEST_STRING_3.doc\\"),           xT("TEST_STRING_3.doc\\")},
            {xT("D:\\Test.config"),               xT("D:\\Test.config\\")},
            {xT("TEST_STRING_3.f\\"),             xT("TEST_STRING_3.f\\")}
        };
    #elif defined(xOS_LINUX)
        const tString sData[][3] = {
            {xT("/home/Test.doc"),                  xT("/home/Test.doc/")},
            {xT("/home/okoval@winnerauto.ua.info"), xT("/home/okoval@winnerauto.ua.info/")},
            {xT("TEST_STRING_3.doc//"),             xT("TEST_STRING_3.doc/")},
            {xT("/home/Test.config"),               xT("/home/Test.config/")},
            {xT("TEST_STRING_3.f/"),                xT("TEST_STRING_3.f/")}
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            tString sStr1 = CxPath::sSlashAppend(sData[i][0]);
            tString sStr2 = CxPath::sSlashAppend(sData[i][1]);
            xASSERT_MSG(sStr1 == sStr2, (sStr1 + xT(" == ") + sStr2).c_str());

            tString sStr3 = CxPath::sSlashAppend(sData[i][0]);
            tString sStr4 = sData[i][1];
            xASSERT_MSG(sStr3 == sStr3, (sStr3 + xT(" == ") + sStr4).c_str());
        }
	}

	//-------------------------------------
	//sSlashRemove
	{
    #if defined(xOS_WIN)
        const tString sData[][3] = {
            {xT("C:\\Test.doc"),                  xT("C:\\Test.doc")},
            {xT("Z:\\okoval@winnerauto.ua.info"), xT("Z:\\okoval@winnerauto.ua.info")},
            {xT("TEST_STRING_3.doc\\"),           xT("TEST_STRING_3.doc")},
            {xT("D:\\Test.config"),               xT("D:\\Test.config")},
            {xT("TEST_STRING_3.f\\"),             xT("TEST_STRING_3.f")}
        };
    #elif defined(xOS_LINUX)
        const tString sData[][3] = {
            {xT("/home/Test.doc"),                  xT("/home/Test.doc")},
            {xT("/home/okoval@winnerauto.ua.info"), xT("/home/okoval@winnerauto.ua.info")},
            {xT("TEST_STRING_3.doc//"),             xT("TEST_STRING_3.doc")},
            {xT("/home/Test.config"),               xT("/home/Test.config")},
            {xT("TEST_STRING_3.f/"),                xT("TEST_STRING_3.f")}
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            tString sStr1 = CxPath::sSlashRemove(sData[i][0]);
            tString sStr2 = CxPath::sSlashRemove(sData[i][1]);
            xASSERT_MSG(sStr1 == sStr2, (sStr1 + xT(" == ") + sStr2).c_str());

            tString sStr3 = CxPath::sSlashRemove(sData[i][0]);
            tString sStr4 = sData[i][1];
            xASSERT_MSG(sStr3 == sStr3, (sStr3 + xT(" == ") + sStr4).c_str());
        }
	}

    //--------------------------------------------------
    //uiGetMaxSize
    {
    	m_uiRes = CxPath::uiGetMaxSize();
    	xASSERT(0 < m_uiRes);
    }

    //--------------------------------------------------
    //uiGetNameMaxSize
    {
        m_uiRes = CxPath::uiGetNameMaxSize();
        xASSERT(0 < m_uiRes);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
