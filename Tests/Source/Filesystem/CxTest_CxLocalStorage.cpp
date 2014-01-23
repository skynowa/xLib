/**
 * \file   CxTest_CxLocalStorage.cpp
 * \brief
 */


#include <Test/Filesystem/CxTest_CxLocalStorage.h>

#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxPath.h>


//-------------------------------------------------------------------------------------------------
/* virtual */
void_t
CxTest_CxLocalStorage::unit(
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

    xTEST_CASE("CxLocalStorage::CxLocalStorage", a_caseLoops)
    {
        CxLocalStorage storage;
    }

    CxFile::remove(filePath);

    CxLocalStorage storage(filePath);

    xTEST_CASE("CxLocalStorage::createDefault", a_caseLoops)
    {
        storage.createDefault(content);
    }

    xTEST_CASE("CxLocalStorage::path", a_caseLoops)
    {
        m_sRv = storage.path();
        xTEST_EQ(filePath, m_sRv);
    }

    xTEST_CASE("CxLocalStorage::setPath", a_caseLoops)
    {
        storage.setPath(filePath);

        m_sRv = storage.path();
        xTEST_EQ(filePath, m_sRv);
    }

    xTEST_CASE("CxLocalStorage::get flush", a_caseLoops)
    {
        std::map_tstring_t &_storage = storage.get();
        xTEST_EQ(true, _storage.empty());

        _storage[key1] = value1;
        _storage[key2] = value2;
        _storage[key3] = value3;

        storage.flush();

        m_sRv = storage.keyReadString(key1, std::tstring_t());
        xTEST_EQ(value1, m_sRv);

        m_sRv = storage.keyReadString(key2, std::tstring_t());
        xTEST_EQ(value2, m_sRv);

        m_sRv = storage.keyReadString(key3, std::tstring_t());
        xTEST_EQ(value3, m_sRv);

        storage.get().clear();
        storage.flush();
    }

    xTEST_CASE("CxLocalStorage::keyIsExists", a_caseLoops)
    {
        std::map_tstring_t &_storage = storage.get();
        xTEST_EQ(true, _storage.empty());

        _storage[key1] = value1;
        _storage[key2] = value2;
        _storage[key3] = value3;

        storage.flush();

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

                m_bRv = storage.keyIsExists( pair.at(0) );
                xTEST_EQ(true, m_bRv);
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

                m_bRv = storage.keyIsExists( pair.at(0) );
                xTEST_EQ(false, m_bRv);
            }
        }

        storage.get().clear();
        storage.flush();
    }

    xTEST_CASE("CxLocalStorage::keyWriteString keyReadString", a_caseLoops)
    {
        // true
        {
            std::ctstring_t str = value1;

            storage.keyWriteString(key1, str);

            m_sRv = storage.keyReadString(key1, std::tstring_t());
            xTEST_EQ(str, m_sRv);
        }

        // false
        {
            std::ctstring_t str = xT("sssssssssssss");

            storage.keyWriteString(key1, str);

            m_sRv = storage.keyReadString(key1, std::tstring_t());
            xTEST_EQ(str, m_sRv);
        }
    }

    xTEST_CASE("CxLocalStorage::keyReadInt keyWriteInt", a_caseLoops)
    {
        clong_t value = 10L;

        storage.keyWriteInt(key1, value);

        m_liRv = storage.keyReadInt(key1, 0L);
        xTEST_EQ(value, m_liRv);
    }

    xTEST_CASE("CxLocalStorage::keyReadFloat keyWriteFloat", a_caseLoops)
    {
        cdouble_t value = 777.0f;

        storage.keyWriteFloat(key1, value);

        m_dRv = storage.keyReadFloat(key1, 0.0f);
        xTEST_EQ(value, m_dRv);
    }

    xTEST_CASE("CxLocalStorage::keyReadBool keyWriteBool", a_caseLoops)
    {
        cbool_t value = false;

        storage.keyWriteBool(key1, value);

        m_bRv = storage.keyReadBool(key1, true);
        xTEST_EQ(value, m_bRv);
    }

    xTEST_CASE("CxLocalStorage::keyWriteBin keyReadBin", a_caseLoops)
    {
        std::custring_t value(10, 'z');
        std::custring_t defaultValue(10, 'd');

        storage.keyWriteBin(key1, value);

        m_usRv = storage.keyReadBin(key1, defaultValue);
        xTEST_EQ(value, m_usRv);
    }

    xTEST_CASE("CxLocalStorage::keyClear", a_caseLoops)
    {
        storage.keyClear(key3);
        xTEST_EQ(true, storage.keyIsExists(key3));

        m_sRv = storage.keyReadString(key3, xT("fasrfsefrtg"));
        xTEST_EQ(CxConst::strEmpty(), m_sRv);
    }

    xTEST_CASE("CxLocalStorage::keyDelete", a_caseLoops)
    {
        std::ctstring_t key   = xT("Key");
        std::ctstring_t value = xT("");

        storage.keyWriteString(key, value);
        xTEST_EQ(true, storage.keyIsExists(key));

        storage.keyDelete(key);
        xTEST_EQ(false, storage.keyIsExists(key));
    }

    xTEST_CASE("CxLocalStorage::clear", a_caseLoops)
    {
        storage.clear();
        xTEST_EQ(0LL, CxFile::size( storage.path() ));
    }

    xTEST_CASE("CxLocalStorage::remove", a_caseLoops)
    {
        storage.remove();
        xTEST_EQ(false, CxFile::isExists( storage.path() ));
    }
}
//-------------------------------------------------------------------------------------------------
