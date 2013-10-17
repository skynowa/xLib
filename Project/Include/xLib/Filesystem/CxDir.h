/**
 * \file  CxDir.h
 * \brief directory
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Core/CxConst.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxDir :
    private CxNonCopyable
    /// directory
{
public:
    explicit              CxDir(std::ctstring_t &dirPath);
        ///< constructor
    virtual              ~CxDir();
        ///< destructor

    std::ctstring_t &     dirPath() const xWARN_UNUSED_RV;
        ///< directory path

    bool_t                isExists() xWARN_UNUSED_RV;
        ///< check for existence
    bool_t                isEmpty(std::ctstring_t &shellFilter = CxConst::xMASK_ALL) xWARN_UNUSED_RV;
        ///< is empty
    bool_t                isRoot() xWARN_UNUSED_RV;
        ///< is root
    bool_t                isDir() xWARN_UNUSED_RV;
        ///< is dir
    void_t                create();
        ///< create
    void_t                pathCreate();
        ///< creation of all directories that not exists in path
    void_t                copy(std::ctstring_t &dirPathTo, cbool_t &failIfExists);
        ///< copy
    void_t                move(std::ctstring_t &dirPathTo, cbool_t &failIfExists);
        ///< move

    void_t                remove();
        ///< deletion dir which empty
    void_t                tryRemove(std::csize_t &attempts, culong_t &timeoutMsec);
        ///< try deleting, max 100 attempts
    void_t                pathClear();
        ///< deletion all content of dir
    void_t                pathDelete();
        ///< deletion dir find all content of it

    // static
    static std::tstring_t current() xWARN_UNUSED_RV;
        ///< get current
    static void_t         setCurrent(std::ctstring_t &dirPath);
        ///< set current
    static std::tstring_t temp() xWARN_UNUSED_RV;
        ///< get path to system var %Temp%

private:
    std::ctstring_t       _dirPath;
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <Filesystem/CxDir.cpp>
#endif
