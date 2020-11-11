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
	virtual ~Environment() = default;

	xNO_DEFAULT_CONSTRUCT(Environment)
	xNO_COPY_ASSIGN(Environment)
///@}

    bool_t         isExists() const;
        ///< check for existence
    std::tstring_t var() const;
        ///< get value by name
    void_t         setVar(std::ctstring_t &value) const;
        ///< set or change value by name
    void_t         removeVar() const;
        ///< delete var

xPUBLIC_STATIC:
    static
    void_t         setVars(const std::set<std::pair_tstring_t> &vars);
        ///< set or change values
    static
    void_t         vars(std::vec_tstring_t *values);
        ///< get all values
    static
    std::tstring_t expandVars(std::ctstring_t &strWithVars);
        ///< expands strings by separator "%"
    static
    void_t         varPath(std::vec_tstring_t *dirPaths);
        ///< get PATH value

private:
    static std::csize_t    _envMax;
        ///< maximum permissible string length of an environmental variable
	static std::ctstring_t _separator;
		///< var / value separator

    std::ctstring_t _varName;

    bool_t _isVarValid() const;
        ///< is valid environment variable name
    bool_t _isValueValid(std::ctstring_t &varValue) const;
        ///< is valid environment variable value

xPLATFORM_IMPL:
    bool_t         _isExists_impl() const;
    std::tstring_t _var_impl() const;
    void_t         _setVar_impl(std::ctstring_t &value) const;
    void_t         _removeVar_impl() const;

    static
    void_t         _vars_impl(std::vec_tstring_t *values);
};

} // namespace
//-------------------------------------------------------------------------------------------------
