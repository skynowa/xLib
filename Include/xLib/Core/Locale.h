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

xPLATFORM_IMPL:
    std::tstring_t _current_impl() const xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "Locale.cpp"
#endif
