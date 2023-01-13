/**
 * \file   ProcessInfo_apple.inl
 * \brief  process information
 */


namespace xl::system
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
ProcessInfo::_exeName_impl() const
{
    std::ctstring_t procFile = Format::str(xT("/proc/{}/exe"), _id);

    return Utils::readSymLink(procFile);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
ProcessInfo::_commandLine_impl(
    std::vec_tstring_t *out_args
) const
{
    std::vec_tstring_t args;

    // TODO: [skynowa] Volume::_commandLine_impl()
    xNOT_IMPLEMENTED

    // out
    out_args->swap(args);
}
//-------------------------------------------------------------------------------------------------

} // namespace
