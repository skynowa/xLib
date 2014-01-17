/**
 * \file  CxLocalStorage.h
 * \brief local storage
 */


#pragma once

#ifndef xLib_CxLocalStorageH
#define xLib_CxLocalStorageH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN(xlib)

typedef std::map_tstring_t local_storage_t;

class CxLocalStorage
    /// local storage
{
public:
                      CxLocalStorage();
        ///< constructor, exe-file path
    explicit          CxLocalStorage(std::ctstring_t &filePath);
        ///< constructor, file path
    virtual          ~CxLocalStorage();
        ///< destructor

    // creation
    void_t            createDefault(std::ctstring_t &content) const;
        ///< create default file
    std::ctstring_t & path() const xWARN_UNUSED_RV;
        ///< get file path
    void_t            setPath(std::ctstring_t &filePath);
        ///< set file path
    local_storage_t & get() xWARN_UNUSED_RV;
        ///< get inner local_storage_t, may be used with bFlush

    void_t            flush() const;
        ///< flush
    void_t            clear();
        ///< clear content
    void_t            remove();
        ///< delete

    // key
    bool_t            keyIsExists(std::ctstring_t &key) const xWARN_UNUSED_RV;
        ///< is exists

    std::tstring_t    keyReadString(std::ctstring_t &key, std::ctstring_t &defaultValue)
                          xWARN_UNUSED_RV;
        ///< read std::tstring_t
    void_t            keyWriteString(std::ctstring_t &key, std::ctstring_t &value);
        ///< write std::tstring_t

    long_t            keyReadInt(std::ctstring_t &key, clong_t &defaultValue) xWARN_UNUSED_RV;
        ///< read int_t
    void_t            keyWriteInt(std::ctstring_t &key, clong_t &value);
        ///< write int_t

    double            keyReadFloat(std::ctstring_t &key, cdouble_t &defaultValue)
                          xWARN_UNUSED_RV;
        ///< read float_t
    void_t            keyWriteFloat(std::ctstring_t &key, cdouble_t &value);
        ///< write float_t

    bool_t            keyReadBool(std::ctstring_t &key, cbool_t &defaultValue) xWARN_UNUSED_RV;
        ///< read bool_t
    void_t            keyWriteBool(std::ctstring_t &key, cbool_t &value);
        ///< write bool_t

    std::ustring_t    keyReadBin(std::ctstring_t &key, std::custring_t &defaultValue)
                          xWARN_UNUSED_RV;
        ///< write std::ustring_t
    void_t            keyWriteBin(std::ctstring_t &key, std::custring_t &value);
        ///< read std::ustring_t

    void_t            keyClear(std::ctstring_t &key);
        ///< clear value
    void_t            keyDelete(std::ctstring_t &key);
        ///< delete key and value

private:
    std::ctstring_t   _separator;  ///< separator between key and value
    std::ctstring_t   _fileExt;    ///< ini-file extension

    std::tstring_t    _filePath;    ///< file path to ini-file
    local_storage_t   _ini;        ///< std::map of keys and values

    void_t            _read(std::ctstring_t &key, std::ctstring_t &defaultValue,
                          std::tstring_t *value);
        ///< parse file
    void_t            _write(std::ctstring_t &key, std::ctstring_t &value);
        ///< flush to local_storage_t, file

    xNO_COPY_ASSIGN(CxLocalStorage)
};

xNAMESPACE_END(xlib)
//-------------------------------------------------------------------------------------------------
#include "CxLocalStorage.inl"
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxLocalStorageH
