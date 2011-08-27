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
        explicit               CxLocalStorage (const std::tstring &csFilePath);
        virtual               ~CxLocalStorage ();

        //creation
        BOOL                   bCreateDefault (const std::tstring &csContent) const;
        std::tstring           sGetPath       () const;
        BOOL                   bSetPath       (const std::tstring &csFilePath);
        NxLib::TLocalStorage & cmsGet         ();

        BOOL                   bFlush         () const;
        BOOL                   bClear         ();
        BOOL                   bDelete        ();

        //key
        BOOL                   bKeyIsExists   (const std::tstring &csKey) const;

        std::tstring           sKeyReadString (const std::tstring &csKey, const std::tstring &csDefaultValue);
        BOOL                   bKeyWriteString(const std::tstring &csKey, const std::tstring &csValue);

        LONG                   iKeyReadInt    (const std::tstring &csKey, const LONG     cliDefaultValue);
        BOOL                   bKeyWriteInt   (const std::tstring &csKey, const LONG     cliValue);

        DOUBLE                 dKeyReadFloat  (const std::tstring &csKey, const DOUBLE   cdDefaultValue);
        BOOL                   bKeyWriteFloat (const std::tstring &csKey, const DOUBLE   cdValue);

        BOOL                   bKeyReadBool   (const std::tstring &csKey, const BOOL     cbDefaultValue);
        BOOL                   bKeyWriteBool  (const std::tstring &csKey, const BOOL     cbValue);

        std::ustring           usKeyReadBin   (const std::tstring &csKey, const std::ustring &cusDefaultValue);
        BOOL                   bKeyWriteBin   (const std::tstring &csKey, const std::ustring &cusValue);

        BOOL                   bKeyClear      (const std::tstring &csKey);
        BOOL                   bKeyDelete     (const std::tstring &csKey);

    private:
        const std::tstring     _m_csSeparator;    //separator between key and value
        const std::tstring     _m_csFileExt;      //ini-file extension

        mutable BOOL           _m_bRes;
        std::tstring           _m_sFilePath;      //file path to ini-file
        NxLib::TLocalStorage   _m_msIni;          //std::map of keys and values

        BOOL                   _bRead         (const std::tstring &csKey, const std::tstring &csDefaultValue, std::tstring *psValue);
        BOOL                   _bWrite        (const std::tstring &csKey, const std::tstring &csValue);
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxLocalStorageH
