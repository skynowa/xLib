/**
 * \file   MsgBox.inl
 * \brief  message box
 */


namespace xl::ui
{

/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
MsgBox::ExModalResult
MsgBox::_show_impl(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cType            a_type    /* = Ok */
) const
{
    ExModalResult mrRv      = Unknown;
    UINT          type_impl = Unknown;
    int_t         iRv       = - 1;

    type_impl = internal::enums::types.toImpl(a_type);
    iRv       = ::MessageBox(nullptr, a_text.c_str(), a_title.c_str(), type_impl);
    mrRv      = internal::enums::modalResults.toCross(iRv);

    return mrRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
