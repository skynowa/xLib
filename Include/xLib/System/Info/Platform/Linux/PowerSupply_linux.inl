/**
 * \file  PowerSupply.inl
 * \brief system information
 */


namespace xl::system::info
{

//-------------------------------------------------------------------------------------------------
bool_t
PowerSupply::_isPowerSupply_impl() const
{
	bool_t bRv {};

    std::ctstring_t dirPath = xT("/sys/class/power_supply");

    Dir dir(dirPath);
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
PowerSupply::_powerSupplyLevel_impl() const
{
    std::size_t uiRv {};

    std::ctstring_t filePath = xT("/sys/class/power_supply/BAT0/capacity");

    FileInfo fileInfo(filePath);
    xCHECK_RET(!fileInfo.isExists(), 0.0);

    // read file
    FileIO file(filePath);
    file.open(FileIO::OpenMode::ReadOnly);
    file.scanf(xT("%") xPR_SIZET, &uiRv);

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
PowerSupply::PowerSupplyStatus
PowerSupply::_powerSupplyStatus_impl() const
{
	PowerSupplyStatus psRv {};

    std::ctstring_t filePath = xT("/sys/class/power_supply/BAT0/status");

    FileInfo fileInfo(filePath);
    xCHECK_RET(!fileInfo.isExists(), PowerSupplyStatus::Unknown);

    // read file
	std::tstring_t status;
	{
		FileIO file(filePath);
		file.open(FileIO::OpenMode::ReadOnly);

		tchar_t szRv[64 + 1];
		file.scanf(xT("%s"), &szRv);

		status = szRv;
	}

	static const std::map<std::tstring_t, PowerSupplyStatus> statuses
	{
		{xT("Unknown"),     PowerSupplyStatus::Unknown},
		{xT("Discharging"), PowerSupplyStatus::Discharging},
		{xT("Charging"),    PowerSupplyStatus::Charging},
		{xT("Full"),        PowerSupplyStatus::Full}
	};

	auto it = statuses.find(status);
	if (it == statuses.cend()) {
		Cout() << xUNKNOWN_VAR(status);
		return static_cast<PowerSupplyStatus>(4);
	}

    return it->second;
}
//-------------------------------------------------------------------------------------------------

} // namespace
