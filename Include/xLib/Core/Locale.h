/**
 * \file  Locale.h
 * \brief locale
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::core
{

class Locale
    /// locale
{
public:
///@name ctors, dtor
///@{
			Locale() = default;
   virtual ~Locale() = default;

   xNO_COPY_ASSIGN(Locale)
///@}

   std::tstring_t current() const;
          ///< get current
   void_t         setCurrent(std::ctstring_t &locale) const;
             ///< set current
   void_t         setDefault() const;
             ///< set default

xPLATFORM_IMPL:
    std::tstring_t _current_impl() const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
