/**
 * \file  CxException.cpp
 * \brief CxException (exception)
 */


#include <xLib/Debug/CxException.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
xINLINE_HO std::ctstring_t &
CxException::what() const
{
    return _msgT;
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
