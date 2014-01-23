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
xNAMESPACE2_BEGIN(xlib, core)

class CxLocale
    /// locale
{
public:
                  CxLocale() {}
       ///< constructor
   virtual       ~CxLocale() {}
             ///< destructor

   std::tstring_t current() const xWARN_UNUSED_RV;
          ///< get current
   void_t         setCurrent(std::ctstring_t &locale) const;
             ///< set current
   void_t         setDefault() const;
             ///< set default

private:
    xNO_COPY_ASSIGN(CxLocale)
};

xNAMESPACE2_END(xlib, core)
//-------------------------------------------------------------------------------------------------
#include "CxLocale.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxLocaleH
