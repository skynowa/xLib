/**
 * \file  Exception.inl
 * \brief exception
 */


#if !xOPTION_HEADER_ONLY
    #include "Exception.h"
#endif

#include <xLib/Core/String.h>


xNAMESPACE_BEGIN2(xlib, debug)

/*******************************************************************************
*    public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
Exception::what() const
{
    return _msgT;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
