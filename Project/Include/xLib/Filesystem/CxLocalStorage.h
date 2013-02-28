/**
 * \file  CxLocalStorage.h
 * \brief local storage
 */


#ifndef xLib_Filesystem_CxLocalStorageH
#define xLib_Filesystem_CxLocalStorageH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

typedef std::map_tstring_t local_storage_t;

class CxLocalStorage :
    private CxNonCopyable
    /// local storage
{
public:
                           CxLocalStorage();
        ///< constructor, exe-file path
    explicit               CxLocalStorage(std::ctstring_t &csFilePath);
        ///< constructor, file path
    virtual               ~CxLocalStorage();
        ///< destructor

    // creation
    void                   createDefault (std::ctstring_t &csContent) const;
        ///< create default file
    std::ctstring_t & path          () const xWARN_UNUSED_RV;
        ///< get file path
    void                   setPath       (std::ctstring_t &csFilePath);
        ///< set file path
    local_storage_t &      get           () xWARN_UNUSED_RV;
        ///< get inner local_storage_t, may be used with bFlush

    void                   flush         () const;
        ///< flush
    void                   clear         ();
        ///< clear content
    void                   remove        ();
        ///< delete

    // key
    bool_t                   keyIsExists   (std::ctstring_t &csKey) const xWARN_UNUSED_RV;
        ///< is exists

    std::tstring_t         keyReadString (std::ctstring_t &csKey, std::ctstring_t &csDefaultValue) xWARN_UNUSED_RV;
        ///< read std::tstring_t
    void                   keyWriteString(std::ctstring_t &csKey, std::ctstring_t &csValue);
        ///< write std::tstring_t

    long_t                 keyReadInt    (std::ctstring_t &csKey, clong_t &cliDefaultValue) xWARN_UNUSED_RV;
        ///< read int_t
    void                   keyWriteInt   (std::ctstring_t &csKey, clong_t &cliValue);
        ///< write int_t

    double                 keyReadFloat  (std::ctstring_t &csKey, cdouble_t &cdDefaultValue) xWARN_UNUSED_RV;
        ///< read float_t
    void                   keyWriteFloat (std::ctstring_t &csKey, cdouble_t &cdValue);
        ///< write float_t

    bool_t                   keyReadBool   (std::ctstring_t &csKey, cbool_t &cbDefaultValue) xWARN_UNUSED_RV;
        ///< read bool_t
    void                   keyWriteBool  (std::ctstring_t &csKey, cbool_t &cbValue);
        ///< write bool_t

    std::ustring_t         keyReadBin    (std::ctstring_t &csKey, std::custring_t &cusDefaultValue) xWARN_UNUSED_RV;
        ///< write std::ustring_t
    void                   keyWriteBin   (std::ctstring_t &csKey, std::custring_t &cusValue);
        ///< read std::ustring_t

    void                   keyClear      (std::ctstring_t &csKey);
        ///< clear value
    void                   keyDelete     (std::ctstring_t &csKey);
        ///< delete key and value

private:
    std::ctstring_t   _m_csSeparator;  ///< separator between key and value
    std::ctstring_t   _m_csFileExt;    ///< ini-file extension

    std::tstring_t         _m_sFilePath;    ///< file path to ini-file
    local_storage_t        _m_msIni;        ///< std::map of keys and values

    void                   _read         (std::ctstring_t &csKey, std::ctstring_t &csDefaultValue, std::tstring_t *psValue);
        ///< parse file
    void                   _write        (std::ctstring_t &csKey, std::ctstring_t &csValue);
        ///< flush to local_storage_t, file
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Filesystem_CxLocalStorageH
