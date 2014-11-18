/**
 * \file  Exception.inl
 * \brief exception
 */


#if !xOPTION_PROJECT_HEADER_ONLY
    #include "Exception.h"
#endif

#include <xLib/Core/String.h>


xNAMESPACE_BEGIN2(xlib, debug)

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

xNAMESPACE_END2(xlib, debug)
