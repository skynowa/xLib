/**
 * \file  CxMsgBox.inl
 * \brief message box
 */


xNAMESPACE_BEGIN(xlib)

/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline CxMsgBox::ExModalResult
CxMsgBox::show_impl(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cExType         &a_type    /* = tpOk */
) const
{
    ExModalResult mrRv      = mrUnknown;
    UINT          type_impl = tpUnknown;
    int_t         iRv       = - 1;

    type_impl = NxInternal::NxEnum::types.toImpl(a_type);
    iRv       = ::MessageBox(NULL, a_text.c_str(), a_title.c_str(), type_impl);
    mrRv      = NxInternal::NxEnum::modalResults.toCross(iRv);

    return mrRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(xlib)
