/**
 * \file  CxLocalStorage.h
 * \brief local storage
 */


#ifndef xLib_Filesystem_CxLocalStorageH
#define xLib_Filesystem_CxLocalStorageH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
namespace NxLib {
    typedef std::map<std::string_t, std::string_t> TLocalStorage;
}

class CxLocalStorage :
    public CxNonCopyable
    /// local storage
{
    public:
                               CxLocalStorage ();
            ///< constructor, exe-file path
        explicit               CxLocalStorage (const std::string_t &csFilePath);
        	///< constructor, file path
        virtual               ~CxLocalStorage ();
        	///< destructor

        //creation
        BOOL                   bCreateDefault (const std::string_t &csContent) const;
    		///< create default file
        std::string_t           sGetPath       () const;
    		///< get file path
        BOOL                   bSetPath       (const std::string_t &csFilePath);
    		///< set file path
        NxLib::TLocalStorage & cmsGet         ();
    		///< get innner TLocalStorage, may be used with bFlush

        BOOL                   bFlush         () const;
    		///< flush
        BOOL                   bClear         ();
    		///< clear content
        BOOL                   bDelete        ();
    		///< delete

        //key
        BOOL                   bKeyIsExists   (const std::string_t &csKey) const;
    		///< is exists

        std::string_t           sKeyReadString (const std::string_t &csKey, const std::string_t &csDefaultValue);
    		///< read std::string_t
        BOOL                   bKeyWriteString(const std::string_t &csKey, const std::string_t &csValue);
    		///< write std::string_t

        LONG                   iKeyReadInt    (const std::string_t &csKey, const LONG     cliDefaultValue);
    		///< read INT
        BOOL                   bKeyWriteInt   (const std::string_t &csKey, const LONG     cliValue);
    		///< write INT

        DOUBLE                 dKeyReadFloat  (const std::string_t &csKey, const DOUBLE   cdDefaultValue);
    		///< read FLOAT
        BOOL                   bKeyWriteFloat (const std::string_t &csKey, const DOUBLE   cdValue);
    		///< write FLOAT

        BOOL                   bKeyReadBool   (const std::string_t &csKey, const BOOL     cbDefaultValue);
    		///< read BOOL
        BOOL                   bKeyWriteBool  (const std::string_t &csKey, const BOOL     cbValue);
    		///< write BOOL

        std::ustring           usKeyReadBin   (const std::string_t &csKey, const std::ustring &cusDefaultValue);
    		///< write std::ustring
        BOOL                   bKeyWriteBin   (const std::string_t &csKey, const std::ustring &cusValue);
    		///< read std::ustring

        BOOL                   bKeyClear      (const std::string_t &csKey);
    		///< clear value
        BOOL                   bKeyDelete     (const std::string_t &csKey);
    		///< delete key and value

    private:
        const std::string_t     _m_csSeparator;  ///< separator between key and value
        const std::string_t     _m_csFileExt;    ///< ini-file extension

        std::string_t           _m_sFilePath;    ///< file path to ini-file
        NxLib::TLocalStorage   _m_msIni;        ///< std::map of keys and values

        BOOL                   _bRead         (const std::string_t &csKey, const std::string_t &csDefaultValue, std::string_t *psValue);
    		///< parse file
        BOOL                   _bWrite        (const std::string_t &csKey, const std::string_t &csValue);
    		///< flush to TLocalStorage, file
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxLocalStorageH
