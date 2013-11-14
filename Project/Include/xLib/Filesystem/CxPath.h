/**
 * \file  CxPath.h
 * \brief file system path
 */


#pragma once

#ifndef xLib_CxPathH
#define xLib_CxPathH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxPath
    /// file system path
{
public:
    enum ExStandartExt
        /// standard extension
    {
        seExe,  ///< execute module
        seDll,  ///< dynamically linked shared library
        seLib,  ///< static library
        seObj,  ///< object file
        seShell ///< shell script file
    };

    explicit              CxPath(std::ctstring_t &filePath);
        ///< constructor
    virtual              ~CxPath() {}
        ///< destructor

    std::ctstring_t &     filePath() const xWARN_UNUSED_RV;
        ///< file path

#if xOS_ENV_WIN
    std::tstring_t        drive() const xWARN_UNUSED_RV;
        ///< get drive
#endif
    std::tstring_t        dir() const xWARN_UNUSED_RV;
        ///< get dir path, without a trailing backslash '\'
    std::tstring_t        dirName() const xWARN_UNUSED_RV;
        ///< get dir name
    std::tstring_t        fileName() const xWARN_UNUSED_RV;
        ///< get name.extension
    std::tstring_t        fileBaseName() const xWARN_UNUSED_RV;
        ///< get name without extension
    std::tstring_t        ext() const xWARN_UNUSED_RV;
        ///< get extension

#if xOS_ENV_WIN
    std::tstring_t        setDrive(std::ctstring_t &drivePath) xWARN_UNUSED_RV;
        ///< set drive
#endif
    std::tstring_t        setDir(std::ctstring_t &dirPath) xWARN_UNUSED_RV;
        ///< set dir
    std::tstring_t        setFileName(std::ctstring_t &fullName) xWARN_UNUSED_RV;
        ///< set full name
    std::tstring_t        setFileBaseName(std::ctstring_t &name) xWARN_UNUSED_RV;
        ///< set name
    std::tstring_t        setExt(std::ctstring_t &ext) xWARN_UNUSED_RV;
        ///< set extension

    std::tstring_t        removeExt() xWARN_UNUSED_RV;
        ///< remove extension
    std::tstring_t        removeExtIf(std::ctstring_t &ext) xWARN_UNUSED_RV;
        ///< remove extension if it equal some string


    bool_t                isAbsolute() const xWARN_UNUSED_RV;
        ///< is absolute

    std::tstring_t        toWin(cbool_t &isSlashAtEnd) const xWARN_UNUSED_RV;
        ///< convert slashes to Windows style
    std::tstring_t        toUnix(cbool_t &isSlashAtEnd) const xWARN_UNUSED_RV;
        ///< convert slashes to Nix style
    std::tstring_t        toNative(cbool_t &isSlashAtEnd) const xWARN_UNUSED_RV;
        ///< convert slashes to native style
    std::tstring_t        absolute() const xWARN_UNUSED_RV;
        ///< get absolute path
    std::tstring_t        brief(std::csize_t &maxSize) const xWARN_UNUSED_RV;
        ///< get short path

    std::tstring_t        slashAppend() const xWARN_UNUSED_RV;
        ///< append slash
    std::tstring_t        slashRemove() const xWARN_UNUSED_RV;
        ///< remove slash

    // static
    static std::tstring_t exe() xWARN_UNUSED_RV;
        ///< get full path to exe
    static std::tstring_t exeDir() xWARN_UNUSED_RV;
        ///< get dir path to exe
    static std::tstring_t dll() xWARN_UNUSED_RV;
        ///< get full path to dll
    static std::tstring_t standartExt(const ExStandartExt &fileExt) xWARN_UNUSED_RV;
        ///< get standard extension

    static bool_t         isValid(std::ctstring_t &filePath) xWARN_UNUSED_RV;
        ///< path validation
    static bool_t         isNameValid(std::ctstring_t &fileName) xWARN_UNUSED_RV;
        ///< name validation

    static std::tstring_t shortName(std::ctstring_t &fileName, std::csize_t &maxSize)
                              xWARN_UNUSED_RV;
        ///< get short name
    static std::tstring_t setNameValid(std::ctstring_t &fileName) xWARN_UNUSED_RV;
        ///< set name as valid

    static size_t         maxSize();
        ///< get max path length in symbols
    static size_t         nameMaxSize();
        ///< get max name length in symbols

#if !xOS_ENV_WIN
    static void_t         proc(std::ctstring_t &procPath, std::vec_tstring_t *data);
        ///< get from UNIX proc file content
    static std::tstring_t procValue(std::ctstring_t &procPath, std::ctstring_t &data)
                              xWARN_UNUSED_RV;
        ///< get from UNIX proc file content value by data
#endif

private:
    std::tstring_t        _filePath;

xNO_COPY_ASSIGN(CxPath)
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------------------------------
#include "CxPath.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxPathH
