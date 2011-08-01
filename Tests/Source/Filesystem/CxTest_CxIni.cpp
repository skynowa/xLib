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
        xASSERT_NOT_EQUAL(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //sGetPath
    {
        m_sRes = iniIni.sGetPath();
        xASSERT_EQUAL(csFilePath, m_sRes);
    }

    //--------------------------------------------------
    //bSetPath
    {
        m_bRes = iniIni.bSetPath(csFilePath);
        xASSERT_NOT_EQUAL(FALSE, m_bRes);

        m_sRes = iniIni.sGetPath();
        xASSERT_EQUAL(csFilePath, m_sRes);
    }

    //--------------------------------------------------
    //cmapsGet, bFlush
    {
        NxLib::TIni &riniIni = iniIni.cmapsGet();
        xASSERT_EQUAL(true, riniIni.empty());

        riniIni[csKey1] = csValue1;
        riniIni[csKey2] = csValue2;
        riniIni[csKey3] = csValue3;

        m_bRes = iniIni.bFlush();
        xASSERT_NOT_EQUAL(FALSE, m_bRes);

        m_sRes = iniIni.sKeyReadString(csKey1, tString());
        xASSERT_EQUAL(csValue1, m_sRes);

        m_sRes = iniIni.sKeyReadString(csKey2, tString());
        xASSERT_EQUAL(csValue2, m_sRes);

        m_sRes = iniIni.sKeyReadString(csKey3, tString());
        xASSERT_EQUAL(csValue3, m_sRes);
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
                xASSERT_NOT_EQUAL(FALSE, m_bRes);
                xASSERT_EQUAL(false, vecsPair.empty());

                m_bRes = iniIni.bKeyIsExists( vecsPair.at(0) );
                xASSERT_NOT_EQUAL(FALSE, m_bRes);
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
                xASSERT_NOT_EQUAL(FALSE, m_bRes);

                m_bRes = iniIni.bKeyIsExists( vecsPair.at(0) );
                xASSERT_EQUAL(FALSE, m_bRes);
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
            xASSERT_NOT_EQUAL(FALSE, m_bRes);

            m_sRes = iniIni.sKeyReadString(csKey1, tString());
            xASSERT_EQUAL(csStr, m_sRes);
        }

        //fail
        {
            const tString csStr = xT("sssssssssssss");

            m_bRes = iniIni.bKeyWriteString(csKey1, csStr);
            xASSERT_NOT_EQUAL(FALSE, m_bRes);

            m_sRes = iniIni.sKeyReadString(csKey1, tString());
            xASSERT_EQUAL(csStr, m_sRes);
        }
    }

    //--------------------------------------------------
    //iKeyReadInt, bKeyWriteInt
    {
        const LONG cliValue = 10L;

        m_bRes  = iniIni.bKeyWriteInt(csKey1, cliValue);
        xASSERT_NOT_EQUAL(FALSE, m_bRes);

        m_liRes = iniIni.iKeyReadInt(csKey1, 0L);
        xASSERT_EQUAL(cliValue, m_liRes);
    }

    //--------------------------------------------------
    //dKeyReadFloat, bKeyWriteFloat
    {
        const DOUBLE cdValue = 777.0f;

        m_bRes  = iniIni.bKeyWriteFloat(csKey1, cdValue);
        xASSERT_NOT_EQUAL(FALSE, m_bRes);

        m_dRes = iniIni.dKeyReadFloat(csKey1, 0.0f);
        xASSERT_EQUAL(cdValue, m_dRes);
    }

    //--------------------------------------------------
    //bKeyReadBool, bKeyWriteBool
    {
        const BOOL cbValue = FALSE;

        m_bRes  = iniIni.bKeyWriteBool(csKey1, cbValue);
        xASSERT_NOT_EQUAL(FALSE, m_bRes);

        m_bRes = iniIni.bKeyReadBool(csKey1, TRUE);
        xASSERT_EQUAL(cbValue, m_bRes);
    }

    //--------------------------------------------------
    //usKeyReadBin, bKeyWriteBin
    {
        const uString cusValue(10, 'z');
        const uString cusDefaultValue(10, 'd');

        m_bRes  = iniIni.bKeyWriteBin(csKey1, cusValue);
        xASSERT_NOT_EQUAL(FALSE, m_bRes);

        m_usRes = iniIni.usKeyReadBin(csKey1, cusDefaultValue);
#if xTODO
        xASSERT_EQUAL(cusValue, m_usRes);
#endif
    }

    //--------------------------------------------------
    //bKeyClear
    {
        m_bRes = iniIni.bKeyClear(csKey3);
        xASSERT_NOT_EQUAL(FALSE, m_bRes);
        xASSERT_NOT_EQUAL(FALSE, iniIni.bKeyIsExists(csKey3));

        m_sRes = iniIni.sKeyReadString(csKey3, xT("fasrfsefrtg"));
        xASSERT_EQUAL(tString(), m_sRes);
    }

    //--------------------------------------------------
    //bKeyDelete
    {
        xASSERT_NOT_EQUAL(FALSE, iniIni.bKeyIsExists(csKey3));
        m_bRes = iniIni.bKeyDelete(csKey3);
        xASSERT_NOT_EQUAL(FALSE, m_bRes);
        xASSERT_EQUAL(FALSE, iniIni.bKeyIsExists(csKey3));
    }

    //--------------------------------------------------
    //bClear
    {
        m_bRes = iniIni.bClear();
        xASSERT_NOT_EQUAL(FALSE, m_bRes);
        xASSERT_EQUAL(0L, CxStdioFile::liGetSize( iniIni.sGetPath() ));
    }

    //--------------------------------------------------
    //bDelete
    {
        m_bRes = iniIni.bDelete();
        xASSERT_NOT_EQUAL(FALSE, m_bRes);
        xASSERT_EQUAL(FALSE, CxStdioFile::bIsExists( iniIni.sGetPath() ));
    }

    return TRUE;
}
//---------------------------------------------------------------------------
