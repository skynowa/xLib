/**
 * \file  ConsoleUI_win.inl
 * \brief Shell console
 */


#include <xLib/Core/Const.h>
#include <xLib/Core/String.h>
#include <xLib/Sync/Thread.h>


namespace xl::system
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
ConsoleUI::_setStdinEcho_impl(
    cbool_t a_isEnable
) const
{
    DWORD mode {};
    BOOL blRv = ::GetConsoleMode(_stdIn.get(), &mode);
    xTEST_DIFF(blRv, FALSE);

    if (a_isEnable) {
        mode |= ENABLE_ECHO_INPUT;
    } else {
        mode &= ~ENABLE_ECHO_INPUT;
    }

    blRv = ::SetConsoleMode(_stdIn.get(), mode);
    xTEST_DIFF(blRv, FALSE);
}
//-------------------------------------------------------------------------------------------------

} // namespace
