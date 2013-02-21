/**
 * \file  CxException.inl
 * \brief CxException (exception)
 */


#include <xLib/Common/CxString.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
template<typename T>
CxException &
CxException::operator << (
    const T &a_cMessageT
)
{
    std::tostringstream_t ossRes;

    ossRes.exceptions(std::tostringstream_t::failbit | std::tostringstream_t::badbit);
    ossRes << a_cMessageT;

    _m_sMessage.append( ossRes.str() );

    return *this;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
