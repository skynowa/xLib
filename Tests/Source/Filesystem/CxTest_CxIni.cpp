/****************************************************************************
* Class name:  CxTest_CxIni
* Description: test CxIni
* File name:   CxIni.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:
*
*****************************************************************************/


#include <Test/Filesystem/CxTest_CxIni.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxIni
CxTest_CxIni::CxTest_CxIni() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxIni
CxTest_CxIni::~CxTest_CxIni() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
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

    //--------------------------------------------------
    //CxIni()
    {
        CxIni iniIni;
    }

    //--------------------------------------------------
    //CxIni(csFilePath)
    CxIni iniIni(csFilePath);

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
    //cmapsGet, bFlush
    {
        NxLib::TIni &riniIni = iniIni.cmapsGet();
        xASSERT(true == riniIni.empty());

        riniIni[csKey1] = csValue1;
        riniIni[csKey2] = csValue2;
        riniIni[csKey3] = csValue3;

        m_bRes = iniIni.bFlush();
        xASSERT(FALSE != m_bRes);

        m_sRes = iniIni.sKeyReadString(csKey1, tString());
        xASSERT(csValue1 == m_sRes);

        m_sRes = iniIni.sKeyReadString(csKey2, tString());
        xASSERT(csValue2 == m_sRes);

        m_sRes = iniIni.sKeyReadString(csKey3, tString());
        xASSERT(csValue3 == m_sRes);
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
                xASSERT(false == vecsPair.empty());

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
        }

        //fail
        {
            const tString csStr = xT("sssssssssssss");

            m_bRes = iniIni.bKeyWriteString(csKey1, csStr);
            xASSERT(FALSE != m_bRes);

            m_sRes = iniIni.sKeyReadString(csKey1, tString());
            xASSERT(csStr == m_sRes);
        }
    }

    //--------------------------------------------------
    //iKeyReadInt, bKeyWriteInt
    {
        const LONG cliValue = 10L;

        m_bRes  = iniIni.bKeyWriteInt(csKey1, cliValue);
        xASSERT(FALSE != m_bRes);

        m_liRes = iniIni.iKeyReadInt(csKey1, 0L);
        xASSERT(cliValue == m_liRes);
    }

    //--------------------------------------------------
    //dKeyReadFloat, bKeyWriteFloat
    {
        const DOUBLE cdValue = 777.0f;

        m_bRes  = iniIni.bKeyWriteFloat(csKey1, cdValue);
        xASSERT(FALSE != m_bRes);

        m_dRes = iniIni.dKeyReadFloat(csKey1, 0.0f);
        xASSERT(cdValue == m_dRes);
    }

    //--------------------------------------------------
    //bKeyReadBool, bKeyWriteBool
    {
        const BOOL cbValue = FALSE;

        m_bRes  = iniIni.bKeyWriteBool(csKey1, cbValue);
        xASSERT(FALSE != m_bRes);

        m_bRes = iniIni.bKeyReadBool(csKey1, TRUE);
        xASSERT(cbValue == m_bRes);
    }

    //--------------------------------------------------
    //usKeyReadBin, bKeyWriteBin
    {
        const uString cusValue(10, 'z');
        const uString cusDefaultValue(10, 'd');

        m_bRes  = iniIni.bKeyWriteBin(csKey1, cusValue);
        xASSERT(FALSE != m_bRes);

        m_usRes = iniIni.usKeyReadBin(csKey1, cusDefaultValue);
        xASSERT(cusValue == m_usRes);
    }

    //--------------------------------------------------
    //bKeyClear
    {
        m_bRes = iniIni.bKeyClear(csKey3);
        xASSERT(FALSE != m_bRes);
        xASSERT(FALSE != iniIni.bKeyIsExists(csKey3));

        m_sRes = iniIni.sKeyReadString(csKey3, xT("fasrfsefrtg"));
        xASSERT(tString() == m_sRes);
    }

    //--------------------------------------------------
    //bKeyDelete
    {
        xASSERT(FALSE != iniIni.bKeyIsExists(csKey3));
        m_bRes = iniIni.bKeyDelete(csKey3);
        xASSERT(FALSE != m_bRes);
        xASSERT(FALSE == iniIni.bKeyIsExists(csKey3));
    }

    //--------------------------------------------------
    //bClear
    {
        m_bRes = iniIni.bClear();
        xASSERT(FALSE != m_bRes);
        xASSERT(CxStdioFile::liGetSize( iniIni.sGetPath() ) == 0);
    }

    //--------------------------------------------------
    //bDelete
    {
        m_bRes = iniIni.bDelete();
        xASSERT(FALSE != m_bRes);
        xASSERT(CxStdioFile::bIsExists( iniIni.sGetPath() ) == FALSE);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
