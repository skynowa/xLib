/**
 * \file   Test_Iconv.cpp
 * \brief  test Iconv
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_Iconv)
xTEST_UNIT(Test_Iconv)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Iconv::unit()
{
	xTEST_CASE("Iconv - trivial")
	{
		Iconv conv("EUC-JP", "UTF-8");
		std::tstring_t in = "hello iconv";
		std::tstring_t out;
		conv.convert(in, &out);
		xTEST_EQ(in, out);

		in = "今日は天気だ";
		Iconv reconv("UTF-8", "EUC-JP");
		conv.convert(in, &out);

		std::tstring_t out2;
		reconv.convert(out, &out2);
		xTEST_EQ(in, out2);
	}

	xTEST_CASE("Iconv - large")
	{
		Iconv conv("EUC-JP", "UTF-8");
		std::tstring_t in = std::tstring_t(2048, 'a');
		std::tstring_t out;
		conv.convert(in, &out);
		xTEST_EQ(in, out);
	}

	xTEST_CASE("Iconv - unsupported")
	{
		xTEST_THROW(Iconv("unknown", "UTF-8"), std::runtime_error);
		xTEST_THROW(Iconv("UTF-8", "unknown"), std::runtime_error);
	}

	xTEST_CASE("Iconv - invalid")
	{
		Iconv conv("UTF-8", "EUC-JP");
		std::tstring_t out;
		xTEST_THROW(conv.convert("あ", &out), std::runtime_error);
	}

	xTEST_CASE("Iconv - ignore_error")
	{
		Iconv conv("UTF-8", "EUC-JP", true);
		std::tstring_t out;
		xTEST_THROW_NO(conv.convert("あ", &out));
	}

	xTEST_CASE("Iconv - zero_buffer")
	{
		xTEST_THROW(Iconv("UTF-8", "EUC-JP", false, 0), std::runtime_error);
	}

	return true;
}
//-------------------------------------------------------------------------------------------------
