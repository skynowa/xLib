/**
 * \file  CxLocale.h
 * \brief locale
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxLocale :
    private CxNonCopyable
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
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
