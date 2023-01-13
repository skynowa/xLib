/**
 * \file  Debugger_apple.inl
 * \brief debugger
 */


namespace xl::debug
{

/**************************************************************************************************
*    public static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
Debugger::_isActive_impl() const
{
	// TOOD: [Apple] _isActive_impl
	// https://stackoverflow.com/questions/40218676/get-parent-process-information-at-runtime-on-ios-application

    return false;
}
//-------------------------------------------------------------------------------------------------

} // namespace
