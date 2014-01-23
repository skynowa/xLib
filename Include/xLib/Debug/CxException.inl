/**
 * \file  CxException.inl
 * \brief CxException (exception)
 */


#include <xLib/Core/CxString.h>


xNAMESPACE2_BEGIN(xlib, debug)

/*******************************************************************************
*    public
*
*******************************************************************************/

//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxException::what() const
{
    return _msgT;
}
//-------------------------------------------------------------------------------------------------
template<class T>
CxException &
CxException::operator << (
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

xNAMESPACE2_END(xlib, debug)
