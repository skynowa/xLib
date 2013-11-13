/**
 * \file  CxLocale.h
 * \brief locale
 */


#pragma once

#ifndef xLib_CxLocaleH
#define xLib_CxLocaleH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxLocale
    /// locale
{
public:
   static std::tstring_t current() xWARN_UNUSED_RV;
          ///< get current
   static void_t         setCurrent(std::ctstring_t &locale);
             ///< set current
   static void_t         setDefault();
             ///< set default

private:
                         CxLocale();
       ///< constructor
   virtual              ~CxLocale();
             ///< destructor

xNO_COPY_ASSIGN(CxLocale)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include <Core/CxLocale.inl>
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxLocaleH
