/**
 * \file  Dir.h
 * \brief directory
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Const.h>
#include <xLib/Interface/IPrinter.h>
#include <xLib/Interface/IStr.h>
//-------------------------------------------------------------------------------------------------
namespace xl::fs
{

class Dir final :
	public IPrinter<std::tostream_t>,
	public IStrConstRef
    /// directory
{
public:
///\name ctors, dtor
///\{
	explicit  Dir(std::ctstring_t &dirPath);
	virtual  ~Dir() = default;

	xNO_DEFAULT_CONSTRUCT(Dir);
	xNO_COPY_ASSIGN(Dir);

	static Dir current();
	static Dir temp();
///\}

///\name Overrides
///\{
	void_t            print(std::tostream_t &stream) const final;
    std::ctstring_t & str() const final;
///\}


    bool_t isExists() const;
        ///< check for existence
    bool_t isEmpty(std::ctstring_t &shellFilter = Const::maskAll()) const;
        ///< is empty
    bool_t isRoot() const;
        ///< is root
    void_t create() const;
        ///< create
    void_t pathCreate() const;
        ///< creation of all directories that not exists in path
    void_t copy(std::ctstring_t &dirPathTo, cbool_t failIfExists) const;
        ///< copy
    void_t move(std::ctstring_t &dirPathTo, cbool_t failIfExists) const;
        ///< move
    void_t createSymlink(std::ctstring_t &dirPathTo) const;
        ///< create symlink

    void_t remove() const;
        ///< deletion dir which empty
    void_t tryRemove(std::csize_t attempts, culong_t timeoutMsec) const;
        ///< try deleting, max 100 attempts
    void_t pathClear() const;
        ///< deletion all content of dir
    void_t pathDelete() const;
        ///< deletion dir find all content of it

xPUBLIC_STATIC:
    static void_t setCurrent(std::ctstring_t &dirPath);
        ///< set current

private:
    std::ctstring_t _dirPath;

xPLATFORM_IMPL:
    // static
	static std::ctstring_t _dirTmp();
		///< temporary directory path
    static std::tstring_t  _current_impl();
    static void_t          _setCurrent_impl(std::ctstring_t &dirPath);
    static std::tstring_t  _temp_impl();

    bool_t          _isRoot_impl() const;
    void_t          _create_impl() const;
    void_t          _createSymlink_impl(std::ctstring_t &dirPathTo) const;
    void_t          _remove_impl() const;
    bool_t          _tryRemove_impl() const;
};

} // namespace
//-------------------------------------------------------------------------------------------------
