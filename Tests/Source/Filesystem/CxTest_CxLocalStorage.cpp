/**
 * \file   CxTest_CxLocalStorage.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxLocalStorage.h>


//---------------------------------------------------------------------------
CxTest_CxLocalStorage::CxTest_CxLocalStorage() {

}
//---------------------------------------------------------------------------
CxTest_CxLocalStorage::~CxTest_CxLocalStorage() {

}
//---------------------------------------------------------------------------
/*virtual*/
bool
CxTest_CxLocalStorage::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    const std::tstring csFilePath = CxPath::sSetExt( CxPath::sGetExe(), xT("ini") );

    const std::tstring csKey1     = xT("a");
    const std::tstring csValue1   = xT("1");

    const std::tstring csKey2     = xT("b");
    const std::tstring csValue2   = xT("2");

    const std::tstring csKey3     = xT("c");
    const std::tstring csValue3   = xT("3");

    const std::tstring csContent  = csKey1 + CxConst::xEQUAL + csValue1 + CxConst::xNL +
                                    csKey2 + CxConst::xEQUAL + csValue2 + CxConst::xNL +
                                    csKey3 + CxConst::xEQUAL + csValue3 + CxConst::xNL;

    //--------------------------------------------------
    //CxLocalStorage()
    xTEST_CASE(cullBlockLoops)
    {
        CxLocalStorage iniIni;
    }

    //--------------------------------------------------
    //CxLocalStorage(csFilePath)
    CxLocalStorage iniIni(csFilePath);

    /****************************************************************************
    *    creation
    *
    *****************************************************************************/

    //--------------------------------------------------
    //bCreateDefault
    xTEST_CASE(cullBlockLoops)
    {
        m_bRes = iniIni.bCreateDefault(csContent);
        xTEST_DIFF(false, m_bRes);
    }

    //--------------------------------------------------
    //sGetPath
    xTEST_CASE(cullBlockLoops)
    {
        m_sRes = iniIni.sGetPath();
        xTEST_EQ(csFilePath, m_sRes);
    }

    //--------------------------------------------------
    //bSetPath
    xTEST_CASE(cullBlockLoops)
    {
        m_bRes = iniIni.bSetPath(csFilePath);
        xTEST_DIFF(false, m_bRes);

        m_sRes = iniIni.sGetPath();
        xTEST_EQ(csFilePath, m_sRes);
    }

    //--------------------------------------------------
    //cmsGet, bFlush
    xTEST_CASE(cullBlockLoops)
    {
        NxLib::TLocalStorage &riniIni = iniIni.cmsGet();
        xTEST_EQ(true, riniIni.empty());

        riniIni[csKey1] = csValue1;
        riniIni[csKey2] = csValue2;
        riniIni[csKey3] = csValue3;

        m_bRes = iniIni.bFlush();
        xTEST_DIFF(false, m_bRes);

        m_sRes = iniIni.sKeyReadString(csKey1, std::tstring());
        xTEST_EQ(csValue1, m_sRes);

        m_sRes = iniIni.sKeyReadString(csKey2, std::tstring());
        xTEST_EQ(csValue2, m_sRes);

        m_sRes = iniIni.sKeyReadString(csKey3, std::tstring());
        xTEST_EQ(csValue3, m_sRes);

        iniIni.cmsGet().clear();

        m_bRes = iniIni.bFlush();
        xTEST_DIFF(false, m_bRes);
    }

    //--------------------------------------------------
    //bKeyIsExists
    xTEST_CASE(cullBlockLoops)
    {
        NxLib::TLocalStorage &riniIni = iniIni.cmsGet();
        xTEST_EQ(true, riniIni.empty());

        riniIni[csKey1] = csValue1;
        riniIni[csKey2] = csValue2;
        riniIni[csKey3] = csValue3;

        m_bRes = iniIni.bFlush();
        xTEST_DIFF(false, m_bRes);

        //success
        {
            std::vector<std::tstring> vsPairs;

            vsPairs.push_back(csKey1 + CxConst::xEQUAL + csValue1);
            vsPairs.push_back(csKey2 + CxConst::xEQUAL + csValue2);
            vsPairs.push_back(csKey3 + CxConst::xEQUAL + csValue3);

            for (size_t i = 0; i < vsPairs.size(); ++ i) {
                std::vector<std::tstring> vsPair;

                m_bRes = CxString::bSplit(vsPairs.at(i), CxConst::xEQUAL, &vsPair);
                xTEST_DIFF(false, m_bRes);
                xTEST_EQ(false, vsPair.empty());

                m_bRes = iniIni.bKeyIsExists( vsPair.at(0) );
                xTEST_DIFF(false, m_bRes);
            }
        }

        //fail
        {
            std::vector<std::tstring> vsPairs;

            vsPairs.push_back(xT("not_existance_key"));
            vsPairs.push_back(xT("s<erfsenot_existance_key56eb54"));
            vsPairs.push_back(xT("not_exist456745g67ance_key"));
            vsPairs.push_back(xT("563yb675dfgv4g67"));
            vsPairs.push_back(xT("not_exi5g675467stance_key"));

            for (size_t i = 0; i < vsPairs.size(); ++ i) {
                std::vector<std::tstring> vsPair;

                m_bRes = CxString::bSplit(vsPairs.at(i), CxConst::xEQUAL, &vsPair);
                xTEST_DIFF(false, m_bRes);

                m_bRes = iniIni.bKeyIsExists( vsPair.at(0) );
                xTEST_EQ(false, m_bRes);
            }
        }

        iniIni.cmsGet().clear();

        m_bRes = iniIni.bFlush();
        xTEST_DIFF(false, m_bRes);
    }

    //--------------------------------------------------
    //bKeyWriteString, sKeyReadString
    xTEST_CASE(cullBlockLoops)
    {
        //success
        {
            const std::tstring csStr = csValue1;

            m_bRes = iniIni.bKeyWriteString(csKey1, csStr);
            xTEST_DIFF(false, m_bRes);

            m_sRes = iniIni.sKeyReadString(csKey1, std::tstring());
            xTEST_EQ(csStr, m_sRes);
        }

        //fail
        {
            const std::tstring csStr = xT("sssssssssssss");

            m_bRes = iniIni.bKeyWriteString(csKey1, csStr);
            xTEST_DIFF(false, m_bRes);

            m_sRes = iniIni.sKeyReadString(csKey1, std::tstring());
            xTEST_EQ(csStr, m_sRes);
        }
    }

    //--------------------------------------------------
    //iKeyReadInt, bKeyWriteInt
    xTEST_CASE(cullBlockLoops)
    {
        const LONG cliValue = 10L;

        m_bRes  = iniIni.bKeyWriteInt(csKey1, cliValue);
        xTEST_DIFF(false, m_bRes);

        m_liRes = iniIni.iKeyReadInt(csKey1, 0L);
        xTEST_EQ(cliValue, m_liRes);
    }

    //--------------------------------------------------
    //dKeyReadFloat, bKeyWriteFloat
    xTEST_CASE(cullBlockLoops)
    {
        const double cdValue = 777.0f;

        m_bRes  = iniIni.bKeyWriteFloat(csKey1, cdValue);
        xTEST_DIFF(false, m_bRes);

        m_dRes = iniIni.dKeyReadFloat(csKey1, 0.0f);
        xTEST_EQ(cdValue, m_dRes);
    }

    //--------------------------------------------------
    //bKeyReadBool, bKeyWriteBool
    xTEST_CASE(cullBlockLoops)
    {
        const bool cbValue = false;

        m_bRes  = iniIni.bKeyWriteBool(csKey1, cbValue);
        xTEST_DIFF(false, m_bRes);

        m_bRes = iniIni.bKeyReadBool(csKey1, true);
        xTEST_EQ(cbValue, m_bRes);
    }

    //--------------------------------------------------
    //usKeyReadBin, bKeyWriteBin
    xTEST_CASE(cullBlockLoops)
    {
        const std::ustring cusValue(10, 'z');
        const std::ustring cusDefaultValue(10, 'd');

        m_bRes  = iniIni.bKeyWriteBin(csKey1, cusValue);
        xTEST_DIFF(false, m_bRes);

        m_usRes = iniIni.usKeyReadBin(csKey1, cusDefaultValue);
#if xTODO
        xTEST_EQ(cusValue, m_usRes);
#endif
    }

    //--------------------------------------------------
    //bKeyClear
    xTEST_CASE(cullBlockLoops)
    {
        m_bRes = iniIni.bKeyClear(csKey3);
        xTEST_DIFF(false, m_bRes);
        xTEST_DIFF(false, iniIni.bKeyIsExists(csKey3));

        m_sRes = iniIni.sKeyReadString(csKey3, xT("fasrfsefrtg"));
        xTEST_EQ(std::tstring(), m_sRes);
    }

    //--------------------------------------------------
    //bKeyDelete
    xTEST_CASE(cullBlockLoops)
    {
        const std::tstring csKey   = xT("Key");
        const std::tstring csValue = xT("");

        m_bRes = iniIni.bKeyWriteString(csKey, csValue);
        xTEST_DIFF(false, m_bRes);
        xTEST_DIFF(false, iniIni.bKeyIsExists(csKey));

        m_bRes = iniIni.bKeyDelete(csKey);
        xTEST_DIFF(false, m_bRes);
        xTEST_EQ(false, iniIni.bKeyIsExists(csKey));
    }

    //--------------------------------------------------
    //bClear
    xTEST_CASE(cullBlockLoops)
    {
        m_bRes = iniIni.bClear();
        xTEST_DIFF(false, m_bRes);
        xTEST_EQ(0L, CxFile::liGetSize( iniIni.sGetPath() ));
    }

    //--------------------------------------------------
    //bDelete
    xTEST_CASE(cullBlockLoops)
    {
        m_bRes = iniIni.bDelete();
        xTEST_DIFF(false, m_bRes);
        xTEST_EQ(false, CxFile::bIsExists( iniIni.sGetPath() ));
    }

    return true;
}
//---------------------------------------------------------------------------
