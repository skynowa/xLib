/**
 * \file  Environment.h
 * \brief system environment variables
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::system
{

class Environment
    /// system environment variables
{
public:
    static
    bool_t         isExists(std::ctstring_t &varName);
        ///< check for existence
    static
    bool_t         isVarValid(std::ctstring_t &varName);
        ///< is valid environment variable name
    static
    bool_t         isValueValid(std::ctstring_t &varValue);
        ///< is valid environment variable value

    static
    std::tstring_t var(std::ctstring_t &varName);
        ///< get value by name
    static
    void_t         setVar(std::ctstring_t &varName, std::ctstring_t &value);
        ///< set or change value by name
    static
    void_t         setVars(const std::set<std::pair_tstring_t> &vars);
        ///< set or change values
    static
    void_t         deleteVar(std::ctstring_t &varName);
        ///< delete var

    static
    void_t         values(std::vec_tstring_t *values);
        ///< get all values
    static
    std::tstring_t expandStrings(std::ctstring_t &var);
        ///< expands strings by separator "%"

private:
    xNO_DEFAULT_CONSTRUCT(Environment)
    xNO_COPY_ASSIGN(Environment)

xPLATFORM_IMPL:
    static
    bool_t         _isExists_impl(std::ctstring_t &varName);
    static
    std::tstring_t _var_impl(std::ctstring_t &varName);
    static
    void_t         _setVar_impl(std::ctstring_t &varName, std::ctstring_t &value);
    static
    void_t         _deleteVar_impl(std::ctstring_t &varName);
    static
    void_t         _values_impl(std::vec_tstring_t *values);
    static
    std::tstring_t _expandStrings_impl(std::ctstring_t &var);
};

} // namespace
//-------------------------------------------------------------------------------------------------
