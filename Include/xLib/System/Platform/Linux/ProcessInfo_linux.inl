/**
 * \file   ProcessInfo.inl
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

    std::ctstring_t procPath = Format::str(xT("/proc/{}/cmdline"), _id);

	auto procFile = autoFile(procPath, "r");
	xTEST_PTR(procFile.get());

    constexpr std::size_t bufferSize {2048};
    char      buff[bufferSize] {};

    while ( std::fgets(buff, static_cast<int_t>(bufferSize), procFile.get()) ) {
        for (size_t pos = 0; pos < bufferSize && buff[pos] != '\0'; ) {
            args.push_back( xA2T(buff + pos) );

            pos += std::strlen(buff + pos) + 1;
        }
    }

    // out
    out_args->swap(args);
}
//-------------------------------------------------------------------------------------------------

} // namespace
