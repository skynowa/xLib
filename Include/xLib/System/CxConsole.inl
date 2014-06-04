/**
 * \file  CxConsole.inl
 * \brief console
 */


#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>
#include <xLib/Sync/CxThread.h>

#if   xENV_WIN
    #include "Platform/Win/CxConsole_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/CxConsole_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/CxConsole_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/CxConsole_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/CxConsole_apple.inl"
    #endif
#endif

xNAMESPACE_BEGIN2(xlib, system)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxConsole::CxConsole()
#if xENV_WIN
    :
    _wnd          (xPTR_NULL),
    _menu         (xPTR_NULL),
    _stdIn        (),
    _stdOut       (),
    _attributesDef(0)
#endif
{
    _construct_impl();
}
//-------------------------------------------------------------------------------------------------
inline
CxConsole::~CxConsole()
{
    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxConsole::setAttributes(
    const ExForeground &a_foreground,
    const ExBackground &a_background,
    cint_t             &a_attributes
) const
{
#if xENV_WIN
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);
#endif
    // n/a

    return _setAttributes_impl(a_foreground, a_background, a_attributes);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxConsole::setAttributesDef() const
{
#if xENV_WIN
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);
#endif
    // n/a

    return _setAttributesDef_impl();
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxConsole::read() const
{
#if xENV_WIN
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);
#endif

    return _read_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::write(
    std::ctstring_t &a_str
) const
{
#if xENV_WIN
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);
#endif

    _write_impl(a_str);

    std::tcout.flush();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::writeLine(
    std::ctstring_t &a_str /* = xT("") */
) const
{
#if xENV_WIN
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);
#endif

    write(a_str + CxConst::nl());
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::writeErrLine(
    std::ctstring_t &a_str
) const
{
#if xENV_WIN
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);
#endif

    writeLine(xT("Error: ") + a_str);

    pause(xTIMEOUT_INFINITE);
}
//-------------------------------------------------------------------------------------------------
inline CxConsole::ExModalResult
CxConsole::msgBox(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cuint_t         &a_type
) const
{
    xUNUSED(a_type);

#if xENV_WIN
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);
#endif

    ExModalResult mrRv;

    enum EConsoleCmd {
        cmAbort  = xT('a'),
        cmIgnore = xT('i'),
        cmRetry  = xT('r')
    };

    writeLine();
    writeLine(xT("################################################################################"));
    writeLine(xT("#  ") + a_title);
    writeLine(xT("#"));
    writeLine(xT("#  ") + a_text);
    writeLine(xT("#"));
    writeLine(xT("################################################################################"));
    writeLine();
    write(CxString::format(xT("\nAbort (%c), Ignore (%c), Retry (%c): "), cmAbort, cmIgnore, cmRetry));

    EConsoleCmd cmRv = static_cast<EConsoleCmd>( std::tcin.get() );   std::tcin.ignore();
    switch (cmRv) {
    case cmAbort:
        mrRv = mrAbort;
        writeLine(xT("Abort..."));
        break;
    case cmIgnore:
        mrRv = mrIgnore;
        writeLine(xT("Ignore..."));
        break;
    case cmRetry:
        mrRv = mrRetry;
        writeLine(xT("Retry..."));
        break;
    default:
        mrRv = mrRetry;
        writeLine(xT("Retry..."));
        break;
    }

    return mrRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::prompt(
    std::ctstring_t &a_prompt,
    cbool_t         &a_isVisible,
    std::tstring_t  *a_answer
) const
{
#if xENV_WIN
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);
#endif

    xTEST_EQ(a_prompt.empty(), false);
    xTEST_PTR(a_answer);

    for ( ; ; ) {
        write(a_prompt + xT(": "));

        for ( ; ; ) {
            ctchar_t letter = static_cast<tchar_t>( std::tcin.get() );

            // asterisks
            xCHECK_DO(a_isVisible, write(xT("*")));

            // ENTER
            xCHECK_DO(letter == 10, break);

            // BACKSPACE
            xCHECK_DO(letter == 0x8, a_answer->clear(); continue);

            a_answer->push_back(letter);
        }

        writeLine(CxConst::strEmpty());

        xCHECK_DO(a_answer->empty(), continue);

        break;
    }
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::pause(
    culong_t &a_timeoutMsec
) const
{
#if xENV_WIN
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);
#endif

    // TODO: CxConsole::pause()
#if xTODO
    #if xENV_UNIX
        std::tcout << std::endl << "Press any key to continue..." << std::endl;

        ::FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        _getch();
    #elif xENV_UNIX
        std::tcout << std::endl << "Press ENTER to continue..." << std::endl;

        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cin.get();
    #endif
#endif

    std::tstring_t msg;

	if (a_timeoutMsec == xTIMEOUT_INFINITE) {
        msg = xT("Pause, press [ENTER] to continue...");

        writeLine(msg);

        std::cin.clear();
        std::cin.ignore();
	} else {
        msg = CxString::format(xT("Pause, wait for %lu msec to continue..."), a_timeoutMsec);

        writeLine(msg);

		CxThread::currentSleep(a_timeoutMsec);
	}
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::clear() const
{
#if xENV_WIN
    xTEST_DIFF(_wnd, xWND_NATIVE_HANDLE_NULL);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);
#endif

    _clear_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxConsole::setTitle(
    std::ctstring_t &a_title
) const
{
#if xENV_WIN
    xTEST_NA(_wnd);
    xTEST_EQ(_stdIn.isValid(), true);
    xTEST_EQ(_stdOut.isValid(), true);
#endif

    _setTitle_impl(a_title);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, system)
