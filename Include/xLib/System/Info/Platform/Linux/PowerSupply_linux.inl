/**
 * \file  PowerSupply.inl
 * \brief system information
 */


namespace
{

std::ctstring_t dirPath = xT("/sys/class/power_supply/BAT0");

}

namespace xl::system::info
{

//-------------------------------------------------------------------------------------------------
bool_t
PowerSupply::_isExists_impl() const
{
	bool_t bRv {};

    Dir dir(::dirPath);
    bRv = !dir.isEmpty(Const::maskAll());

    return bRv;
}
//-------------------------------------------------------------------------------------------------
/**
 * \code{.sh}
 * cat /sys/class/power_supply/BAT0/uevent
 *
 * cat /sys/class/power_supply/BAT0/capacity
 * cat /sys/class/power_supply/BAT0/status
 * \endcode
 */
std::size_t
PowerSupply::_level_impl() const
{
    std::size_t uiRv {};

    std::ctstring_t filePath = ::dirPath + xT("/capacity");

    FileInfo fileInfo(filePath);
    xCHECK_RET(!fileInfo.isExists(), 0.0);

    // read file
    FileIO file(filePath);
    file.open(FileIO::OpenMode::ReadOnly);
    file.scanf(xT("%") xPR_SIZET, &uiRv);

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
PowerSupply::Status
PowerSupply::_status_impl() const
{
	Status psRv {};

    std::ctstring_t filePath = ::dirPath + xT("/status");

    FileInfo fileInfo(filePath);
    xCHECK_RET(!fileInfo.isExists(), Status::Unknown);

    // read file
	std::tstring_t status;
	{
		FileIO file(filePath);
		file.open(FileIO::OpenMode::ReadOnly);

		tchar_t szRv[64 + 1];
		file.scanf(xT("%s"), &szRv);

		status = szRv;
	}

	static const std::map<std::tstring_t, Status> statuses
	{
		{xT("Unknown"),     Status::Unknown},
		{xT("Discharging"), Status::Discharging},
		{xT("Charging"),    Status::Charging},
		{xT("Full"),        Status::Full}
	};

	auto it = statuses.find(status);
	if (it == statuses.cend()) {
		LogCout() << xUNKNOWN_VAR(status);
		return static_cast<Status>(4);
	}

    return it->second;
}
//-------------------------------------------------------------------------------------------------

} // namespace
