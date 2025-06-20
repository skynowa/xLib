/**
 * \file  Console_unix.inl
 * \brief Shell console
 */


namespace xl::system
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
Console::_ctor_impl()
{
    // xNA;
}
//-------------------------------------------------------------------------------------------------
void_t
Console::_dtor_impl()
{
    // xNA;
}
//-------------------------------------------------------------------------------------------------
/**
 * Change the title of a terminal
 *
 * https://www.zachpfeffer.com/single-post/Change-the-title-of-a-terminal-on-Ubuntu-1604
 *
 * set-title()
 * {
 *     ORIG=$PS1
 * 	   TITLE="\033]2;$@\a"
 * 	   PS1=${ORIG}${TITLE}
 * }
 *
 * ESC]0;stringBEL - Set icon name and window title to string
 * ESC]1;stringBEL - Set icon name to string
 * ESC]2;stringBEL - Set window title to string
 *
 * Icons:
 * https://unicode.org/emoji/charts/full-emoji-list.html
 * https://apps.timwhitlock.info/emoji/tables/unicode
 */
void_t
Console::_setTitle_impl(
    std::ctstring_t &a_title
) const
{
	Color color(true, true);

	write( color.escape(Format::str(xT("\033]0;{}\a"), a_title)) );
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Console::_read_impl() const
{
    std::tstring_t sRv;

    // BUG: Console::_read_impl()
    std::tcin >> sRv;

    return sRv;
}
//-------------------------------------------------------------------------------------------------
void_t
Console::_write_impl(
    std::ctstring_t &a_str
) const
{
    std::tcout << a_str << std::flush;
}
//-------------------------------------------------------------------------------------------------
void_t
Console::_clear_impl() const
{
    writeLine( Const::ff() );
}
//-------------------------------------------------------------------------------------------------

} // namespace
