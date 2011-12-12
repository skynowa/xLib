/**
 * \file  CxIni.h
 * \brief ini
 */


#ifndef xLib_Filesystem_Win_CxIniH
#define xLib_Filesystem_Win_CxIniH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxIni :
    public CxNonCopyable
    /// ini
{
    public:
                       CxIni             ();
        explicit       CxIni             (const std::tstring_t &csFilePath);
        virtual       ~CxIni             ();

        //creation
        bool           bCreateDefault    (const std::tstring_t &csContent);
        std::tstring_t sGetPath          ();
        bool           bSetPath          (const std::tstring_t &csFilePath);
        bool           bFlush            ();
        bool           bClear            ();

        //key
        bool           bKeyIsExists      (const std::tstring_t &csSection, const std::tstring_t &csKey);

        int            iKeyReadInt       (const std::tstring_t &csSection, const std::tstring_t &csKey, long_t   iDefaultValue);
        bool           bKeyWriteInt      (const std::tstring_t &csSection, const std::tstring_t &csKey, long_t   iValue);

        double         dKeyReadFloat     (const std::tstring_t &csSection, const std::tstring_t &csKey, double dDefaultValue);
        bool           bKeyWriteFloat    (const std::tstring_t &csSection, const std::tstring_t &csKey, double dValue);

        bool           bKeyReadBool      (const std::tstring_t &csSection, const std::tstring_t &csKey, bool   bDefaultValue);
        bool           bKeyWriteBool     (const std::tstring_t &csSection, const std::tstring_t &csKey, bool   bValue);

        std::tstring_t sKeyReadString    (const std::tstring_t &csSection, const std::tstring_t &csKey, const std::tstring_t &csDefaultValue);
        bool           bKeyWriteString   (const std::tstring_t &csSection, const std::tstring_t &csKey, const std::tstring_t &csValue);

        std::ustring_t usKeyReadBin      (const std::tstring_t &csSection, const std::tstring_t &csKey, const std::ustring_t &cusDefaultValue);
        bool           bKeyWriteBin      (const std::tstring_t &csSection, const std::tstring_t &csKey, const std::ustring_t &cusValue);

        bool           bKeyClear         (const std::tstring_t &csSection, const std::tstring_t &csKey);
        bool           bKeyDelete        (const std::tstring_t &csSection, const std::tstring_t &csKey);

        //section
        bool           bSectionIsExists  (const std::tstring_t &csSection);
        bool           bSectionRead      (const std::tstring_t &csSection, std::map<std::tstring_t, std::tstring_t> *pmsContent);
        bool           bSectionWrite     (const std::tstring_t &csSection, const std::map<std::tstring_t, std::tstring_t> &msContent);
        bool           bSectionsReadNames(std::vector<std::tstring_t> *pvsNames);
        bool           bSectionClear     (const std::tstring_t &csSection);
        bool           bSectionDelete    (const std::tstring_t &csSection);

        //function ValueExists(const Section, Ident: string): Boolean;

    private:
        std::tstring_t _m_sFilePath;
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_Win_CxIniH
