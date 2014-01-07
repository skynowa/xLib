/**
 * \file  CxMsgBox.inl
 * \brief message box
 */


#include <xLib/Core/CxString.h>
#include <xLib/System/CxConsole.h>
#include <xLib/Filesystem/CxPath.h>


xNAMESPACE_BEGIN(NxLib)

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
    ExModalResult mrRv = mrUnknown;
    int_t         iRv  = - 1;

    UINT type = MB_OK;
    {
        switch (a_type) {
        case tpOk:
        default:
            type = MB_OK;
            break;
        case tpAbortRetryIgnore:
            type = MB_ABORTRETRYIGNORE | MB_ICONSTOP;
            break;
        }
    }

    iRv  = ::MessageBox(NULL, a_text.c_str(), a_title.c_str(), a_type);
    mrRv = NxInternal::NxEnum::modalResults.toCross(iRv);

    return mrRv;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
