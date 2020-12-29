/**
 * \file   Test_Config.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Config)
xTEST_UNIT(Test_Config)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Config::unit()
{
    std::ctstring_t filePath = Path::exe().setExt(xT("cfg") ).str();

    std::ctstring_t key1     = xT("a");
    std::ctstring_t value1   = xT("1");

    std::ctstring_t key2     = xT("b");
    std::ctstring_t value2   = xT("2");

    std::ctstring_t key3     = xT("c");
    std::ctstring_t value3   = xT("3");

    std::cmap_tstring_t content
	{
        {key1, value1},
        {key2, value2},
        {key3, value3}
    };

    xTEST_CASE("Config")
    {
        Config config;
    }

	{
		File(filePath).remove();
	}

    Config config(filePath);

    xTEST_CASE("saveDefault,read")
    {
        config.saveDefault(content);
        config.read();
        xTEST(!config.get().empty());

        config.clear();
    }

    xTEST_CASE("path")
    {
        m_sRv = config.path();
        xTEST_EQ(m_sRv, filePath);
    }

    xTEST_CASE("setPath")
    {
        config.setPath(filePath);

        m_sRv = config.path();
        xTEST_EQ(m_sRv, filePath);
    }

    xTEST_CASE("get, save")
    {
        auto &content = config.get();
        xTEST(content.empty());

        content[key1] = value1;
        content[key2] = value2;
        content[key3] = value3;

        config.save();

        m_sRv = config.value(key1, std::tstring_t());
        xTEST_EQ(m_sRv, value1);

        m_sRv = config.value(key2, std::tstring_t());
        xTEST_EQ(m_sRv, value2);

        m_sRv = config.value(key3, std::tstring_t());
        xTEST_EQ(m_sRv, value3);

        config.get().clear();
        config.save();
    }

    xTEST_CASE("keyIsExists")
    {
    	auto &content = config.get();
        xTEST(content.empty());

        content[key1] = value1;
        content[key2] = value2;
        content[key3] = value3;

        config.save();

        // true
        {
            std::cvec_tstring_t pairs
			{
				{key1 + Const::equal() + value1},
				{key2 + Const::equal() + value2},
				{key3 + Const::equal() + value3}
			};

            for (const auto &it_pair : pairs) {
                std::vec_tstring_t pair;
                String::split(it_pair, Const::equal(), &pair);
                xTEST(!pair.empty());

                m_bRv = config.keyIsExists( pair.at(0) );
                xTEST(m_bRv);
            }
        }

        // false
        {
            std::cvec_tstring_t pairs
            {
				{xT("not_existance_key")},
				{xT("s<erfsenot_existance_key56eb54")},
				{xT("not_exist456745g67ance_key")},
				{xT("563yb675dfgv4g67")},
				{xT("not_exi5g675467stance_key")}
            };

            for (const auto &it_pair : pairs) {
                std::vec_tstring_t pair;
                 String::split(it_pair, Const::equal(), &pair);

                m_bRv = config.keyIsExists( pair.at(0) );
                xTEST(!m_bRv);
            }
        }

        config.get().clear();
        config.save();
    }

    xTEST_CASE("get/set - cptr_ctchar_t")
    {
		// true
		{
			std::ctstring_t str = value1;
			config.setValue(key1, str);

			m_sRv = config.value(key1, xT(""));
			xTEST_EQ(m_sRv, str);
		}

		// false
		{
			std::ctstring_t str = xT("sssssssssssss");
			config.setValue(key1, str);

			m_sRv = config.value(key1, xT(""));
			xTEST(m_sRv == str);
		}
    }

    xTEST_CASE("get/set - std::ctstring_t")
    {
        // true
        {
            std::ctstring_t str = value1;
            config.setValue(key1, str);

            m_sRv = config.value(key1, std::tstring_t());
            xTEST_EQ(m_sRv, str);
        }

        // false
        {
            std::ctstring_t str = xT("sssssssssssss");
            config.setValue(key1, str);

            m_sRv = config.value(key1, std::tstring_t());
            xTEST_EQ(m_sRv, str);
        }
    }

    xTEST_CASE("get/set - clong_t")
    {
        clong_t value = 10L;
        config.setValue(key1, value);

        m_liRv = config.value(key1, 1L);
        xTEST_EQ(m_liRv, value);
    }

    xTEST_CASE("get/set - cdouble_t")
    {
        cdouble_t value = 777.0f;
        config.setValue(key1, value);

        m_dRv = config.value(key1, 0.0f);
        xTEST_EQ(m_dRv, value);
    }

    xTEST_CASE("get/set - cbool_t")
    {
        cbool_t value = false;
        config.setValue(key1, value);

        m_bRv = config.value(key1, true);
        xTEST_EQ(m_bRv, value);
    }

    xTEST_CASE("get/set - std::custring_t")
    {
        std::custring_t value(10, 'z');
        std::custring_t defaultValue(10, 'd');

        config.setValue(key1, value);

        m_usRv = config.value(key1, defaultValue);
        xTEST_EQ(m_usRv, value);
    }

    xTEST_CASE("keyClear")
    {
		config.keyClear(key3);
		xTEST( config.keyIsExists(key3));

		m_sRv = config.value(key3, xT("fasrfsefrtg"));
		xTEST_EQ(m_sRv, Const::strEmpty());
    }

    xTEST_CASE("keyDelete")
    {
        std::ctstring_t key   = xT("Key");
        std::ctstring_t value = xT("");

        config.setValue(key, value);
        xTEST(config.keyIsExists(key));

        config.keyDelete(key);
        xTEST(!config.keyIsExists(key));
    }

    xTEST_CASE("clear")
    {
        config.clear();
        xTEST_EQ(FileInfo( config.path() ).size(), 0LL);
    }

    xTEST_CASE("remove")
    {
        config.remove();
        xTEST(!FileInfo( config.path() ).isExists());
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
