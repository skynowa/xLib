/**
 * \file   CxTest_CxLocalStorage.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxLocalStorage.h>

#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxPath.h>


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
    const ulonglong_t cullCaseLoops
)
{
    const std::tstring_t csFilePath = CxPath::sSetExt( CxPath::sGetExe(), xT("ini") );

    const std::tstring_t csKey1     = xT("a");
    const std::tstring_t csValue1   = xT("1");

    const std::tstring_t csKey2     = xT("b");
    const std::tstring_t csValue2   = xT("2");

    const std::tstring_t csKey3     = xT("c");
    const std::tstring_t csValue3   = xT("3");

    const std::tstring_t csContent  = csKey1 + CxConst::xEQUAL + csValue1 + CxConst::xNL +
                                    csKey2 + CxConst::xEQUAL + csValue2 + CxConst::xNL +
                                    csKey3 + CxConst::xEQUAL + csValue3 + CxConst::xNL;

    //--------------------------------------------------
    //CxLocalStorage()
    xTEST_CASE(cullCaseLoops)
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
    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = iniIni.bCreateDefault(csContent);
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //sGetPath
    xTEST_CASE(cullCaseLoops)
    {
        m_sRes = iniIni.sGetPath();
        xTEST_EQ(csFilePath, m_sRes);
    }

    //--------------------------------------------------
    //bSetPath
    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = iniIni.bSetPath(csFilePath);
        xTEST_EQ(true, m_bRes);

        m_sRes = iniIni.sGetPath();
        xTEST_EQ(csFilePath, m_sRes);
    }

    //--------------------------------------------------
    //cmsGet, bFlush
    xTEST_CASE(cullCaseLoops)
    {
        NxLib::TLocalStorage &riniIni = iniIni.cmsGet();
        xTEST_EQ(true, riniIni.empty());

        riniIni[csKey1] = csValue1;
        riniIni[csKey2] = csValue2;
        riniIni[csKey3] = csValue3;

        m_bRes = iniIni.bFlush();
        xTEST_EQ(true, m_bRes);

        m_sRes = iniIni.sKeyReadString(csKey1, std::tstring_t());
        xTEST_EQ(csValue1, m_sRes);

        m_sRes = iniIni.sKeyReadString(csKey2, std::tstring_t());
        xTEST_EQ(csValue2, m_sRes);

        m_sRes = iniIni.sKeyReadString(csKey3, std::tstring_t());
        xTEST_EQ(csValue3, m_sRes);

        iniIni.cmsGet().clear();

        m_bRes = iniIni.bFlush();
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //bKeyIsExists
    xTEST_CASE(cullCaseLoops)
    {
        NxLib::TLocalStorage &riniIni = iniIni.cmsGet();
        xTEST_EQ(true, riniIni.empty());

        riniIni[csKey1] = csValue1;
        riniIni[csKey2] = csValue2;
        riniIni[csKey3] = csValue3;

        m_bRes = iniIni.bFlush();
        xTEST_EQ(true, m_bRes);

        //success
        {
            std::vector<std::tstring_t> vsPairs;

            vsPairs.push_back(csKey1 + CxConst::xEQUAL + csValue1);
            vsPairs.push_back(csKey2 + CxConst::xEQUAL + csValue2);
            vsPairs.push_back(csKey3 + CxConst::xEQUAL + csValue3);

            for (size_t i = 0; i < vsPairs.size(); ++ i) {
                std::vector<std::tstring_t> vsPair;

                m_bRes = CxString::bSplit(vsPairs.at(i), CxConst::xEQUAL, &vsPair);
                xTEST_EQ(true, m_bRes);
                xTEST_EQ(false, vsPair.empty());

                m_bRes = iniIni.bKeyIsExists( vsPair.at(0) );
                xTEST_EQ(true, m_bRes);
            }
        }

        //fail
        {
            std::vector<std::tstring_t> vsPairs;

            vsPairs.push_back(xT("not_existance_key"));
            vsPairs.push_back(xT("s<erfsenot_existance_key56eb54"));
            vsPairs.push_back(xT("not_exist456745g67ance_key"));
            vsPairs.push_back(xT("563yb675dfgv4g67"));
            vsPairs.push_back(xT("not_exi5g675467stance_key"));

            for (size_t i = 0; i < vsPairs.size(); ++ i) {
                std::vector<std::tstring_t> vsPair;

                m_bRes = CxString::bSplit(vsPairs.at(i), CxConst::xEQUAL, &vsPair);
                xTEST_EQ(true, m_bRes);

                m_bRes = iniIni.bKeyIsExists( vsPair.at(0) );
                xTEST_EQ(false, m_bRes);
            }
        }

        iniIni.cmsGet().clear();

        m_bRes = iniIni.bFlush();
        xTEST_EQ(true, m_bRes);
    }

    //--------------------------------------------------
    //bKeyWriteString, sKeyReadString
    xTEST_CASE(cullCaseLoops)
    {
        //success
        {
            const std::tstring_t csStr = csValue1;

            m_bRes = iniIni.bKeyWriteString(csKey1, csStr);
            xTEST_EQ(true, m_bRes);

            m_sRes = iniIni.sKeyReadString(csKey1, std::tstring_t());
            xTEST_EQ(csStr, m_sRes);
        }

        //fail
        {
            const std::tstring_t csStr = xT("sssssssssssss");

            m_bRes = iniIni.bKeyWriteString(csKey1, csStr);
            xTEST_EQ(true, m_bRes);

            m_sRes = iniIni.sKeyReadString(csKey1, std::tstring_t());
            xTEST_EQ(csStr, m_sRes);
        }
    }

    //--------------------------------------------------
    //iKeyReadInt, bKeyWriteInt
    xTEST_CASE(cullCaseLoops)
    {
        const long_t cliValue = 10L;

        m_bRes  = iniIni.bKeyWriteInt(csKey1, cliValue);
        xTEST_EQ(true, m_bRes);

        m_liRes = iniIni.iKeyReadInt(csKey1, 0L);
        xTEST_EQ(cliValue, m_liRes);
    }

    //--------------------------------------------------
    //dKeyReadFloat, bKeyWriteFloat
    xTEST_CASE(cullCaseLoops)
    {
        const double cdValue = 777.0f;

        m_bRes  = iniIni.bKeyWriteFloat(csKey1, cdValue);
        xTEST_EQ(true, m_bRes);

        m_dRes = iniIni.dKeyReadFloat(csKey1, 0.0f);
        xTEST_EQ(cdValue, m_dRes);
    }

    //--------------------------------------------------
    //bKeyReadBool, bKeyWriteBool
    xTEST_CASE(cullCaseLoops)
    {
        const bool cbValue = false;

        m_bRes  = iniIni.bKeyWriteBool(csKey1, cbValue);
        xTEST_EQ(true, m_bRes);

        m_bRes = iniIni.bKeyReadBool(csKey1, true);
        xTEST_EQ(cbValue, m_bRes);
    }

    //--------------------------------------------------
    //usKeyReadBin, bKeyWriteBin
    xTEST_CASE(cullCaseLoops)
    {
        const std::ustring_t cusValue(10, 'z');
        const std::ustring_t cusDefaultValue(10, 'd');

        m_bRes  = iniIni.bKeyWriteBin(csKey1, cusValue);
        xTEST_EQ(true, m_bRes);

        m_usRes = iniIni.usKeyReadBin(csKey1, cusDefaultValue);
#if xTODO
        xTEST_EQ(cusValue, m_usRes);
#endif
    }

    //--------------------------------------------------
    //bKeyClear
    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = iniIni.bKeyClear(csKey3);
        xTEST_EQ(true, m_bRes);
        xTEST_EQ(true, iniIni.bKeyIsExists(csKey3));

        m_sRes = iniIni.sKeyReadString(csKey3, xT("fasrfsefrtg"));
        xTEST_EQ(CxConst::xSTR_EMPTY, m_sRes);
    }

    //--------------------------------------------------
    //bKeyDelete
    xTEST_CASE(cullCaseLoops)
    {
        const std::tstring_t csKey   = xT("Key");
        const std::tstring_t csValue = xT("");

        m_bRes = iniIni.bKeyWriteString(csKey, csValue);
        xTEST_EQ(true, m_bRes);
        xTEST_EQ(true, iniIni.bKeyIsExists(csKey));

        m_bRes = iniIni.bKeyDelete(csKey);
        xTEST_EQ(true, m_bRes);
        xTEST_EQ(false, iniIni.bKeyIsExists(csKey));
    }

    //--------------------------------------------------
    //bClear
    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = iniIni.bClear();
        xTEST_EQ(true, m_bRes);
        xTEST_EQ(0LL, CxFile::llGetSize( iniIni.sGetPath() ));
    }

    //--------------------------------------------------
    //bDelete
    xTEST_CASE(cullCaseLoops)
    {
        m_bRes = iniIni.bDelete();
        xTEST_EQ(true, m_bRes);
        xTEST_EQ(false, CxFile::bIsExists( iniIni.sGetPath() ));
    }

    return true;
}
//---------------------------------------------------------------------------
