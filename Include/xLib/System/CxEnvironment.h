/**
 * \file  CxEnvironment.h
 * \brief system environment variables
 */


#pragma once

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

xPLATFORM:
    static
    bool_t         _isExists_impl(std::ctstring_t &varName) xWARN_UNUSED_RV;
    static
    std::tstring_t _var_impl(std::ctstring_t &varName) xWARN_UNUSED_RV;
    static
    void_t         _setVar_impl(std::ctstring_t &varName, std::ctstring_t &value);
    static
    void_t         _deleteVar_impl(std::ctstring_t &varName);
    static
    void_t         _values_impl(std::vec_tstring_t *values);
    static
    std::tstring_t _expandStrings_impl(std::ctstring_t &var) xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xlib, system)
//-------------------------------------------------------------------------------------------------
#include "CxEnvironment.inl"
