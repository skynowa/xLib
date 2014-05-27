/**
 * \file  CxDir.h
 * \brief directory
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Core/CxConst.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, filesystem)

class CxDir
    /// directory
{
public:
    explicit          CxDir(std::ctstring_t &dirPath);
        ///< constructor
    virtual          ~CxDir() {}
        ///< destructor

    std::ctstring_t & dirPath() const xWARN_UNUSED_RV;
        ///< directory path

    bool_t            isExists() const xWARN_UNUSED_RV;
        ///< check for existence
    bool_t            isEmpty(std::ctstring_t &shellFilter = CxConst::maskAll()) const
                          xWARN_UNUSED_RV;
        ///< is empty
    bool_t            isRoot() const xWARN_UNUSED_RV;
        ///< is root
    bool_t            isDir() const xWARN_UNUSED_RV;
        ///< is dir
    void_t            create() const;
        ///< create
    void_t            pathCreate() const;
        ///< creation of all directories that not exists in path
    void_t            copy(std::ctstring_t &dirPathTo, cbool_t &failIfExists) const;
        ///< copy
    void_t            move(std::ctstring_t &dirPathTo, cbool_t &failIfExists) const;
        ///< move

    void_t            remove() const;
        ///< deletion dir which empty
    void_t            tryRemove(std::csize_t &attempts, culong_t &timeoutMsec) const;
        ///< try deleting, max 100 attempts
    void_t            pathClear() const;
        ///< deletion all content of dir
    void_t            pathDelete() const;
        ///< deletion dir find all content of it

    // static
    static
    std::tstring_t    current() xWARN_UNUSED_RV;
        ///< get current
    static
    void_t            setCurrent(std::ctstring_t &dirPath);
        ///< set current
    static
    std::tstring_t    temp() xWARN_UNUSED_RV;
        ///< get path to system var %Temp%

private:
    std::ctstring_t   _dirPath;

    xNO_COPY_ASSIGN(CxDir)

xPLATFORM:
    bool_t            _isRoot_impl() const xWARN_UNUSED_RV;
    void_t            _create_impl() const;
    void_t            _remove_impl() const;
    bool_t            _tryRemove_impl() const;

    // static
    static
    std::tstring_t    _current_impl() xWARN_UNUSED_RV;
    static
    void_t            _setCurrent_impl(std::ctstring_t &dirPath);
    static
    std::tstring_t    _temp_impl() xWARN_UNUSED_RV;
};

xNAMESPACE_END2(xlib, filesystem)
//-------------------------------------------------------------------------------------------------
#include "CxDir.inl"
