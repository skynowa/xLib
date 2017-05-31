/**
 * \file   FormatC.cpp
 * \brief  C-style format string
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "FormatC.h"
#endif

#include <xLib/Debug/Debug.h>
#include <xLib/Test/StdTest.h>
#include <xLib/Test/Test.h>


xNAMESPACE_BEGIN2(xl, core)


/**************************************************************************************************
*   FormatC - public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
FormatC::str(
    cptr_ctchar_t a_format, ...    ///< string format
)
{
    xTEST_NA(a_format);

    xCHECK_RET(a_format == xPTR_NULL, std::tstring_t());

    std::tstring_t sRv;

    va_list args;
    xVA_START(args, a_format);
    sRv = strV(a_format, args);
    xVA_END(args);

    return sRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
xINLINE std::tstring_t
FormatC::strV(
    cptr_ctchar_t a_format,    ///< string format
    va_list       a_args       ///< arguments
)
{
    xTEST_NA(a_format);
    xTEST_NA(a_args);

    xCHECK_RET(a_format == xPTR_NULL, std::tstring_t());

    std::size_t buffSize = 0;
    {
        va_list args;
        xVA_COPY(args, a_args);
        cint_t iRv = xTVSNPRINTF(xPTR_NULL, 0, a_format, args);
        xVA_END(args);

        STD_VERIFY(iRv != - 1);
        STD_VERIFY(iRv > - 1);

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
        cint_t iRv = xTVSNPRINTF(&buff.at(0), buffSize, a_format, args);
        xVA_END(args);

        STD_VERIFY(iRv != - 1);
        STD_VERIFY(iRv > - 1);
        STD_VERIFY(iRv == static_cast<int_t>(buffSize) - 1);

        buff.resize( static_cast<std::size_t>(iRv) );
    }

    return buff;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, core)
