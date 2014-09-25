/**
 * \file  Locale.h
 * \brief locale
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

class Locale
    /// locale
{
public:
                  Locale() {}
       ///< constructor
   virtual       ~Locale() {}
             ///< destructor

   std::tstring_t current() const xWARN_UNUSED_RV;
          ///< get current
   void_t         setCurrent(std::ctstring_t &locale) const;
             ///< set current
   void_t         setDefault() const;
             ///< set default

private:
    xNO_COPY_ASSIGN(Locale)

xPLATFORM:
    std::tstring_t _current_impl() const xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#if xOPTION_HEADER_ONLY
    #include "Locale.inl"
#endif
