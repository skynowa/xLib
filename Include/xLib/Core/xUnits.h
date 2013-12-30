/**
 * \file   xUnits.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

// bytes
#define xBYTES(x) \
    ( static_cast<culonglong_t>(x) )
#define xKB(x) \
    ( static_cast<culonglong_t>(x) << 10 )
#define xMB(x) \
    ( static_cast<culonglong_t>(x) << 20 )
#define xGB(x) \
    ( static_cast<culonglong_t>(x) << 30 )
#define xTB(x) \
    ( static_cast<culonglong_t>(x) << 40 )
#define xPB(x) \
    ( static_cast<culonglong_t>(x) << 50 )
#define xEB(x) \
    ( static_cast<culonglong_t>(x) << 60 )

// datetime
#define xMSEC(x) \
    ( static_cast<culonglong_t>(x) )
#define xSECOND(x) \
    ( static_cast<culonglong_t>(x) * 1000ULL )
#define xMINUTE(x) \
    ( static_cast<culonglong_t>(x) * 1000ULL * 60 )
#define xHOUR(x) \
    ( static_cast<culonglong_t>(x) * 1000ULL * 60 * 60 )
#define xDAY(x) \
    ( static_cast<culonglong_t>(x) * 1000ULL * 60 * 60 * 24 )
#define xMONTH(x) \
    ( static_cast<culonglong_t>(x) * 1000ULL * 60 * 60 * 24 * 30 )
#define xYEAR(x) \
    ( static_cast<culonglong_t>(x) * 1000ULL * 60 * 60 * 24 * 30 * 12 )

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
