/**
 * \file  PowerSupply.inl
 * \brief system information
 */


namespace xl::system::info
{

//-------------------------------------------------------------------------------------------------
bool_t
PowerSupply::_isExists_impl() const
{
	bool_t bRv {};

    // TODO: [skynowa] PowerSupply::_isExists_impl()
    xNOT_IMPLEMENTED

    return bRv;
}
//-------------------------------------------------------------------------------------------------
std::size_t
PowerSupply::_level_impl() const
{
	std::size_t uiRv {};

    // TODO: [skynowa] PowerSupply::_level_impl()
    xNOT_IMPLEMENTED

    return uiRv;
}
//-------------------------------------------------------------------------------------------------
PowerSupply::Status
PowerSupply::_status_impl() const
{
	Status psRv {};

	// TODO: [skynowa] PowerSupply::_level_impl()
	xNOT_IMPLEMENTED

	return psRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
