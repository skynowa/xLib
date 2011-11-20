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
        explicit     CxIni             (const std::tstring &csFilePath);
        virtual     ~CxIni             ();

        //creation
        bool         bCreateDefault    (const std::tstring &csContent);
        std::tstring sGetPath          ();
        bool         bSetPath          (const std::tstring &csFilePath);
        bool         bFlush            ();
        bool         bClear            ();

        //key
        bool         bKeyIsExists      (const std::tstring &csSection, const std::tstring &csKey);

        int          iKeyReadInt       (const std::tstring &csSection, const std::tstring &csKey, LONG   iDefaultValue);
        bool         bKeyWriteInt      (const std::tstring &csSection, const std::tstring &csKey, LONG   iValue);

        double       dKeyReadFloat     (const std::tstring &csSection, const std::tstring &csKey, double dDefaultValue);
        bool         bKeyWriteFloat    (const std::tstring &csSection, const std::tstring &csKey, double dValue);

        bool         bKeyReadBool      (const std::tstring &csSection, const std::tstring &csKey, bool   bDefaultValue);
        bool         bKeyWriteBool     (const std::tstring &csSection, const std::tstring &csKey, bool   bValue);

        std::tstring sKeyReadString    (const std::tstring &csSection, const std::tstring &csKey, const std::tstring &csDefaultValue);
        bool         bKeyWriteString   (const std::tstring &csSection, const std::tstring &csKey, const std::tstring &csValue);

        std::ustring usKeyReadBin      (const std::tstring &csSection, const std::tstring &csKey, const std::ustring &cusDefaultValue);
        bool         bKeyWriteBin      (const std::tstring &csSection, const std::tstring &csKey, const std::ustring &cusValue);

        bool         bKeyClear         (const std::tstring &csSection, const std::tstring &csKey);
        bool         bKeyDelete        (const std::tstring &csSection, const std::tstring &csKey);

        //section
        bool         bSectionIsExists  (const std::tstring &csSection);
        bool         bSectionRead      (const std::tstring &csSection, std::map<std::tstring, std::tstring> *pmsContent);
        bool         bSectionWrite     (const std::tstring &csSection, const std::map<std::tstring, std::tstring> &msContent);
        bool         bSectionsReadNames(std::vector<std::tstring> *pvsNames);
        bool         bSectionClear     (const std::tstring &csSection);
        bool         bSectionDelete    (const std::tstring &csSection);

        //function ValueExists(const Section, Ident: string): Boolean;

    private:
        std::tstring _m_sFilePath;
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_Win_CxIniH
