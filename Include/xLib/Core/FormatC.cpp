/**
 * \file   FormatC.cpp
 * \brief  C-style format string
 */


#include "FormatC.h"

#include <xLib/Debug/Debug.h>
#include <xLib/Test/Test.h>


namespace xl::core
{


/**************************************************************************************************
*   FormatC - public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
FormatC::str(
    cptr_ctchar_t a_fmt, ///< string format
    ...                  ///< arguments
)
{
    xTEST_NA(a_fmt);

    xCHECK_RET(a_fmt == nullptr, std::tstring_t());

    std::tstring_t sRv;

    va_list args;
    xVA_START(args, a_fmt);
    sRv = strV(a_fmt, args);
    xVA_END(args);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
std::tstring_t
FormatC::strV(
    cptr_ctchar_t a_fmt, ///< string format
    va_list       a_args ///< arguments
)
{
    xTEST_NA(a_fmt);
    xTEST_NA(a_args);

    xCHECK_RET(a_fmt == nullptr, std::tstring_t());

    std::size_t buffSize {};
    {
        va_list args;
        xVA_COPY(args, a_args);
        cint_t iRv = xTVSNPRINTF(nullptr, 0, a_fmt, args);
        xVA_END(args);

        xSTD_VERIFY(iRv != - 1);
        xSTD_VERIFY(iRv > - 1);

        if (iRv <= - 1) {
            buffSize = 0;
        } else {
            buffSize = static_cast<std::size_t>(iRv) + 1;  // + 1 for '\0'
        }

        // std::tcout << xTRACE_VAR(buffSize) << std::endl;

        xCHECK_RET(buffSize == 0, std::tstring_t());
    }

    // write to buffer
    std::tstring_t buff(buffSize, xT('\0'));
    {
        va_list args;
        xVA_COPY(args, a_args);
        cint_t iRv = xTVSNPRINTF(&buff.at(0), buffSize, a_fmt, args);
        xVA_END(args);

        xSTD_VERIFY(iRv != - 1);
        xSTD_VERIFY(iRv > - 1);
        xSTD_VERIFY(iRv == static_cast<int_t>(buffSize) - 1);

        buff.resize( static_cast<std::size_t>(iRv) );
    }

    return buff;
}
//-------------------------------------------------------------------------------------------------

} // namespace
