/**
 * \file  CxLocalStorage.h
 * \brief local storage
 */


#ifndef xLib_Filesystem_CxLocalStorageH
#define xLib_Filesystem_CxLocalStorageH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

typedef std::map_tstring_t local_storage_t;

class CxLocalStorage :
    private CxNonCopyable
    /// local storage
{
public:
                           CxLocalStorage();
        ///< constructor, exe-file path
    explicit               CxLocalStorage(const std::tstring_t &csFilePath);
        ///< constructor, file path
    virtual               ~CxLocalStorage();
        ///< destructor

    //creation
    void                   createDefault (const std::tstring_t &csContent) const;
        ///< create default file
    const std::tstring_t & path          () const;
        ///< get file path
    void                   setPath       (const std::tstring_t &csFilePath);
        ///< set file path
    local_storage_t &      get           ();
        ///< get inner local_storage_t, may be used with bFlush

    void                   flush         () const;
        ///< flush
    void                   clear         ();
        ///< clear content
    void                   remove        ();
        ///< delete

    //key
    bool                   keyIsExists   (const std::tstring_t &csKey) const;
        ///< is exists

    std::tstring_t         keyReadString (const std::tstring_t &csKey, const std::tstring_t &csDefaultValue);
        ///< read std::tstring_t
    void                   keyWriteString(const std::tstring_t &csKey, const std::tstring_t &csValue);
        ///< write std::tstring_t

    long_t                 keyReadInt    (const std::tstring_t &csKey, const long_t &cliDefaultValue);
        ///< read int
    void                   keyWriteInt   (const std::tstring_t &csKey, const long_t &cliValue);
        ///< write int

    double                 keyReadFloat  (const std::tstring_t &csKey, const double &cdDefaultValue);
        ///< read float
    void                   keyWriteFloat (const std::tstring_t &csKey, const double &cdValue);
        ///< write float

    bool                   keyReadBool   (const std::tstring_t &csKey, const bool &cbDefaultValue);
        ///< read bool
    void                   keyWriteBool  (const std::tstring_t &csKey, const bool &cbValue);
        ///< write bool

    std::ustring_t         keyReadBin    (const std::tstring_t &csKey, const std::ustring_t &cusDefaultValue);
        ///< write std::ustring_t
    void                   keyWriteBin   (const std::tstring_t &csKey, const std::ustring_t &cusValue);
        ///< read std::ustring_t

    void                   keyClear      (const std::tstring_t &csKey);
        ///< clear value
    void                   keyDelete     (const std::tstring_t &csKey);
        ///< delete key and value

private:
    const std::tstring_t   _m_csSeparator;  ///< separator between key and value
    const std::tstring_t   _m_csFileExt;    ///< ini-file extension

    std::tstring_t         _m_sFilePath;    ///< file path to ini-file
    local_storage_t        _m_msIni;        ///< std::map of keys and values

    void                   _read         (const std::tstring_t &csKey, const std::tstring_t &csDefaultValue, std::tstring_t *psValue);
        ///< parse file
    void                   _write        (const std::tstring_t &csKey, const std::tstring_t &csValue);
        ///< flush to local_storage_t, file
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Filesystem_CxLocalStorageH
