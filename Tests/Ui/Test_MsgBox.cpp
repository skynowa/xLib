/**
 * \file   Test_MsgBox.cpp
 * \brief  test MsgBox
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_MsgBox)
xTEST_UNIT(Test_MsgBox)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_MsgBox::unit()
{
    xTEST_CASE("show")
    {
    #if xTEST_IGNORE
	#if   0
        std::ctstring_t title;
        std::ctstring_t text;
	#elif 0
		std::ctstring_t title;
		std::ctstring_t text  = xT("Line_aaaaa");
	#elif 0
		std::ctstring_t title = xT("Title-Test AAAAAAAA BBBBBBBB");
		std::ctstring_t text;
	#elif 1
		std::ctstring_t title = xT("Title-Test AAAAAAAA BBBBBBBB");
		std::ctstring_t text  = xT("Line_aaaaa\nLine_bbbbbbb\nLine_cccccc\ndddddd fffffffffffff hhhhhhhhhhhhhhhhh jjjjjjjjjjjjjjjjjjjjj kkkkkkkkkkkkkk");
	#elif 0
		std::ctstring_t title = xT("Line_aaaaa\nLine_bbbbbbb\nLine_cccccc\ndddddd fffffffffffff hhhhhhhhhhhhhhhhh jjjjjjjjjjjjjjjjjjjjj kkkkkkkkkkkkkk");
		std::ctstring_t text  = xT("Title-Test AAAAAAAA BBBBBBBB");
	#else
	#endif

		MsgBox msgBox;
        MsgBox::ModalResult mrRes = msgBox.show(text, title, MsgBox::tpOk);
        xUNUSED(mrRes);
    #else
        Trace() << xT("[skip]");
	#endif
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
