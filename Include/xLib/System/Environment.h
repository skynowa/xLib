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
///@name ctors, dtor
///@{
	explicit Environment(std::ctstring_t &varName);
	        ~Environment() = default;

	xNO_DEFAULT_CONSTRUCT(Environment)
	xNO_COPY_ASSIGN(Environment)
///@}

    bool_t         isExists() const;
        ///< check for existence
    std::tstring_t var() const;
        ///< get value by name
    void_t         setVar(std::ctstring_t &value) const;
        ///< set or change value by name
    void_t         deleteVar() const;
        ///< delete var

xPUBLIC_STATIC:
    static
    void_t         setVars(const std::set<std::pair_tstring_t> &vars);
        ///< set or change values
    static
    void_t         values(std::vec_tstring_t *values);
        ///< get all values
    static
    std::tstring_t expandStrings(std::ctstring_t &varName);
        ///< expands strings by separator "%"
    static
    void_t         varPath(std::vec_tstring_t *dirPaths);
        ///< get PATH value

private:
    static constexpr std::size_t _envMax
    #if   xENV_WIN
        #if   xCOMPILER_MS
            {_MAX_ENV};
        #else
            {32767}; // custom define
        #endif
    #elif xENV_UNIX
        {32767}; // custom define
    #endif
        ///< maximum permissible string length of an environmental variable

    std::ctstring_t _varName;

    bool_t         _isVarValid() const;
        ///< is valid environment variable name
    bool_t         _isValueValid(std::ctstring_t &varValue) const;
        ///< is valid environment variable value

xPLATFORM_IMPL:
    bool_t         _isExists_impl() const;
    std::tstring_t _var_impl() const;
    void_t         _setVar_impl(std::ctstring_t &value) const;
    void_t         _deleteVar_impl() const;

    static
    void_t         _values_impl(std::vec_tstring_t *values);
    static
    std::tstring_t _expandStrings_impl(std::ctstring_t &varName);
};

} // namespace
//-------------------------------------------------------------------------------------------------
