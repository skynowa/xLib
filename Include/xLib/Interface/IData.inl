/**
 * \file  IData.inl
 * \brief  DTO (Data transfer object)
 */


namespace xl::interface_
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline core::OStream &
operator << (
	core::OStream    &a_os,
	const IDataPrint &a_data
)
{
	a_data.print(a_os);

	return a_os;
}
//-------------------------------------------------------------------------------------------------

} // namespace
