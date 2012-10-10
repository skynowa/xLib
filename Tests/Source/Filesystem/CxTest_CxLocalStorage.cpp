/**
 * \file   CxTest_CxLocalStorage.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxLocalStorage.h>

#include <xLib/Common/CxConst.h>
#include <xLib/Common/CxString.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxPath.h>


//---------------------------------------------------------------------------
CxTest_CxLocalStorage::CxTest_CxLocalStorage() {

}
//---------------------------------------------------------------------------
CxTest_CxLocalStorage::~CxTest_CxLocalStorage() {

}
//---------------------------------------------------------------------------
/* virtual */
void
CxTest_CxLocalStorage::vUnit(
    const ulonglong_t &cullCaseLoops
)
{
    const std::tstring_t csFilePath = CxPath::sSetExt( CxPath::sExe(), xT("ini") );

    const std::tstring_t csKey1     = xT("a");
    const std::tstring_t csValue1   = xT("1");

    const std::tstring_t csKey2     = xT("b");
    const std::tstring_t csValue2   = xT("2");

    const std::tstring_t csKey3     = xT("c");
    const std::tstring_t csValue3   = xT("3");

    const std::tstring_t csContent  = csKey1 + CxConst::xEQUAL + csValue1 + CxConst::xNL +
                                      csKey2 + CxConst::xEQUAL + csValue2 + CxConst::xNL +
                                      csKey3 + CxConst::xEQUAL + csValue3 + CxConst::xNL;

    xTEST_CASE(CxLocalStorage::CxLocalStorage, cullCaseLoops)
    {
        CxLocalStorage iniIni;
    }


    CxFile::vDelete(csFilePath);

    CxLocalStorage iniIni(csFilePath);

    /****************************************************************************
    *    creation
    *
    *****************************************************************************/

    xTEST_CASE(CxLocalStorage::vCreateDefault, cullCaseLoops)
    {
        iniIni.vCreateDefault(csContent);
    }

    xTEST_CASE(CxLocalStorage::sGetPath, cullCaseLoops)
    {
        m_sRv = iniIni.sPath();
        xTEST_EQ(csFilePath, m_sRv);
    }

    xTEST_CASE(CxLocalStorage::vSetPath, cullCaseLoops)
    {
        iniIni.vSetPath(csFilePath);

        m_sRv = iniIni.sPath();
        xTEST_EQ(csFilePath, m_sRv);
    }

    xTEST_CASE(CxLocalStorage::cmsGet CxLocalStorage::vFlush, cullCaseLoops)
    {
        TLocalStorage &riniIni = iniIni.cmsGet();
        xTEST_EQ(true, riniIni.empty());

        riniIni[csKey1] = csValue1;
        riniIni[csKey2] = csValue2;
        riniIni[csKey3] = csValue3;

        iniIni.vFlush();

        m_sRv = iniIni.sKeyReadString(csKey1, std::tstring_t());
        xTEST_EQ(csValue1, m_sRv);

        m_sRv = iniIni.sKeyReadString(csKey2, std::tstring_t());
        xTEST_EQ(csValue2, m_sRv);

        m_sRv = iniIni.sKeyReadString(csKey3, std::tstring_t());
        xTEST_EQ(csValue3, m_sRv);

        iniIni.cmsGet().clear();

        iniIni.vFlush();
    }

    xTEST_CASE(CxLocalStorage::bKeyIsExists, cullCaseLoops)
    {
        TLocalStorage &riniIni = iniIni.cmsGet();
        xTEST_EQ(true, riniIni.empty());

        riniIni[csKey1] = csValue1;
        riniIni[csKey2] = csValue2;
        riniIni[csKey3] = csValue3;

        iniIni.vFlush();

        //success
        {
            std::vec_tstring_t vsPairs;

            vsPairs.push_back(csKey1 + CxConst::xEQUAL + csValue1);
            vsPairs.push_back(csKey2 + CxConst::xEQUAL + csValue2);
            vsPairs.push_back(csKey3 + CxConst::xEQUAL + csValue3);

            for (size_t i = 0; i < vsPairs.size(); ++ i) {
                std::vec_tstring_t vsPair;

                CxString::vSplit(vsPairs.at(i), CxConst::xEQUAL, &vsPair);
                xTEST_EQ(false, vsPair.empty());

                m_bRv = iniIni.bKeyIsExists( vsPair.at(0) );
                xTEST_EQ(true, m_bRv);
            }
        }

        //fail
        {
            std::vec_tstring_t vsPairs;

            vsPairs.push_back(xT("not_existance_key"));
            vsPairs.push_back(xT("s<erfsenot_existance_key56eb54"));
            vsPairs.push_back(xT("not_exist456745g67ance_key"));
            vsPairs.push_back(xT("563yb675dfgv4g67"));
            vsPairs.push_back(xT("not_exi5g675467stance_key"));

            for (size_t i = 0; i < vsPairs.size(); ++ i) {
                std::vec_tstring_t vsPair;

                 CxString::vSplit(vsPairs.at(i), CxConst::xEQUAL, &vsPair);

                m_bRv = iniIni.bKeyIsExists( vsPair.at(0) );
                xTEST_EQ(false, m_bRv);
            }
        }

        iniIni.cmsGet().clear();

        iniIni.vFlush();
    }

    xTEST_CASE(CxLocalStorage::vKeyWriteString CxLocalStorage::sKeyReadString, cullCaseLoops)
    {
        //success
        {
            const std::tstring_t csStr = csValue1;

            iniIni.vKeyWriteString(csKey1, csStr);

            m_sRv = iniIni.sKeyReadString(csKey1, std::tstring_t());
            xTEST_EQ(csStr, m_sRv);
        }

        //fail
        {
            const std::tstring_t csStr = xT("sssssssssssss");

            iniIni.vKeyWriteString(csKey1, csStr);

            m_sRv = iniIni.sKeyReadString(csKey1, std::tstring_t());
            xTEST_EQ(csStr, m_sRv);
        }
    }

    xTEST_CASE(CxLocalStorage::iKeyReadInt CxLocalStorage::vKeyWriteInt, cullCaseLoops)
    {
        const long_t cliValue = 10L;

        iniIni.vKeyWriteInt(csKey1, cliValue);

        m_liRv = iniIni.iKeyReadInt(csKey1, 0L);
        xTEST_EQ(cliValue, m_liRv);
    }

    xTEST_CASE(CxLocalStorage::dKeyReadFloat CxLocalStorage::vKeyWriteFloat, cullCaseLoops)
    {
        const double cdValue = 777.0f;

        iniIni.vKeyWriteFloat(csKey1, cdValue);

        m_dRv = iniIni.dKeyReadFloat(csKey1, 0.0f);
        xTEST_EQ(cdValue, m_dRv);
    }

    xTEST_CASE(CxLocalStorage::bKeyReadBool CxLocalStorage::vKeyWriteBool, cullCaseLoops)
    {
        const bool cbValue = false;

        iniIni.vKeyWriteBool(csKey1, cbValue);

        m_bRv = iniIni.bKeyReadBool(csKey1, true);
        xTEST_EQ(cbValue, m_bRv);
    }

    xTEST_CASE(CxLocalStorage::vKeyWriteBin CxLocalStorage::usKeyReadBin, cullCaseLoops)
    {
        const std::ustring_t cusValue(10, 'z');
        const std::ustring_t cusDefaultValue(10, 'd');

        iniIni.vKeyWriteBin(csKey1, cusValue);

        m_usRv = iniIni.usKeyReadBin(csKey1, cusDefaultValue);
#if xTODO
        xTEST_EQ(cusValue, m_usRv);
#endif
    }

    xTEST_CASE(CxLocalStorage::vKeyClear, cullCaseLoops)
    {
        iniIni.vKeyClear(csKey3);
        xTEST_EQ(true, iniIni.bKeyIsExists(csKey3));

        m_sRv = iniIni.sKeyReadString(csKey3, xT("fasrfsefrtg"));
        xTEST_EQ(CxConst::xSTR_EMPTY, m_sRv);
    }

    xTEST_CASE(CxLocalStorage::vKeyDelete, cullCaseLoops)
    {
        const std::tstring_t csKey   = xT("Key");
        const std::tstring_t csValue = xT("");

        iniIni.vKeyWriteString(csKey, csValue);
        xTEST_EQ(true, iniIni.bKeyIsExists(csKey));

        iniIni.vKeyDelete(csKey);
        xTEST_EQ(false, iniIni.bKeyIsExists(csKey));
    }

    xTEST_CASE(CxLocalStorage::vClear, cullCaseLoops)
    {
        iniIni.vClear();
        xTEST_EQ(0LL, CxFile::llSize( iniIni.sPath() ));
    }

    xTEST_CASE(CxLocalStorage::vDelete, cullCaseLoops)
    {
        iniIni.vDelete();
        xTEST_EQ(false, CxFile::bIsExists( iniIni.sPath() ));
    }
}
//---------------------------------------------------------------------------
