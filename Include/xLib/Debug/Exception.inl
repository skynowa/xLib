/**
 * \file  Exception.inl
 * \brief exception
 */


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
template<class T>
Exception &
Exception::operator << (
    const T &a_msgT
)
{
    std::tostringstream_t ossRes;

    ossRes.exceptions(std::tostringstream_t::failbit | std::tostringstream_t::badbit);
    ossRes << a_msgT;

    _msgT.append( ossRes.str() );

    return *this;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
