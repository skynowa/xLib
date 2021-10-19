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
MsgBox::ModalResult
MsgBox::_show_impl(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cType            a_type    /* = Ok */
) const
{
    ModalResult mrRv      { ModalResult::Unknown };
    UINT        type_impl {};
    int_t       iRv       { -1 };

    type_impl = static_cast<UINT>( internal::enums::types.toImpl( static_cast<std::ssize_t>(a_type) ) );
    iRv       = ::MessageBox(nullptr, a_text.c_str(), a_title.c_str(), type_impl);
    mrRv      = internal::enums::modalResults.toCross(iRv);

    return mrRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
