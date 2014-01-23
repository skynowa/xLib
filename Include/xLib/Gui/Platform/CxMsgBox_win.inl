/**
 * \file  CxMsgBox.inl
 * \brief message box
 */


xNAMESPACE2_BEGIN(xlib, gui)

/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline CxMsgBox::ExModalResult
CxMsgBox::_show_impl(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cExType         &a_type    /* = tpOk */
) const
{
    ExModalResult mrRv      = mrUnknown;
    UINT          type_impl = tpUnknown;
    int_t         iRv       = - 1;

    type_impl = internal::enums::types.toImpl(a_type);
    iRv       = ::MessageBox(NULL, a_text.c_str(), a_title.c_str(), type_impl);
    mrRv      = internal::enums::modalResults.toCross(iRv);

    return mrRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE2_END(xlib, gui)
