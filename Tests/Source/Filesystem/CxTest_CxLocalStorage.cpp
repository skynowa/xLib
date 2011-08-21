/****************************************************************************
* Class name:  CxTest_CxLocalStorage
* Description: test CxLocalStorage
* File name:   CxLocalStorage.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:
*
*****************************************************************************/


#include <Test/Filesystem/CxTest_CxLocalStorage.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxLocalStorage
CxTest_CxLocalStorage::CxTest_CxLocalStorage() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxLocalStorage
CxTest_CxLocalStorage::~CxTest_CxLocalStorage() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxLocalStorage::bUnit(
    const ULONGLONG cullBlockLoops
)
{
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
    //CxLocalStorage()
    xTEST_BLOCK(cullBlockLoops)
    {
        CxLocalStorage iniIni;
    }

    //--------------------------------------------------
    //CxLocalStorage(csFilePath)
    CxLocalStorage iniIni(csFilePath);

    /****************************************************************************
    *	creation
    *
    *****************************************************************************/

    //--------------------------------------------------
    //bCreateDefault
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = iniIni.bCreateDefault(csContent);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //sGetPath
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = iniIni.sGetPath();
        xASSERT_EQ(csFilePath, m_sRes);
    }

    //--------------------------------------------------
    //bSetPath
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = iniIni.bSetPath(csFilePath);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_sRes = iniIni.sGetPath();
        xASSERT_EQ(csFilePath, m_sRes);
    }

    //--------------------------------------------------
    //cmsGet, bFlush
    xTEST_BLOCK(cullBlockLoops)
    {
        NxLib::TLocalStorage &riniIni = iniIni.cmsGet();
        xASSERT_EQ(true, riniIni.empty());

        riniIni[csKey1] = csValue1;
        riniIni[csKey2] = csValue2;
        riniIni[csKey3] = csValue3;

        m_bRes = iniIni.bFlush();
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_sRes = iniIni.sKeyReadString(csKey1, tString());
        xASSERT_EQ(csValue1, m_sRes);

        m_sRes = iniIni.sKeyReadString(csKey2, tString());
        xASSERT_EQ(csValue2, m_sRes);

        m_sRes = iniIni.sKeyReadString(csKey3, tString());
        xASSERT_EQ(csValue3, m_sRes);

        iniIni.cmsGet().clear();

        m_bRes = iniIni.bFlush();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bKeyIsExists
    xTEST_BLOCK(cullBlockLoops)
    {
        NxLib::TLocalStorage &riniIni = iniIni.cmsGet();
        xASSERT_EQ(true, riniIni.empty());

        riniIni[csKey1] = csValue1;
        riniIni[csKey2] = csValue2;
        riniIni[csKey3] = csValue3;

        m_bRes = iniIni.bFlush();
        xASSERT_NOT_EQ(FALSE, m_bRes);

        //success
        {
            std::vector<tString> vsPairs;

            vsPairs.push_back(csKey1 + CxConst::xEQUAL + csValue1);
            vsPairs.push_back(csKey2 + CxConst::xEQUAL + csValue2);
            vsPairs.push_back(csKey3 + CxConst::xEQUAL + csValue3);

            for (size_t i = 0; i < vsPairs.size(); ++ i) {
                std::vector<tString> vsPair;

                m_bRes = CxString::bSplit(vsPairs.at(i), CxConst::xEQUAL, &vsPair);
                xASSERT_NOT_EQ(FALSE, m_bRes);
                xASSERT_EQ(false, vsPair.empty());

                m_bRes = iniIni.bKeyIsExists( vsPair.at(0) );
                xASSERT_NOT_EQ(FALSE, m_bRes);
            }
        }

        //fail
        {
            std::vector<tString> vsPairs;

            vsPairs.push_back(xT("not_existance_key"));
            vsPairs.push_back(xT("s<erfsenot_existance_key56eb54"));
            vsPairs.push_back(xT("not_exist456745g67ance_key"));
            vsPairs.push_back(xT("563yb675dfgv4g67"));
            vsPairs.push_back(xT("not_exi5g675467stance_key"));

            for (size_t i = 0; i < vsPairs.size(); ++ i) {
                std::vector<tString> vsPair;

                m_bRes = CxString::bSplit(vsPairs.at(i), CxConst::xEQUAL, &vsPair);
                xASSERT_NOT_EQ(FALSE, m_bRes);

                m_bRes = iniIni.bKeyIsExists( vsPair.at(0) );
                xASSERT_EQ(FALSE, m_bRes);
            }
        }

        iniIni.cmsGet().clear();

        m_bRes = iniIni.bFlush();
        xASSERT_NOT_EQ(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bKeyWriteString, sKeyReadString
    xTEST_BLOCK(cullBlockLoops)
    {
        //success
        {
            const tString csStr = csValue1;

            m_bRes = iniIni.bKeyWriteString(csKey1, csStr);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_sRes = iniIni.sKeyReadString(csKey1, tString());
            xASSERT_EQ(csStr, m_sRes);
        }

        //fail
        {
            const tString csStr = xT("sssssssssssss");

            m_bRes = iniIni.bKeyWriteString(csKey1, csStr);
            xASSERT_NOT_EQ(FALSE, m_bRes);

            m_sRes = iniIni.sKeyReadString(csKey1, tString());
            xASSERT_EQ(csStr, m_sRes);
        }
    }

    //--------------------------------------------------
    //iKeyReadInt, bKeyWriteInt
    xTEST_BLOCK(cullBlockLoops)
    {
        const LONG cliValue = 10L;

        m_bRes  = iniIni.bKeyWriteInt(csKey1, cliValue);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_liRes = iniIni.iKeyReadInt(csKey1, 0L);
        xASSERT_EQ(cliValue, m_liRes);
    }

    //--------------------------------------------------
    //dKeyReadFloat, bKeyWriteFloat
    xTEST_BLOCK(cullBlockLoops)
    {
        const DOUBLE cdValue = 777.0f;

        m_bRes  = iniIni.bKeyWriteFloat(csKey1, cdValue);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_dRes = iniIni.dKeyReadFloat(csKey1, 0.0f);
        xASSERT_EQ(cdValue, m_dRes);
    }

    //--------------------------------------------------
    //bKeyReadBool, bKeyWriteBool
    xTEST_BLOCK(cullBlockLoops)
    {
        const BOOL cbValue = FALSE;

        m_bRes  = iniIni.bKeyWriteBool(csKey1, cbValue);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = iniIni.bKeyReadBool(csKey1, TRUE);
        xASSERT_EQ(cbValue, m_bRes);
    }

    //--------------------------------------------------
    //usKeyReadBin, bKeyWriteBin
    xTEST_BLOCK(cullBlockLoops)
    {
        const uString cusValue(10, 'z');
        const uString cusDefaultValue(10, 'd');

        m_bRes  = iniIni.bKeyWriteBin(csKey1, cusValue);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_usRes = iniIni.usKeyReadBin(csKey1, cusDefaultValue);
#if xTODO
        xASSERT_EQ(cusValue, m_usRes);
#endif
    }

    //--------------------------------------------------
    //bKeyClear
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = iniIni.bKeyClear(csKey3);
        xASSERT_NOT_EQ(FALSE, m_bRes);
        xASSERT_NOT_EQ(FALSE, iniIni.bKeyIsExists(csKey3));

        m_sRes = iniIni.sKeyReadString(csKey3, xT("fasrfsefrtg"));
        xASSERT_EQ(tString(), m_sRes);
    }

    //--------------------------------------------------
    //bKeyDelete
    xTEST_BLOCK(cullBlockLoops)
    {
        const tString csKey   = xT("Key");
        const tString csValue = xT("");

        m_bRes = iniIni.bKeyWriteString(csKey, csValue);
        xASSERT_NOT_EQ(FALSE, m_bRes);
        xASSERT_NOT_EQ(FALSE, iniIni.bKeyIsExists(csKey));

        m_bRes = iniIni.bKeyDelete(csKey);
        xASSERT_NOT_EQ(FALSE, m_bRes);
        xASSERT_EQ(FALSE, iniIni.bKeyIsExists(csKey));
    }

    //--------------------------------------------------
    //bClear
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = iniIni.bClear();
        xASSERT_NOT_EQ(FALSE, m_bRes);
        xASSERT_EQ(0L, CxStdioFile::liGetSize( iniIni.sGetPath() ));
    }

    //--------------------------------------------------
    //bDelete
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = iniIni.bDelete();
        xASSERT_NOT_EQ(FALSE, m_bRes);
        xASSERT_EQ(FALSE, CxStdioFile::bIsExists( iniIni.sGetPath() ));
    }

    return TRUE;
}
//---------------------------------------------------------------------------
