/**
 * \file  Config.h
 * \brief config file
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Interface/IGet.h>
#include <xLib/Fs/FileInfo.h>
#include <xLib/Fs/FileText.h>
//-------------------------------------------------------------------------------------------------
namespace xl::fs
{

class Config :
	public IGetRef<std::map_tstring_t>
    /// config file
{
public:
///\name ctors, dtor
///\{
			  Config();
	explicit  Config(std::ctstring_t &filePath);
	virtual  ~Config();

	xNO_COPY_ASSIGN(Config);
///\}

///\name Overrides
///\{
	std::map_tstring_t & get() final;
///\}

///\name File's
///\{
    void_t read();
        ///< parse file
    void_t write() const;
        ///< write
    void_t writeDefault(std::cmap_tstring_t &content);
        ///< write default file
    void_t clear();
        ///< clear content
    void_t remove();
        ///< delete
///\}

///\name Key's
///\{
    bool_t keyIsExists(std::ctstring_t &key) const;
        ///< is exists
    void_t keyClear(std::ctstring_t &key);
        ///< clear value
    void_t keyDelete(std::ctstring_t &key);
        ///< delete key and value
///\}

///\name Get/set values
///\{
    template<typename T>
    T      value(std::ctstring_t &key, const T defaultValue);
    template<typename T>
    void_t setValue(std::ctstring_t &key, const T value);
///\}

xPRIVATE_STATIC:
    static std::ctstring_t _separator; ///< separator between key and value

private:
    FileInfo           _fileInfo;
    FileText           _file;
    std::map_tstring_t _config; ///< std::map of keys and values
};

} // namespace
//-------------------------------------------------------------------------------------------------
#include "Config.inl"
