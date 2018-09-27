/**
 * \file   MsgBox.inl
 * \brief  message box
 */


xNAMESPACE_BEGIN2(xl, ui)

/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
MsgBox::ExModalResult
MsgBox::_show_impl(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cType            a_type    /* = tpOk */
) const
{
    ExModalResult mrRv      = mrUnknown;
    UINT          type_impl = tpUnknown;
    int_t         iRv       = - 1;

    type_impl = internal::enums::types.toImpl(a_type);
    iRv       = ::MessageBox(nullptr, a_text.c_str(), a_title.c_str(), type_impl);
    mrRv      = internal::enums::modalResults.toCross(iRv);

    return mrRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, ui)
