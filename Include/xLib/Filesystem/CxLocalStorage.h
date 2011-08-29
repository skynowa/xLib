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
    typedef std::map<std::tstring, std::tstring> TLocalStorage;
}

class CxLocalStorage :
    public CxNonCopyable
    /// local storage
{
    public:
                               CxLocalStorage ();
            ///< constructor, exe-file path
        explicit               CxLocalStorage (const std::tstring &csFilePath);
        	///< constructor, file path
        virtual               ~CxLocalStorage ();
        	///< destructor

        //creation
        BOOL                   bCreateDefault (const std::tstring &csContent) const;
    		///< create default file
        std::tstring           sGetPath       () const;
    		///< get file path
        BOOL                   bSetPath       (const std::tstring &csFilePath);
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
        BOOL                   bKeyIsExists   (const std::tstring &csKey) const;
    		///< is exists

        std::tstring           sKeyReadString (const std::tstring &csKey, const std::tstring &csDefaultValue);
    		///< read std::tstring
        BOOL                   bKeyWriteString(const std::tstring &csKey, const std::tstring &csValue);
    		///< write std::tstring

        LONG                   iKeyReadInt    (const std::tstring &csKey, const LONG     cliDefaultValue);
    		///< read INT
        BOOL                   bKeyWriteInt   (const std::tstring &csKey, const LONG     cliValue);
    		///< write INT

        DOUBLE                 dKeyReadFloat  (const std::tstring &csKey, const DOUBLE   cdDefaultValue);
    		///< read FLOAT
        BOOL                   bKeyWriteFloat (const std::tstring &csKey, const DOUBLE   cdValue);
    		///< write FLOAT

        BOOL                   bKeyReadBool   (const std::tstring &csKey, const BOOL     cbDefaultValue);
    		///< read BOOL
        BOOL                   bKeyWriteBool  (const std::tstring &csKey, const BOOL     cbValue);
    		///< write BOOL

        std::ustring           usKeyReadBin   (const std::tstring &csKey, const std::ustring &cusDefaultValue);
    		///< write std::ustring
        BOOL                   bKeyWriteBin   (const std::tstring &csKey, const std::ustring &cusValue);
    		///< read std::ustring

        BOOL                   bKeyClear      (const std::tstring &csKey);
    		///< clear value
        BOOL                   bKeyDelete     (const std::tstring &csKey);
    		///< delete key and value

    private:
        const std::tstring     _m_csSeparator;  ///< separator between key and value
        const std::tstring     _m_csFileExt;    ///< ini-file extension

        mutable BOOL           _m_bRes;         ///< for private use
        std::tstring           _m_sFilePath;    ///< file path to ini-file
        NxLib::TLocalStorage   _m_msIni;        ///< std::map of keys and values

        BOOL                   _bRead         (const std::tstring &csKey, const std::tstring &csDefaultValue, std::tstring *psValue);
    		///< parse file
        BOOL                   _bWrite        (const std::tstring &csKey, const std::tstring &csValue);
    		///< flush to TLocalStorage, file
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxLocalStorageH
