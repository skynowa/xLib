/**
 * \file   xUnits.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

// bytes
#define xBYTES(byte) \
    ( static_cast<culonglong_t>(byte) )
#define xKB(byte) \
    ( static_cast<culonglong_t>(byte) << 10 )
#define xMB(byte) \
    ( static_cast<culonglong_t>(byte) << 20 )
#define xGB(byte) \
    ( static_cast<culonglong_t>(byte) << 30 )
#define xTB(byte) \
    ( static_cast<culonglong_t>(byte) << 40 )
#define xPB(byte) \
    ( static_cast<culonglong_t>(byte) << 50 )
#define xEB(byte) \
    ( static_cast<culonglong_t>(byte) << 60 )

// datetime
#define xMSEC(msec) \
    ( static_cast<culonglong_t>(msec) )
#define xSECOND(msec) \
    ( static_cast<culonglong_t>(msec) / 1000ULL )
#define xMINUTE(msec) \
    ( static_cast<culonglong_t>(msec) / 1000ULL * 60 )
#define xHOUR(msec) \
    ( static_cast<culonglong_t>(msec) / 1000ULL * 60 * 60 )
#define xDAY(msec) \
    ( static_cast<culonglong_t>(msec) / 1000ULL * 60 * 60 * 24 )
#define xMONTH(msec) \
    ( static_cast<culonglong_t>(msec) / 1000ULL * 60 * 60 * 24 * 30 )
#define xYEAR(msec) \
    ( static_cast<culonglong_t>(msec) / 1000ULL * 60 * 60 * 24 * 30 * 12 )

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
