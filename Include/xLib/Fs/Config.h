/**
 * \file  Config.h
 * \brief config file
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/String.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, fs)

class Config
    /// config file
{
public:
                      Config();
        ///< exe-file path
    explicit          Config(std::ctstring_t &filePath);
        ///< file path
    virtual          ~Config();
        ///< destructor

///@name Creations
///@{
    std::ctstring_t & path() const;
        ///< get file path
    void_t            setPath(std::ctstring_t &filePath);
        ///< set file path
    std::map_tstring_t & get();
        ///< get inner local_storage_t, may be used with bFlush

    void_t            read();
        ///< parse file
    void_t            save() const;
        ///< save
    void_t            saveDefault(std::cmap_tstring_t &content);
        ///< save default file
    void_t            clear();
        ///< clear content
    void_t            remove();
        ///< delete
///@}

///@name Key's actions
///@{
    bool_t            keyIsExists(std::ctstring_t &key) const;
        ///< is exists
    void_t            keyClear(std::ctstring_t &key);
        ///< clear value
    void_t            keyDelete(std::ctstring_t &key);
        ///< delete key and value
///@}

///@name Get/set values
///@{
    template<typename T>
    T                 value(std::ctstring_t &key, const T defaultValue);
    template<typename T>
    void_t            setValue(std::ctstring_t &key, const T value);
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
#include "Config.inl"
