/**
 * \file  CxEnvironment.h
 * \brief system environment variables
 */


#pragma once

#ifndef xLib_CxEnvironmentH
#define xLib_CxEnvironmentH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, system)

class CxEnvironment
    /// system environment variables
{
public:
    static
    bool_t         isExists(std::ctstring_t &varName) xWARN_UNUSED_RV;
        ///< check for existence
    static
    bool_t         isVarValid(std::ctstring_t &varName) xWARN_UNUSED_RV;
        ///< is valid environment variable name
    static
    bool_t         isValueValid(std::ctstring_t &varValue) xWARN_UNUSED_RV;
        ///< is valid environment variable value
    static
    std::tstring_t var(std::ctstring_t &varName) xWARN_UNUSED_RV;
        ///< get value by name
    static
    void_t         setVar(std::ctstring_t &varName, std::ctstring_t &value);
        ///< set or change value by name
    static
    void_t         deleteVar(std::ctstring_t &varName);
        ///< delete var
    static
    void_t         values(std::vec_tstring_t *values);
        ///< get all values
    static
    std::tstring_t expandStrings(std::ctstring_t &var) xWARN_UNUSED_RV;
        ///< expands strings by separator "%"

private:
                   CxEnvironment();
        ///< constructor
    virtual       ~CxEnvironment();
        ///< destructor

    xNO_COPY_ASSIGN(CxEnvironment)
};

xNAMESPACE_END2(xlib, system)
//-------------------------------------------------------------------------------------------------
#include "CxEnvironment.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxEnvironmentH
