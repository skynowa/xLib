/**
 * \file   Units.h
 * \brief  measure units
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

///\name In bytes
///\{
#define xBYTES(x) \
    ( static_cast<ulonglong_t>(x) )
#define xKB(x) \
    ( xBYTES(x) << 10 )
#define xMB(x) \
    ( xBYTES(x) << 20 )
#define xGB(x) \
    ( xBYTES(x) << 30 )
#define xTB(x) \
    ( xBYTES(x) << 40 )
#define xPB(x) \
    ( xBYTES(x) << 50 )
#define xEB(x) \
    ( xBYTES(x) << 60 )
#define xZB(x) \
    ( xBYTES(x) << 70 )
///\}

///\name In milliseconds
///\{
#define xMSEC(x) \
    ( static_cast<ulonglong_t>(x) )
#define xSECOND(x) \
    ( xMSEC(x) * 1000ULL )
#define xMINUTE(x) \
    ( xMSEC(x) * 1000ULL * 60 )
#define xHOUR(x) \
    ( xMSEC(x) * 1000ULL * 60 * 60 )
#define xDAY(x) \
    ( xMSEC(x) * 1000ULL * 60 * 60 * 24 )
#define xMONTH(x) \
    ( xMSEC(x) * 1000ULL * 60 * 60 * 24 * 30 )
#define xYEAR(x) \
    ( xMSEC(x) * 1000ULL * 60 * 60 * 24 * 30 * 12 )
///\}

} // namespace
//-------------------------------------------------------------------------------------------------
