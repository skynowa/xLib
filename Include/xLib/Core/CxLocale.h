/**
 * \file  CxLocale.h
 * \brief locale
 */


#pragma once

#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

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

xPLATFORM:
    std::tstring_t _current_impl() const xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#include "CxLocale.inl"
