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

typedef std::map<std::tstring, std::tstring> TLocalStorage;

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
        bool                   bCreateDefault (const std::tstring &csContent) const;
            ///< create default file
        std::tstring           sGetPath       () const;
            ///< get file path
        bool                   bSetPath       (const std::tstring &csFilePath);
            ///< set file path
        NxLib::TLocalStorage & cmsGet         ();
            ///< get innner TLocalStorage, may be used with bFlush

        bool                   bFlush         () const;
            ///< flush
        bool                   bClear         ();
            ///< clear content
        bool                   bDelete        ();
            ///< delete

        //key
        bool                   bKeyIsExists   (const std::tstring &csKey) const;
            ///< is exists

        std::tstring           sKeyReadString (const std::tstring &csKey, const std::tstring &csDefaultValue);
            ///< read std::tstring
        bool                   bKeyWriteString(const std::tstring &csKey, const std::tstring &csValue);
            ///< write std::tstring

        LONG                   iKeyReadInt    (const std::tstring &csKey, const LONG     cliDefaultValue);
            ///< read int
        bool                   bKeyWriteInt   (const std::tstring &csKey, const LONG     cliValue);
            ///< write int

        double                 dKeyReadFloat  (const std::tstring &csKey, const double   cdDefaultValue);
            ///< read float
        bool                   bKeyWriteFloat (const std::tstring &csKey, const double   cdValue);
            ///< write float

        bool                   bKeyReadBool   (const std::tstring &csKey, const bool     cbDefaultValue);
            ///< read bool
        bool                   bKeyWriteBool  (const std::tstring &csKey, const bool     cbValue);
            ///< write bool

        std::ustring           usKeyReadBin   (const std::tstring &csKey, const std::ustring &cusDefaultValue);
            ///< write std::ustring
        bool                   bKeyWriteBin   (const std::tstring &csKey, const std::ustring &cusValue);
            ///< read std::ustring

        bool                   bKeyClear      (const std::tstring &csKey);
            ///< clear value
        bool                   bKeyDelete     (const std::tstring &csKey);
            ///< delete key and value

    private:
        const std::tstring     _m_csSeparator;  ///< separator between key and value
        const std::tstring     _m_csFileExt;    ///< ini-file extension

        std::tstring           _m_sFilePath;    ///< file path to ini-file
        NxLib::TLocalStorage   _m_msIni;        ///< std::map of keys and values

        bool                   _bRead         (const std::tstring &csKey, const std::tstring &csDefaultValue, std::tstring *psValue);
            ///< parse file
        bool                   _bWrite        (const std::tstring &csKey, const std::tstring &csValue);
            ///< flush to TLocalStorage, file
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxLocalStorageH
