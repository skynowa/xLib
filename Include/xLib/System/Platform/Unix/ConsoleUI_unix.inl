/**
 * \file  ConsoleUI_unix.inl
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
    struct termios tty {};

    int_t iRv = ::tcgetattr(STDIN_FILENO, &tty);
    xTEST_DIFF(iRv, -1);

    if (a_isEnable) {
        tty.c_lflag |= static_cast<uint_t>(ECHO);
    } else {
        tty.c_lflag &= static_cast<uint_t>(~ECHO);
    }

    iRv = ::tcsetattr(STDIN_FILENO, TCSANOW, &tty);
    xTEST_DIFF(iRv, -1);
}
//-------------------------------------------------------------------------------------------------

} // namespace
