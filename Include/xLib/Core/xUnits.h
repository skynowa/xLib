/**
 * \file   xUnits.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

// bytes
#define xKB(x) ( static_cast<culonglong_t>(x) << 10 )
#define xMB(x) ( static_cast<culonglong_t>(x) << 20 )
#define xGB(x) ( static_cast<culonglong_t>(x) << 30 )
#define xTB(x) ( static_cast<culonglong_t>(x) << 40 )
#define xPB(x) ( static_cast<culonglong_t>(x) << 50 )
#define xEB(x) ( static_cast<culonglong_t>(x) << 60 )

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
