/**
 * \file  Process_apple.inl
 * \brief process
 */


namespace xl::sync
{


/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
Process::id_t
Process::_idByName_impl(
    std::ctstring_t &a_processName
)
{
    id_t ulRv {};

    // TOOD: [Apple] _idByName_impl
    xNOT_IMPLEMENTED

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Process::_ids_impl(
    std::vector<Process::id_t> *a_ids
)
{
    std::vector<id_t> vidRv;

    // TOOD: [Apple] _ids_impl
    xNOT_IMPLEMENTED

    // out
    a_ids->swap(vidRv);
}
//-------------------------------------------------------------------------------------------------

} // namespace
