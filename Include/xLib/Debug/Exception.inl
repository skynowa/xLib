/**
 * \file  Exception.inl
 * \brief exception
 */


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
    std::tostringstream_t ossRes;

    ossRes.exceptions(std::tostringstream_t::failbit | std::tostringstream_t::badbit);
    ossRes << a_msgT;

    _msgT.append( ossRes.str() );

    return *this;
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
