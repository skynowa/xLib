/**
 * \file   CxTest_CxConfig.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxConfig.h>

#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxPath.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxConfig::unit(
    culonglong_t &a_caseLoops
)
{
    std::ctstring_t filePath = CxPath( CxPath::exe() ).setExt(xT("ini") );

    std::ctstring_t key1     = xT("a");
    std::ctstring_t value1   = xT("1");

    std::ctstring_t key2     = xT("b");
    std::ctstring_t value2   = xT("2");

    std::ctstring_t key3     = xT("c");
    std::ctstring_t value3   = xT("3");

    std::ctstring_t content  = key1 + CxConst::equal() + value1 + CxConst::nl() +
                               key2 + CxConst::equal() + value2 + CxConst::nl() +
                               key3 + CxConst::equal() + value3 + CxConst::nl();

    xTEST_CASE("CxConfig::CxConfig", a_caseLoops)
    {
        CxConfig config;
    }

    CxFile::remove(filePath);

    CxConfig config(filePath);

    xTEST_CASE("CxConfig::createDefault", a_caseLoops)
    {
        config.createDefault(content);
    }

    xTEST_CASE("CxConfig::path", a_caseLoops)
    {
        m_sRv = config.path();
        xTEST_EQ(filePath, m_sRv);
    }

    xTEST_CASE("CxConfig::setPath", a_caseLoops)
    {
        config.setPath(filePath);

        m_sRv = config.path();
        xTEST_EQ(filePath, m_sRv);
    }

    xTEST_CASE("CxConfig::get flush", a_caseLoops)
    {
        std::map_tstring_t &_storage = config.get();
        xTEST_EQ(true, _storage.empty());

        _storage[key1] = value1;
        _storage[key2] = value2;
        _storage[key3] = value3;

        config.flush();

        m_sRv = config.keyReadString(key1, std::tstring_t());
        xTEST_EQ(value1, m_sRv);

        m_sRv = config.keyReadString(key2, std::tstring_t());
        xTEST_EQ(value2, m_sRv);

        m_sRv = config.keyReadString(key3, std::tstring_t());
        xTEST_EQ(value3, m_sRv);

        config.get().clear();
        config.flush();
    }

    xTEST_CASE("CxConfig::keyIsExists", a_caseLoops)
    {
        std::map_tstring_t &_storage = config.get();
        xTEST_EQ(true, _storage.empty());

        _storage[key1] = value1;
        _storage[key2] = value2;
        _storage[key3] = value3;

        config.flush();

        // true
        {
            std::vec_tstring_t pairs;

            pairs.push_back(key1 + CxConst::equal() + value1);
            pairs.push_back(key2 + CxConst::equal() + value2);
            pairs.push_back(key3 + CxConst::equal() + value3);

            for (size_t i = 0; i < pairs.size(); ++ i) {
                std::vec_tstring_t pair;

                CxString::split(pairs.at(i), CxConst::equal(), &pair);
                xTEST_EQ(false, pair.empty());

                m_bRv = config.keyIsExists( pair.at(0) );
                xTEST_EQ(m_bRv, true);
            }
        }

        // false
        {
            std::vec_tstring_t pairs;

            pairs.push_back(xT("not_existance_key"));
            pairs.push_back(xT("s<erfsenot_existance_key56eb54"));
            pairs.push_back(xT("not_exist456745g67ance_key"));
            pairs.push_back(xT("563yb675dfgv4g67"));
            pairs.push_back(xT("not_exi5g675467stance_key"));

            for (size_t i = 0; i < pairs.size(); ++ i) {
                std::vec_tstring_t pair;

                 CxString::split(pairs.at(i), CxConst::equal(), &pair);

                m_bRv = config.keyIsExists( pair.at(0) );
                xTEST_EQ(m_bRv, false);
            }
        }

        config.get().clear();
        config.flush();
    }

    xTEST_CASE("CxConfig::keyWriteString keyReadString", a_caseLoops)
    {
        // true
        {
            std::ctstring_t str = value1;

            config.keyWriteString(key1, str);

            m_sRv = config.keyReadString(key1, std::tstring_t());
            xTEST_EQ(str, m_sRv);
        }

        // false
        {
            std::ctstring_t str = xT("sssssssssssss");

            config.keyWriteString(key1, str);

            m_sRv = config.keyReadString(key1, std::tstring_t());
            xTEST_EQ(str, m_sRv);
        }
    }

    xTEST_CASE("CxConfig::keyReadInt keyWriteInt", a_caseLoops)
    {
        clong_t value = 10L;

        config.keyWriteInt(key1, value);

        m_liRv = config.keyReadInt(key1, 0L);
        xTEST_EQ(value, m_liRv);
    }

    xTEST_CASE("CxConfig::keyReadFloat keyWriteFloat", a_caseLoops)
    {
        cdouble_t value = 777.0f;

        config.keyWriteFloat(key1, value);

        m_dRv = config.keyReadFloat(key1, 0.0f);
        xTEST_EQ(value, m_dRv);
    }

    xTEST_CASE("CxConfig::keyReadBool keyWriteBool", a_caseLoops)
    {
        cbool_t value = false;

        config.keyWriteBool(key1, value);

        m_bRv = config.keyReadBool(key1, true);
        xTEST_EQ(value, m_bRv);
    }

    xTEST_CASE("CxConfig::keyWriteBin keyReadBin", a_caseLoops)
    {
        std::custring_t value(10, 'z');
        std::custring_t defaultValue(10, 'd');

        config.keyWriteBin(key1, value);

        m_usRv = config.keyReadBin(key1, defaultValue);
        xTEST_EQ(value, m_usRv);
    }

    xTEST_CASE("CxConfig::keyClear", a_caseLoops)
    {
        config.keyClear(key3);
        xTEST_EQ(true, config.keyIsExists(key3));

        m_sRv = config.keyReadString(key3, xT("fasrfsefrtg"));
        xTEST_EQ(CxConst::strEmpty(), m_sRv);
    }

    xTEST_CASE("CxConfig::keyDelete", a_caseLoops)
    {
        std::ctstring_t key   = xT("Key");
        std::ctstring_t value = xT("");

        config.keyWriteString(key, value);
        xTEST_EQ(true, config.keyIsExists(key));

        config.keyDelete(key);
        xTEST_EQ(false, config.keyIsExists(key));
    }

    xTEST_CASE("CxConfig::clear", a_caseLoops)
    {
        config.clear();
        xTEST_EQ(0LL, CxFile::size( config.path() ));
    }

    xTEST_CASE("CxConfig::remove", a_caseLoops)
    {
        config.remove();
        xTEST_EQ(false, CxFile::isExists( config.path() ));
    }
}
//-------------------------------------------------------------------------------------------------
