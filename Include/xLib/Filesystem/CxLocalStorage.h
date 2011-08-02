/****************************************************************************
* Class name:  CxLocalStorage
* Description: ini
* File name:   CxLocalStorage.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     10.05.2011
*
*****************************************************************************/


#ifndef xLib_Filesystem_CxLocalStorageH
#define xLib_Filesystem_CxLocalStorageH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
namespace NxLib {
    typedef std::map<tString, tString> TLocalStorage;
}

class CxLocalStorage :
    public CxNonCopyable
{
    public:
                               CxLocalStorage ();
        explicit               CxLocalStorage (const tString &csFilePath);
        virtual               ~CxLocalStorage ();

        //creation
        BOOL                   bCreateDefault (const tString &csContent) const;
        tString                sGetPath       () const;
        BOOL                   bSetPath       (const tString &csFilePath);
        NxLib::TLocalStorage & cmapsGet       ();

        BOOL                   bFlush         () const;
        BOOL                   bClear         ();
        BOOL                   bDelete        ();

        //key
        BOOL                   bKeyIsExists   (const tString &csKey) const;

        tString                sKeyReadString (const tString &csKey, const tString &csDefaultValue);
        BOOL                   bKeyWriteString(const tString &csKey, const tString &csValue);

        LONG                   iKeyReadInt    (const tString &csKey, const LONG     cliDefaultValue);
        BOOL                   bKeyWriteInt   (const tString &csKey, const LONG     cliValue);

        DOUBLE                 dKeyReadFloat  (const tString &csKey, const DOUBLE   cdDefaultValue);
        BOOL                   bKeyWriteFloat (const tString &csKey, const DOUBLE   cdValue);

        BOOL                   bKeyReadBool   (const tString &csKey, const BOOL     cbDefaultValue);
        BOOL                   bKeyWriteBool  (const tString &csKey, const BOOL     cbValue);

        uString                usKeyReadBin   (const tString &csKey, const uString &cusDefaultValue);
        BOOL                   bKeyWriteBin   (const tString &csKey, const uString &cusValue);

        BOOL                   bKeyClear      (const tString &csKey);
        BOOL                   bKeyDelete     (const tString &csKey);

    private:
        const tString          _m_csSeparator;    //separator between key and value
        const tString          _m_csFileExt;      //ini-file extension

        mutable BOOL           _m_bRes;
        tString                _m_sFilePath;      //file path to ini-file
        NxLib::TLocalStorage   _m_msIni;          //std::map of keys and values

        BOOL                   _bRead         (const tString &csKey, const tString &csDefaultValue, tString *psValue);
        BOOL                   _bWrite        (const tString &csKey, const tString &csValue);
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxLocalStorageH
