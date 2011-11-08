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
CxTest_CxLocalStorage::CxTest_CxLocalStorage() {

}
//---------------------------------------------------------------------------
CxTest_CxLocalStorage::~CxTest_CxLocalStorage() {

}
//---------------------------------------------------------------------------
/*virtual*/
BOOL
CxTest_CxLocalStorage::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    const std::string_t csFilePath = CxPath::sSetExt( CxPath::sGetExe(), xT("ini") );

    const std::string_t csKey1     = xT("a");
    const std::string_t csValue1   = xT("1");

    const std::string_t csKey2     = xT("b");
    const std::string_t csValue2   = xT("2");

    const std::string_t csKey3     = xT("c");
    const std::string_t csValue3   = xT("3");

    const std::string_t csContent  = csKey1 + CxConst::xEQUAL + csValue1 + CxConst::xNL +
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
        xTEST_DIFF(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //sGetPath
    xTEST_BLOCK(cullBlockLoops)
    {
        m_sRes = iniIni.sGetPath();
        xTEST_EQ(csFilePath, m_sRes);
    }

    //--------------------------------------------------
    //bSetPath
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = iniIni.bSetPath(csFilePath);
        xTEST_DIFF(FALSE, m_bRes);

        m_sRes = iniIni.sGetPath();
        xTEST_EQ(csFilePath, m_sRes);
    }

    //--------------------------------------------------
    //cmsGet, bFlush
    xTEST_BLOCK(cullBlockLoops)
    {
        NxLib::TLocalStorage &riniIni = iniIni.cmsGet();
        xTEST_EQ(true, riniIni.empty());

        riniIni[csKey1] = csValue1;
        riniIni[csKey2] = csValue2;
        riniIni[csKey3] = csValue3;

        m_bRes = iniIni.bFlush();
        xTEST_DIFF(FALSE, m_bRes);

        m_sRes = iniIni.sKeyReadString(csKey1, std::string_t());
        xTEST_EQ(csValue1, m_sRes);

        m_sRes = iniIni.sKeyReadString(csKey2, std::string_t());
        xTEST_EQ(csValue2, m_sRes);

        m_sRes = iniIni.sKeyReadString(csKey3, std::string_t());
        xTEST_EQ(csValue3, m_sRes);

        iniIni.cmsGet().clear();

        m_bRes = iniIni.bFlush();
        xTEST_DIFF(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bKeyIsExists
    xTEST_BLOCK(cullBlockLoops)
    {
        NxLib::TLocalStorage &riniIni = iniIni.cmsGet();
        xTEST_EQ(true, riniIni.empty());

        riniIni[csKey1] = csValue1;
        riniIni[csKey2] = csValue2;
        riniIni[csKey3] = csValue3;

        m_bRes = iniIni.bFlush();
        xTEST_DIFF(FALSE, m_bRes);

        //success
        {
            std::vector<std::string_t> vsPairs;

            vsPairs.push_back(csKey1 + CxConst::xEQUAL + csValue1);
            vsPairs.push_back(csKey2 + CxConst::xEQUAL + csValue2);
            vsPairs.push_back(csKey3 + CxConst::xEQUAL + csValue3);

            for (size_t i = 0; i < vsPairs.size(); ++ i) {
                std::vector<std::string_t> vsPair;

                m_bRes = CxString::bSplit(vsPairs.at(i), CxConst::xEQUAL, &vsPair);
                xTEST_DIFF(FALSE, m_bRes);
                xTEST_EQ(false, vsPair.empty());

                m_bRes = iniIni.bKeyIsExists( vsPair.at(0) );
                xTEST_DIFF(FALSE, m_bRes);
            }
        }

        //fail
        {
            std::vector<std::string_t> vsPairs;

            vsPairs.push_back(xT("not_existance_key"));
            vsPairs.push_back(xT("s<erfsenot_existance_key56eb54"));
            vsPairs.push_back(xT("not_exist456745g67ance_key"));
            vsPairs.push_back(xT("563yb675dfgv4g67"));
            vsPairs.push_back(xT("not_exi5g675467stance_key"));

            for (size_t i = 0; i < vsPairs.size(); ++ i) {
                std::vector<std::string_t> vsPair;

                m_bRes = CxString::bSplit(vsPairs.at(i), CxConst::xEQUAL, &vsPair);
                xTEST_DIFF(FALSE, m_bRes);

                m_bRes = iniIni.bKeyIsExists( vsPair.at(0) );
                xTEST_EQ(FALSE, m_bRes);
            }
        }

        iniIni.cmsGet().clear();

        m_bRes = iniIni.bFlush();
        xTEST_DIFF(FALSE, m_bRes);
    }

    //--------------------------------------------------
    //bKeyWriteString, sKeyReadString
    xTEST_BLOCK(cullBlockLoops)
    {
        //success
        {
            const std::string_t csStr = csValue1;

            m_bRes = iniIni.bKeyWriteString(csKey1, csStr);
            xTEST_DIFF(FALSE, m_bRes);

            m_sRes = iniIni.sKeyReadString(csKey1, std::string_t());
            xTEST_EQ(csStr, m_sRes);
        }

        //fail
        {
            const std::string_t csStr = xT("sssssssssssss");

            m_bRes = iniIni.bKeyWriteString(csKey1, csStr);
            xTEST_DIFF(FALSE, m_bRes);

            m_sRes = iniIni.sKeyReadString(csKey1, std::string_t());
            xTEST_EQ(csStr, m_sRes);
        }
    }

    //--------------------------------------------------
    //iKeyReadInt, bKeyWriteInt
    xTEST_BLOCK(cullBlockLoops)
    {
        const LONG cliValue = 10L;

        m_bRes  = iniIni.bKeyWriteInt(csKey1, cliValue);
        xTEST_DIFF(FALSE, m_bRes);

        m_liRes = iniIni.iKeyReadInt(csKey1, 0L);
        xTEST_EQ(cliValue, m_liRes);
    }

    //--------------------------------------------------
    //dKeyReadFloat, bKeyWriteFloat
    xTEST_BLOCK(cullBlockLoops)
    {
        const double cdValue = 777.0f;

        m_bRes  = iniIni.bKeyWriteFloat(csKey1, cdValue);
        xTEST_DIFF(FALSE, m_bRes);

        m_dRes = iniIni.dKeyReadFloat(csKey1, 0.0f);
        xTEST_EQ(cdValue, m_dRes);
    }

    //--------------------------------------------------
    //bKeyReadBool, bKeyWriteBool
    xTEST_BLOCK(cullBlockLoops)
    {
        const BOOL cbValue = FALSE;

        m_bRes  = iniIni.bKeyWriteBool(csKey1, cbValue);
        xTEST_DIFF(FALSE, m_bRes);

        m_bRes = iniIni.bKeyReadBool(csKey1, TRUE);
        xTEST_EQ(cbValue, m_bRes);
    }

    //--------------------------------------------------
    //usKeyReadBin, bKeyWriteBin
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::ustring cusValue(10, 'z');
        const std::ustring cusDefaultValue(10, 'd');

        m_bRes  = iniIni.bKeyWriteBin(csKey1, cusValue);
        xTEST_DIFF(FALSE, m_bRes);

        m_usRes = iniIni.usKeyReadBin(csKey1, cusDefaultValue);
#if xTODO
        xTEST_EQ(cusValue, m_usRes);
#endif
    }

    //--------------------------------------------------
    //bKeyClear
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = iniIni.bKeyClear(csKey3);
        xTEST_DIFF(FALSE, m_bRes);
        xTEST_DIFF(FALSE, iniIni.bKeyIsExists(csKey3));

        m_sRes = iniIni.sKeyReadString(csKey3, xT("fasrfsefrtg"));
        xTEST_EQ(std::string_t(), m_sRes);
    }

    //--------------------------------------------------
    //bKeyDelete
    xTEST_BLOCK(cullBlockLoops)
    {
        const std::string_t csKey   = xT("Key");
        const std::string_t csValue = xT("");

        m_bRes = iniIni.bKeyWriteString(csKey, csValue);
        xTEST_DIFF(FALSE, m_bRes);
        xTEST_DIFF(FALSE, iniIni.bKeyIsExists(csKey));

        m_bRes = iniIni.bKeyDelete(csKey);
        xTEST_DIFF(FALSE, m_bRes);
        xTEST_EQ(FALSE, iniIni.bKeyIsExists(csKey));
    }

    //--------------------------------------------------
    //bClear
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = iniIni.bClear();
        xTEST_DIFF(FALSE, m_bRes);
        xTEST_EQ(0L, CxFile::liGetSize( iniIni.sGetPath() ));
    }

    //--------------------------------------------------
    //bDelete
    xTEST_BLOCK(cullBlockLoops)
    {
        m_bRes = iniIni.bDelete();
        xTEST_DIFF(FALSE, m_bRes);
        xTEST_EQ(FALSE, CxFile::bIsExists( iniIni.sGetPath() ));
    }

    return TRUE;
}
//---------------------------------------------------------------------------
