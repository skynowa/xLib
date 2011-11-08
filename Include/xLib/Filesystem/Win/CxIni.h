/**
 * \file  CxIni.h
 * \brief ini
 */


#ifndef xLib_Filesystem_Win_CxIniH
#define xLib_Filesystem_Win_CxIniH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)
class CxIni :
    public CxNonCopyable
    /// ini
{
    public:
                     CxIni             ();
        explicit     CxIni             (const std::string_t &csFilePath);
        virtual     ~CxIni             ();

        //creation
        BOOL         bCreateDefault    (const std::string_t &csContent);
        std::string_t sGetPath          ();
        BOOL         bSetPath          (const std::string_t &csFilePath);
        BOOL         bFlush            ();
        BOOL         bClear            ();

        //key
        BOOL         bKeyIsExists      (const std::string_t &csSection, const std::string_t &csKey);

        INT          iKeyReadInt       (const std::string_t &csSection, const std::string_t &csKey, LONG   iDefaultValue);
        BOOL         bKeyWriteInt      (const std::string_t &csSection, const std::string_t &csKey, LONG   iValue);

        double       dKeyReadFloat     (const std::string_t &csSection, const std::string_t &csKey, double dDefaultValue);
        BOOL         bKeyWriteFloat    (const std::string_t &csSection, const std::string_t &csKey, double dValue);

        BOOL         bKeyReadBool      (const std::string_t &csSection, const std::string_t &csKey, BOOL   bDefaultValue);
        BOOL         bKeyWriteBool     (const std::string_t &csSection, const std::string_t &csKey, BOOL   bValue);

        std::string_t sKeyReadString    (const std::string_t &csSection, const std::string_t &csKey, const std::string_t &csDefaultValue);
        BOOL         bKeyWriteString   (const std::string_t &csSection, const std::string_t &csKey, const std::string_t &csValue);

        std::ustring usKeyReadBin      (const std::string_t &csSection, const std::string_t &csKey, const std::ustring &cusDefaultValue);
        BOOL         bKeyWriteBin      (const std::string_t &csSection, const std::string_t &csKey, const std::ustring &cusValue);

        BOOL         bKeyClear         (const std::string_t &csSection, const std::string_t &csKey);
        BOOL         bKeyDelete        (const std::string_t &csSection, const std::string_t &csKey);

        //section
        BOOL         bSectionIsExists  (const std::string_t &csSection);
        BOOL         bSectionRead      (const std::string_t &csSection, std::map<std::string_t, std::string_t> *pmsContent);
        BOOL         bSectionWrite     (const std::string_t &csSection, const std::map<std::string_t, std::string_t> &msContent);
        BOOL         bSectionsReadNames(std::vector<std::string_t> *pvsNames);
        BOOL         bSectionClear     (const std::string_t &csSection);
        BOOL         bSectionDelete    (const std::string_t &csSection);

        //function ValueExists(const Section, Ident: string): Boolean;

    private:
        std::string_t _m_sFilePath;
};
#endif
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_Win_CxIniH
