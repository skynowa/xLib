/**
 * \file  Config.h
 * \brief config file
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, fs)

class Config
    /// config file
{
public:
                      Config();
        ///< constructor, exe-file path
    explicit          Config(std::ctstring_t &filePath);
        ///< constructor, file path
    virtual          ~Config();
        ///< destructor

///@name Creations
///@{
    void_t            createDefault(std::cmap_tstring_t &content) const;
        ///< create default file
    std::ctstring_t & path() const xWARN_UNUSED_RV;
        ///< get file path
    void_t            setPath(std::ctstring_t &filePath);
        ///< set file path
    std::map_tstring_t & get() xWARN_UNUSED_RV;
        ///< get inner local_storage_t, may be used with bFlush

    void_t            read();
        ///< parse file
    void_t            save() const;
        ///< save
    void_t            clear();
        ///< clear content
    void_t            remove();
        ///< delete
///@}

///@name Key's actions
///@{
    bool_t            keyIsExists(std::ctstring_t &key) const xWARN_UNUSED_RV;
        ///< is exists
    void_t            keyClear(std::ctstring_t &key);
        ///< clear value
    void_t            keyDelete(std::ctstring_t &key);
        ///< delete key and value
///@}

///@name Get/set values
///@{
    std::tstring_t    value(std::ctstring_t &key, cptr_ctchar_t defaultValue)
                          xWARN_UNUSED_RV;
    void_t            setValue(std::ctstring_t &key, cptr_ctchar_t value);

    std::tstring_t    value(std::ctstring_t &key, std::ctstring_t &defaultValue)
                          xWARN_UNUSED_RV;
    void_t            setValue(std::ctstring_t &key, std::ctstring_t &value);

    long_t            value(std::ctstring_t &key, clong_t &defaultValue) xWARN_UNUSED_RV;
    void_t            setValue(std::ctstring_t &key, clong_t &value);

    double            value(std::ctstring_t &key, cdouble_t &defaultValue)
                          xWARN_UNUSED_RV;
    void_t            setValue(std::ctstring_t &key, cdouble_t &value);

    bool_t            value(std::ctstring_t &key, cbool_t &defaultValue) xWARN_UNUSED_RV;
    void_t            setValue(std::ctstring_t &key, cbool_t &value);

    std::ustring_t    value(std::ctstring_t &key, std::custring_t &defaultValue)
                          xWARN_UNUSED_RV;
    void_t            setValue(std::ctstring_t &key, std::custring_t &value);
///@}

private:
    std::ctstring_t    _separator;  ///< separator between key and value
    std::ctstring_t    _fileExt;    ///< file extension

    std::tstring_t     _filePath;   ///< file path to file
    std::map_tstring_t _config;     ///< std::map of keys and values

    xNO_COPY_ASSIGN(Config)
};

xNAMESPACE_END2(xl, fs)
//-------------------------------------------------------------------------------------------------
