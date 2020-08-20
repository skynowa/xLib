/**
 * \file  Locale.h
 * \brief locale
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

class Locale
    /// locale
{
public:
                  Locale() = default;
   virtual       ~Locale() = default;

   std::tstring_t current() const;
          ///< get current
   void_t         setCurrent(std::ctstring_t &locale) const;
             ///< set current
   void_t         setDefault() const;
             ///< set default

private:
    xNO_COPY_ASSIGN(Locale)

xPLATFORM_IMPL:
    std::tstring_t _current_impl() const;
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
