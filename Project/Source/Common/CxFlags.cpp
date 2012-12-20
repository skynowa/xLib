/**
 * \file   CxFlags.cpp
 * \brief  bit mask flags
 */


#include <xLib/Common/CxFlags.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*   public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxFlags::CxFlags() : 
    _m_mFlags(0)
{
}
//---------------------------------------------------------------------------
CxFlags::CxFlags(
    const CxFlags &a_cfFlags
) : 
    _m_mFlags(a_cfFlags._m_mFlags)
{
}
//---------------------------------------------------------------------------
CxFlags::CxFlags(
    const int &a_ciFlag
) : 
    _m_mFlags( mask_t(a_ciFlag) )
{
} 
//---------------------------------------------------------------------------
CxFlags::CxFlags(
    const mask_t &a_cmFlag
) :
    _m_mFlags(a_cmFlag)
{
}
//---------------------------------------------------------------------------
/* virtual */
CxFlags::~CxFlags() {

}
//---------------------------------------------------------------------------﻿  ﻿
bool 
CxFlags::isSet(
    const int &a_ciFlag
) const
{
    return (_m_mFlags & mask_t(a_ciFlag)) == mask_t(a_ciFlag);
}
//---------------------------------------------------------------------------        
bool 
CxFlags::isSet(
    const mask_t &a_cmFlag
) const
{
    return (_m_mFlags & a_cmFlag) == a_cmFlag;
}
//---------------------------------------------------------------------------        
bool 
CxFlags::isAnySet(
    const mask_t &a_cmFlag
) const
{
    return 0 != (_m_mFlags & a_cmFlag);
}
//---------------------------------------------------------------------------        
bool 
CxFlags::isAnySet(
    const int &a_ciFlag
) const
{
    return 0 != (_m_mFlags & mask_t(a_ciFlag)); 
}
//---------------------------------------------------------------------------        
void 
CxFlags::setFlag(
    const mask_t &a_cmFlag
)
{
    _m_mFlags |= a_cmFlag;
}
//---------------------------------------------------------------------------        
void 
CxFlags::setFlag(
    const int &a_ciFlag
)
{
    _m_mFlags |= mask_t(a_ciFlag);
}
//---------------------------------------------------------------------------        
void 
CxFlags::unsetFlag(
    const mask_t &a_cmFlag
)
{
    _m_mFlags &= ~a_cmFlag;
}
//---------------------------------------------------------------------------        
void 
CxFlags::unsetFlag(
    const int &a_ciFlag
)
{
    _m_mFlags &= ~mask_t(a_ciFlag);
}
//---------------------------------------------------------------------------        
void 
CxFlags::setFlags(
    const mask_t &a_cmFlag
)
{
    _m_mFlags = a_cmFlag; 
}
//---------------------------------------------------------------------------        
CxFlags::mask_t
CxFlags::getFlags() const {
    return _m_mFlags;
}
//---------------------------------------------------------------------------        
CxFlags& 
CxFlags::operator = (
    const CxFlags &a_cfFlags
)
{
    xCHECK_RET(this == &a_cfFlags, *this);

    _m_mFlags = a_cfFlags._m_mFlags;

    return *this;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
