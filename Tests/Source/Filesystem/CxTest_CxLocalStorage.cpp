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
CxTest_CxLocalStorage::unit(
    const ulonglong_t &cullCaseLoops
)
{
    const std::tstring_t csFilePath = CxPath( CxPath::exe() ).setExt(xT("ini") );

    const std::tstring_t csKey1     = xT("a");
    const std::tstring_t csValue1   = xT("1");

    const std::tstring_t csKey2     = xT("b");
    const std::tstring_t csValue2   = xT("2");

    const std::tstring_t csKey3     = xT("c");
    const std::tstring_t csValue3   = xT("3");

    const std::tstring_t csContent  = csKey1 + CxConst::xEQUAL + csValue1 + CxConst::xNL +
                                      csKey2 + CxConst::xEQUAL + csValue2 + CxConst::xNL +
                                      csKey3 + CxConst::xEQUAL + csValue3 + CxConst::xNL;

    xTEST_CASE("CxLocalStorage::CxLocalStorage", cullCaseLoops)
    {
        CxLocalStorage iniIni;
    }

    CxFile::remove(csFilePath);

    CxLocalStorage iniIni(csFilePath);

    xTEST_CASE("CxLocalStorage::createDefault", cullCaseLoops)
    {
        iniIni.createDefault(csContent);
    }

    xTEST_CASE("CxLocalStorage::path", cullCaseLoops)
    {
        m_sRv = iniIni.path();
        xTEST_EQ(csFilePath, m_sRv);
    }

    xTEST_CASE("CxLocalStorage::setPath", cullCaseLoops)
    {
        iniIni.setPath(csFilePath);

        m_sRv = iniIni.path();
        xTEST_EQ(csFilePath, m_sRv);
    }

    xTEST_CASE("CxLocalStorage::get CxLocalStorage::flush", cullCaseLoops)
    {
        local_storage_t &riniIni = iniIni.get();
        xTEST_EQ(true, riniIni.empty());

        riniIni[csKey1] = csValue1;
        riniIni[csKey2] = csValue2;
        riniIni[csKey3] = csValue3;

        iniIni.flush();

        m_sRv = iniIni.keyReadString(csKey1, std::tstring_t());
        xTEST_EQ(csValue1, m_sRv);

        m_sRv = iniIni.keyReadString(csKey2, std::tstring_t());
        xTEST_EQ(csValue2, m_sRv);

        m_sRv = iniIni.keyReadString(csKey3, std::tstring_t());
        xTEST_EQ(csValue3, m_sRv);

        iniIni.get().clear();

        iniIni.flush();
    }

    xTEST_CASE("CxLocalStorage::keyIsExists", cullCaseLoops)
    {
        local_storage_t &riniIni = iniIni.get();
        xTEST_EQ(true, riniIni.empty());

        riniIni[csKey1] = csValue1;
        riniIni[csKey2] = csValue2;
        riniIni[csKey3] = csValue3;

        iniIni.flush();

        // true
        {
            std::vec_tstring_t vsPairs;

            vsPairs.push_back(csKey1 + CxConst::xEQUAL + csValue1);
            vsPairs.push_back(csKey2 + CxConst::xEQUAL + csValue2);
            vsPairs.push_back(csKey3 + CxConst::xEQUAL + csValue3);

            for (size_t i = 0; i < vsPairs.size(); ++ i) {
                std::vec_tstring_t vsPair;

                CxString::split(vsPairs.at(i), CxConst::xEQUAL, &vsPair);
                xTEST_EQ(false, vsPair.empty());

                m_bRv = iniIni.keyIsExists( vsPair.at(0) );
                xTEST_EQ(true, m_bRv);
            }
        }

        // false
        {
            std::vec_tstring_t vsPairs;

            vsPairs.push_back(xT("not_existance_key"));
            vsPairs.push_back(xT("s<erfsenot_existance_key56eb54"));
            vsPairs.push_back(xT("not_exist456745g67ance_key"));
            vsPairs.push_back(xT("563yb675dfgv4g67"));
            vsPairs.push_back(xT("not_exi5g675467stance_key"));

            for (size_t i = 0; i < vsPairs.size(); ++ i) {
                std::vec_tstring_t vsPair;

                 CxString::split(vsPairs.at(i), CxConst::xEQUAL, &vsPair);

                m_bRv = iniIni.keyIsExists( vsPair.at(0) );
                xTEST_EQ(false, m_bRv);
            }
        }

        iniIni.get().clear();

        iniIni.flush();
    }

    xTEST_CASE("CxLocalStorage::keyWriteString CxLocalStorage::keyReadString", cullCaseLoops)
    {
        // true
        {
            const std::tstring_t csStr = csValue1;

            iniIni.keyWriteString(csKey1, csStr);

            m_sRv = iniIni.keyReadString(csKey1, std::tstring_t());
            xTEST_EQ(csStr, m_sRv);
        }

        // false
        {
            const std::tstring_t csStr = xT("sssssssssssss");

            iniIni.keyWriteString(csKey1, csStr);

            m_sRv = iniIni.keyReadString(csKey1, std::tstring_t());
            xTEST_EQ(csStr, m_sRv);
        }
    }

    xTEST_CASE("CxLocalStorage::keyReadInt CxLocalStorage::keyWriteInt", cullCaseLoops)
    {
        const long_t cliValue = 10L;

        iniIni.keyWriteInt(csKey1, cliValue);

        m_liRv = iniIni.keyReadInt(csKey1, 0L);
        xTEST_EQ(cliValue, m_liRv);
    }

    xTEST_CASE("CxLocalStorage::keyReadFloat CxLocalStorage::keyWriteFloat", cullCaseLoops)
    {
        const double cdValue = 777.0f;

        iniIni.keyWriteFloat(csKey1, cdValue);

        m_dRv = iniIni.keyReadFloat(csKey1, 0.0f);
        xTEST_EQ(cdValue, m_dRv);
    }

    xTEST_CASE("CxLocalStorage::keyReadBool CxLocalStorage::keyWriteBool", cullCaseLoops)
    {
        const bool cbValue = false;

        iniIni.keyWriteBool(csKey1, cbValue);

        m_bRv = iniIni.keyReadBool(csKey1, true);
        xTEST_EQ(cbValue, m_bRv);
    }

    xTEST_CASE("CxLocalStorage::keyWriteBin CxLocalStorage::keyReadBin", cullCaseLoops)
    {
        const std::ustring_t cusValue(10, 'z');
        const std::ustring_t cusDefaultValue(10, 'd');

        iniIni.keyWriteBin(csKey1, cusValue);

        m_usRv = iniIni.keyReadBin(csKey1, cusDefaultValue);

        // TEST: CxLocalStorage::keyWriteBin CxLocalStorage::keyReadBin
    #if xTODO
        xTEST_EQ(cusValue, m_usRv);
    #endif
    }

    xTEST_CASE("CxLocalStorage::keyClear", cullCaseLoops)
    {
        iniIni.keyClear(csKey3);
        xTEST_EQ(true, iniIni.keyIsExists(csKey3));

        m_sRv = iniIni.keyReadString(csKey3, xT("fasrfsefrtg"));
        xTEST_EQ(CxConst::xSTR_EMPTY, m_sRv);
    }

    xTEST_CASE("CxLocalStorage::keyDelete", cullCaseLoops)
    {
        const std::tstring_t csKey   = xT("Key");
        const std::tstring_t csValue = xT("");

        iniIni.keyWriteString(csKey, csValue);
        xTEST_EQ(true, iniIni.keyIsExists(csKey));

        iniIni.keyDelete(csKey);
        xTEST_EQ(false, iniIni.keyIsExists(csKey));
    }

    xTEST_CASE("CxLocalStorage::clear", cullCaseLoops)
    {
        iniIni.clear();
        xTEST_EQ(0LL, CxFile::size( iniIni.path() ));
    }

    xTEST_CASE("CxLocalStorage::remove", cullCaseLoops)
    {
        iniIni.remove();
        xTEST_EQ(false, CxFile::isExists( iniIni.path() ));
    }
}
//---------------------------------------------------------------------------
