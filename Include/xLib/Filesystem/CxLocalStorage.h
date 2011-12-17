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

typedef std::map<std::tstring_t, std::tstring_t> TLocalStorage;

class CxLocalStorage :
    private CxNonCopyable
    /// local storage
{
    public:
                               CxLocalStorage ();
            ///< constructor, exe-file path
        explicit               CxLocalStorage (const std::tstring_t &csFilePath);
            ///< constructor, file path
        virtual               ~CxLocalStorage ();
            ///< destructor

        //creation
        bool                   bCreateDefault (const std::tstring_t &csContent) const;
            ///< create default file
        std::tstring_t         sGetPath       () const;
            ///< get file path
        bool                   bSetPath       (const std::tstring_t &csFilePath);
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
        bool                   bKeyIsExists   (const std::tstring_t &csKey) const;
            ///< is exists

        std::tstring_t         sKeyReadString (const std::tstring_t &csKey, const std::tstring_t &csDefaultValue);
            ///< read std::tstring_t
        bool                   bKeyWriteString(const std::tstring_t &csKey, const std::tstring_t &csValue);
            ///< write std::tstring_t

        long_t                 iKeyReadInt    (const std::tstring_t &csKey, const long_t     cliDefaultValue);
            ///< read int
        bool                   bKeyWriteInt   (const std::tstring_t &csKey, const long_t     cliValue);
            ///< write int

        double                 dKeyReadFloat  (const std::tstring_t &csKey, const double   cdDefaultValue);
            ///< read float
        bool                   bKeyWriteFloat (const std::tstring_t &csKey, const double   cdValue);
            ///< write float

        bool                   bKeyReadBool   (const std::tstring_t &csKey, const bool     cbDefaultValue);
            ///< read bool
        bool                   bKeyWriteBool  (const std::tstring_t &csKey, const bool     cbValue);
            ///< write bool

        std::ustring_t         usKeyReadBin   (const std::tstring_t &csKey, const std::ustring_t &cusDefaultValue);
            ///< write std::ustring_t
        bool                   bKeyWriteBin   (const std::tstring_t &csKey, const std::ustring_t &cusValue);
            ///< read std::ustring_t

        bool                   bKeyClear      (const std::tstring_t &csKey);
            ///< clear value
        bool                   bKeyDelete     (const std::tstring_t &csKey);
            ///< delete key and value

    private:
        const std::tstring_t   _m_csSeparator;  ///< separator between key and value
        const std::tstring_t   _m_csFileExt;    ///< ini-file extension

        std::tstring_t         _m_sFilePath;    ///< file path to ini-file
        NxLib::TLocalStorage   _m_msIni;        ///< std::map of keys and values

        bool                   _bRead         (const std::tstring_t &csKey, const std::tstring_t &csDefaultValue, std::tstring_t *psValue);
            ///< parse file
        bool                   _bWrite        (const std::tstring_t &csKey, const std::tstring_t &csValue);
            ///< flush to TLocalStorage, file
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxLocalStorageH
