/****************************************************************************
* Class name:  CxTest_CxIni
* Description: test CxIni
* File name:   CxIni.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:
*
*****************************************************************************/


#ifndef CxTest_CxIniH
#define CxTest_CxIniH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/CxIni.h>
//---------------------------------------------------------------------------
class CxTest_CxIni : public CxTest {
	public:
		         CxTest_CxIni();
	    virtual ~CxTest_CxIni();

	    virtual  BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//DONE: CxTest_CxIni (constructor)
CxTest_CxIni::CxTest_CxIni() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxIni (destructor)
CxTest_CxIni::~CxTest_CxIni() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxIni::bUnit() {
    const tString csFilePath = CxPath::sSetExt( CxPath::sGetExe(), xT("ini") );

    const tString csKey1   = xT("a");
    const tString csValue1 = xT("1");

    const tString csKey2   = xT("b");
    const tString csValue2 = xT("2");

    const tString csKey3   = xT("c");
    const tString csValue3 = xT("3");



    const tString csContent = csKey1 + CxConst::xEQUAL + csValue1 + CxConst::xNL +
                              csKey2 + CxConst::xEQUAL + csValue2 + CxConst::xNL +
                              csKey3 + CxConst::xEQUAL + csValue3 + CxConst::xNL;
    xTRACE(csContent);

    CxIni iniIni;
    //CxIni             (const tString &csFilePath);

    /****************************************************************************
    *	creation
    *
    *****************************************************************************/

    //--------------------------------------------------
    //bCreateDefault
    {
        m_bRes = iniIni.bCreateDefault(csContent);
        xASSERT(FALSE != m_bRes);
    }

    //--------------------------------------------------
    //sGetPath
    {
        m_sRes = iniIni.sGetPath();
        xASSERT(csFilePath == m_sRes);
    }

    //--------------------------------------------------
    //bSetPath
    {
        m_bRes = iniIni.bSetPath(csFilePath);
        xASSERT(FALSE != m_bRes);

        m_sRes = iniIni.sGetPath();
        xASSERT(csFilePath == m_sRes);
    }

    //--------------------------------------------------
    //bKeyIsExists
    {
        //success
        {
            std::vector<tString> vecsPairs;

            vecsPairs.push_back(csKey1 + CxConst::xEQUAL + csValue1);
            vecsPairs.push_back(csKey2 + CxConst::xEQUAL + csValue2);
            vecsPairs.push_back(csKey3 + CxConst::xEQUAL + csValue3);

            for (size_t i = 0; i < vecsPairs.size(); ++ i) {
                std::vector<tString> vecsPair;

                m_bRes = CxString::bSplit(vecsPairs.at(i), CxConst::xEQUAL, &vecsPair);
                xASSERT(FALSE != m_bRes);

                m_bRes = iniIni.bKeyIsExists( vecsPair.at(0) );
                xASSERT(FALSE != m_bRes);
            }
        }

        //fail
        {
            std::vector<tString> vecsPairs;

            vecsPairs.push_back(xT("not_existance_key"));
            vecsPairs.push_back(xT("s<erfsenot_existance_key56eb54"));
            vecsPairs.push_back(xT("not_exist456745g67ance_key"));
            vecsPairs.push_back(xT("563yb675dfgv4g67"));
            vecsPairs.push_back(xT("not_exi5g675467stance_key"));

            for (size_t i = 0; i < vecsPairs.size(); ++ i) {
                std::vector<tString> vecsPair;

                m_bRes = CxString::bSplit(vecsPairs.at(i), CxConst::xEQUAL, &vecsPair);
                xASSERT(FALSE != m_bRes);

                m_bRes = iniIni.bKeyIsExists( vecsPair.at(0) );
                xASSERT(FALSE == m_bRes);
            }
        }
    }

    //--------------------------------------------------
    //bKeyWriteString, sKeyReadString
    {
        //success
        {
            const tString csStr = csValue1;

            m_bRes = iniIni.bKeyWriteString(csKey1, csStr);
            xASSERT(FALSE != m_bRes);

            m_sRes = iniIni.sKeyReadString(csKey1, tString());
            xASSERT(csStr == m_sRes);

            //rollback csKey1, csValue1
            m_bRes = iniIni.bKeyWriteString(csKey1, csValue1);
            xASSERT(FALSE != m_bRes);

            m_sRes = iniIni.sKeyReadString(csKey1, tString());
            xASSERT(csValue1 == m_sRes);
        }

        //fail
        {
            const tString csStr = xT("sssssssssssss");

            m_bRes = iniIni.bKeyWriteString(csKey1, csStr);
            xASSERT(FALSE != m_bRes);

            m_sRes = iniIni.sKeyReadString(csKey1, tString());
            xASSERT(csStr == m_sRes);

            //rollback csKey1, csValue1
            m_bRes = iniIni.bKeyWriteString(csKey1, csValue1);
            xASSERT(FALSE != m_bRes);

            m_sRes = iniIni.sKeyReadString(csKey1, tString());
            xASSERT(csValue1 == m_sRes);
        }
    }
















    //--------------------------------------------------
    //bClear
    {
        m_bRes = iniIni.bClear();
        xASSERT(FALSE != m_bRes);
        xASSERT(CxStdioFile::liGetSize( iniIni.sGetPath() ) == 0);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxIniH
