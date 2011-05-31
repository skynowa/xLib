/****************************************************************************
* Class name:  CxTest_CxEnvironment
* Description: test CxEnvironment
* File name:   CxTest_CxEnvironment.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxEnvironmentH
#define CxTest_CxEnvironmentH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/CxEnvironment.h>
//---------------------------------------------------------------------------
class CxTest_CxEnvironment : public CxTest {
	public:
		CxTest_CxEnvironment();
		virtual     ~CxTest_CxEnvironment();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//DONE: CxTest_CxEnvironment (constructor)
CxTest_CxEnvironment::CxTest_CxEnvironment() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxEnvironment (destructor)
CxTest_CxEnvironment::~CxTest_CxEnvironment() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxEnvironment::bUnit() {
    //-------------------------------------
    //bSetVar
    {
        const tString sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},   //custom
            {xT("ENV_TEST_2"), xT("value2")},   //custom
            {xT("ENV_TEST_3"), xT("value3")},   //custom
            {xT("ENV_TEST_4"), xT("value4")}    //custom
        };

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            m_bRes = CxEnvironment::bSetVar(sData[i][0], sData[i][1]);
            xASSERT(m_bRes == TRUE);
        }
    }

    //-------------------------------------
    //bIsExists
    {
    #if defined(xOS_WIN)
        const tString sData[][2] = {
            {xT("ENV_TEST_1"), xT("TRUE")},   //custom
            {xT("ENV_TEST_2"), xT("TRUE")},   //custom
            {xT("ENV_TEST_3"), xT("TRUE")},   //custom
            {xT("ENV_TEST_4"), xT("TRUE")},   //custom

            {xT("OS"),         xT("TRUE") },
            {xT("XXXL"),       xT("FALSE")},
            {xT("windir"),     xT("TRUE") }
        };
    #elif defined(xOS_LINUX)
        const tString sData[][2] = {
            {xT("ENV_TEST_1"), xT("TRUE")},   //custom
            {xT("ENV_TEST_2"), xT("TRUE")},   //custom
            {xT("ENV_TEST_3"), xT("TRUE")},   //custom
            {xT("ENV_TEST_4"), xT("TRUE")},   //custom

            ////{xT("USER"), xT("TRUE") },
            ////{xT("TERM"), xT("TRUE") },
            ////{xT("SHELL"), xT("TRUE")}
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            BOOL bStr1 = CxEnvironment::bIsExists(sData[i][0]);
            xASSERT_MSG((sData[i][1] == xT("FALSE") ? FALSE : TRUE) == bStr1, sData[i][0]);
        }
    }

    //-------------------------------------
    //sGetVar
    {
    #if defined(xOS_WIN)
        const tString sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},   //custom
            {xT("ENV_TEST_2"), xT("value2")},   //custom
            {xT("ENV_TEST_3"), xT("value3")},   //custom
            {xT("ENV_TEST_4"), xT("value4")},   //custom
        };
    #elif defined(xOS_LINUX)
        const tString sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},   //custom
            {xT("ENV_TEST_2"), xT("value2")},   //custom
            {xT("ENV_TEST_3"), xT("value3")},   //custom
            {xT("ENV_TEST_4"), xT("value4")},   //custom

            {xT("USER"),  xT("user")},
            {xT("SHELL"), xT("/bin/bash")}
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            tString sStr1 = CxEnvironment::sGetVar(sData[i][0]);
            tString sStr2 = sData[i][1];
            xASSERT_MSG(sStr1 == sStr2, (sStr1 + xT(" == ") + sStr2));
        }
    }

    //-------------------------------------
    //bGetValues
    {
        m_bRes = CxEnvironment::bGetValues(&m_vecsRes);
        xASSERT(FALSE != m_bRes);

        ////CxString::vStdVectorPrintT(m_vecsRes);
    }

	//-------------------------------------
	//sExpandStrings
    {
    #if defined(xOS_WIN)
        const tString sData[][2] = {
            {xT(" System root: %SystemRoot%"),  xT(" System root: C:\\WINDOWS")},
            {xT("Windows Dir: %windir% "),      xT("Windows Dir: C:\\WINDOWS ")}
        };
    #elif defined(xOS_LINUX)
        const tString sData[][2] = {
            {xT("111%ENV_TEST_1%"), xT("111value1")},   //custom
            {xT("%ENV_TEST_2%111"), xT("value2111")},   //custom
            {xT("ttt%ENV_TEST_3%"), xT("tttvalue3")},   //custom
            {xT("rrr%ENV_TEST_4%rrr"), xT("rrrvalue4rrr")},   //custom

            {xT("User = %USER%"),                     xT("User = user")},
            {xT("Shell = %SHELL%"),                   xT("Shell = /bin/bash")},
            {xT("User = %USER%, Shell = %SHELL%"),    xT("User = user, Shell = /bin/bash")},
            {xT("Home = %HOME%"),                     xT("Home = /home/user")},
            {xT("...User = %USER%"),                  xT("...User = user")},
            {xT("Shell = %SHELL%..."),                xT("Shell = /bin/bash...")},
            {xT("+++User = %USER%, Shell = %SHELL%"), xT("+++User = user, Shell = /bin/bash")},
            {xT("Home =   %HOME%"),                   xT("Home =   /home/user")},
            {xT("Home =   %HOME%"),                   xT("Home =   /home/user")},
            {xT("User = %USER%, Shell = %SHELL%, Home = %HOME%"), xT("User = user, Shell = /bin/bash, Home = /home/user")},
        };
    #endif

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            tString sStr1 = CxEnvironment::sExpandStrings(sData[i][0]);
            tString sStr2 = sData[i][1];
            xASSERT_MSG(sStr1 == sStr2, (sStr1 + xT(" == ") + sStr2).c_str());
        }
    }

    //-------------------------------------
    //bDeleteVar
    {
        const tString sData[][2] = {
            {xT("ENV_TEST_1"), xT("value1")},   //custom
            {xT("ENV_TEST_2"), xT("value2")},   //custom
            {xT("ENV_TEST_3"), xT("value3")},   //custom
            {xT("ENV_TEST_4"), xT("value4")}    //custom
        };

        for (size_t i = 0; i < xARRAY_SIZE(sData); ++ i) {
            BOOL bStr1 = CxEnvironment::bDeleteVar(sData[i][0]);
            xASSERT(FALSE != bStr1);
        }
    }

    //-------------------------------------
    //sGetCommandLine
    {
        m_sRes = CxEnvironment::sGetCommandLine();
        #if defined(xOS_WIN)
        ////xASSERT(CxString::sTrimChars(m_sRes, xT("\"")) == CxPath::sGetExe());
        #elif defined(xOS_LINUX)
        ////xASSERT_MSG(m_sRes == xT("./") + CxPath::sGetFullName(CxPath::sGetExe())/* + xT(" -www")*/, m_sRes.c_str());
        #endif
    }

    //-------------------------------------
    //bGetCommandLineArgs
    {
        m_bRes = CxEnvironment::bGetCommandLineArgs(&m_vecsRes);
        //CxString::vStdVectorPrintT(m_vecsRes);
        xASSERT(FALSE != m_bRes);
    #if defined(xOS_WIN)
        xASSERT_MSG(CxPath::sGetExe()                                  == m_vecsRes.at(0), m_vecsRes.at(0).c_str());
    #elif defined(xOS_LINUX)
        ////////////////////////xASSERT_MSG(xT("./") + CxPath::sGetFullName(CxPath::sGetExe()) == m_vecsRes.at(0), m_vecsRes.at(0).c_str());
    #endif
    }

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxEnvironmentH

