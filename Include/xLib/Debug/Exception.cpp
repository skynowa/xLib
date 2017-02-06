/**
 * \file  Exception.inl
 * \brief exception
 */


#if !cmOPTION_PROJECT_HEADER_ONLY
    #include "Exception.h"
#endif

#include <xLib/Core/String.h>


xNAMESPACE_BEGIN2(xl, debug)

/*******************************************************************************
*    public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
xINLINE std::ctstring_t &
Exception::what() const
{
    return _msgT;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, debug)
