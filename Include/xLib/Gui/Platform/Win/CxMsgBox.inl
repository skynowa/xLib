/**
 * \file   CxMsgBox.inl
 * \brief  message box
 */


xNAMESPACE_BEGIN2(xlib, gui)

/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline CxMsgBox::ExModalResult
CxMsgBox::show(
    std::ctstring_t &a_text,
    std::ctstring_t &a_title,
    cExType         &a_type    /* = tpOk */
) const
{
#if xPLATFORM_IMPL
    ExModalResult mrRv      = mrUnknown;
    UINT          type_impl = tpUnknown;
    int_t         iRv       = - 1;

    type_impl = internal::enums::types.toImpl(a_type);
    iRv       = ::MessageBox(xPTR_NULL, a_text.c_str(), a_title.c_str(), type_impl);
    mrRv      = internal::enums::modalResults.toCross(iRv);

    return mrRv;
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, gui)
