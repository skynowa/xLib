/**
 * \file  Signal_unix.inl
 * \brief
 */


#include <xLib/Test/Test.h>
#include <xLib/Core/Const.h>


xNAMESPACE_BEGIN2(xl, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
Signal::_decription_impl(
    cint_t &a_signalNum
)
{
   /**
    * FAQ: ::psignal, ::sys_siglist
    */

    cptr_cchar pcszRv = ::strsignal(a_signalNum);
    if (pcszRv == nullptr) {
        return Const::strUnknown();
    }

    return xA2T(pcszRv);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, sync)
