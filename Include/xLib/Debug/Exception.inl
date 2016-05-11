/**
 * \file  Exception.inl
 * \brief exception
 */


#include <xLib/Core/Format.h>

xNAMESPACE_BEGIN2(xlib, debug)

/*******************************************************************************
*    public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
template<class T>
Exception &
Exception::operator << (
    const T &a_msgT
)
{
    _msgT.append( Format::str(xT("{}"), a_msgT) );

    return *this;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
