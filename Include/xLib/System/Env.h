/**
 * \file  Env.h
 * \brief system environment variables
 *
 * \libs
 *
 * - https://github.com/TUM-I5/utils/blob/master/env.h
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Interface/IStr.h>
//-------------------------------------------------------------------------------------------------
namespace xl::system
{

class Env :
	public IStr
    /// system environment variable
{
public:
///\name ctors, dtor
///\{
    explicit Env(std::ctstring_t &name);
             Env(std::ctstring_t &ns, std::ctstring_t &name);
    virtual ~Env() = default;

    xNO_DEFAULT_CONSTRUCT(Env);
    xNO_COPY_ASSIGN(Env);

    static Env path();
        ///< get PATH values (/usr/bin ... pathes) with separator
///\}

///\name Overrides
///\{
	std::tstring_t str() const final;
		///< variable with value (DESKTOP_SESSION=xfce)
///\}

    bool_t             isExists() const;
        ///< check for existence
    std::tstring_t     value() const;
        ///< get value
    std::vec_tstring_t values() const;
        ///< convert value to container
    void_t             setValue(std::ctstring_t &value) const;
        ///< set or change value
    void_t             remove() const;
        ///< delete var

private:
    static std::csize_t    _envMax();
        ///< maximum permissible string length of an environment variable
	static std::ctstring_t _envsSeparator();
		///< vars separator

    std::ctstring_t _nsName; ///< Like a "namespace" prefix + variable name

    bool_t _isNameValid() const;
        ///< is valid environment variable name
    bool_t _isValueValid(std::ctstring_t &value) const;
        ///< is valid environment variable value

xPLATFORM_IMPL:
    bool_t         _isExists_impl() const;
    std::tstring_t _value_impl() const;
    void_t         _setValue_impl(std::ctstring_t &value) const;
    void_t         _remove_impl() const;
};
//-------------------------------------------------------------------------------------------------
class Envs
	/// system environment variables
{
public:
///\name ctors, dtor
///\{
			 Envs();
	explicit Envs(std::ctstring_t &ns);
	virtual ~Envs() = default;

	xNO_COPY_ASSIGN(Envs);
///\}

///\name Setters
///\{
	void_t setVars(std::ctstring_t &envFilePath) const;
		///< set or change values from env file (for example ".env")
	void_t setVars(const std::map_tstring_t &vars) const;
		///< set or change values
///\}

///\name Getters
///\{
	std::map_tstring_t vars() const;
		///< get all values
	std::tstring_t     findFirstOf(std::cvec_tstring_t &names) const;
		///< get first value by names
	std::tstring_t     operator [] (std::ctstring_t &name) const;
		///< get value by name
///\}

xPUBLIC_STATIC:
    static std::tstring_t expandVars(std::ctstring_t &strWithVars);
        ///< expands strings by separator "%"
        ///< \win Same as ExpandEnvironmentStrings()

private:
    std::ctstring_t _ns; ///< Like a "namespace" prefix

xPLATFORM_IMPL:
    std::vec_tstring_t _vars_impl() const;
        ///< variables with values (DESKTOP_SESSION=xfce, ...)
};
//-------------------------------------------------------------------------------------------------

} // namespace
//-------------------------------------------------------------------------------------------------
/**
 * \file  Env.h
 * \todo
 *
 * - [ ] Dll path (LD_LIBRARY_PATH)
 *
 * Imports - https://docs.conan.io/en/latest/using_packages/conanfile_txt.html#imports-txt
 * There are some differences between shared libraries on Linux (*.so), Windows (*.dll) and
 * MacOS (*.dylib). The shared libraries must be located in a folder where they can be found,
 * either by the linker, or by the OS runtime.
 * You can add the libraries’ folders to the path (LD_LIBRARY_PATH environment variable in Linux,
 * DYLD_LIBRARY_PATH in OSX, or system PATH in Windows), or copy those shared libraries to
 * some system folder where they can be found by the OS. But these operations are only related
 * to the deployment or installation of apps; they are not relevant during development.
 * Conan is intended for developers, so it avoids such manipulation of the OS environment.
 * In Windows and OSX, the simplest approach is to copy the shared libraries to the executable
 * folder, so they are found by the executable, without having to modify the path.
 *
 * - [ ] Default values
 * - [ ] .env file - ok with commets, empty line
 *
 * \done
 *
 * - Prefix for name
 */
//-------------------------------------------------------------------------------------------------
