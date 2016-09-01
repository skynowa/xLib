/**
 * \file  Signal_unix.inl
 * \brief
 */


#include <xLib/Test/Test.h>
#include <xLib/Core/Const.h>


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
Signal::_decription_impl(
    cint_t &a_signalNum
)
{
   /**
    * FAQ: ::psignal, ::sys_siglist
    */

    const char *pcszRv = ::strsignal(a_signalNum);
    if (pcszRv == xPTR_NULL) {
        return Const::strUnknown();
    }

    return xA2T(pcszRv);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
