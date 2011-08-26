/**
 * \file  CxIni.h
 * \brief ini
 */


#ifndef xLib_Filesystem_Win_CxIniH
#define xLib_Filesystem_Win_CxIniH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if defined(xOS_WIN)
class CxIni :
    public CxNonCopyable
    /// ini
{
    public:
                         CxIni             ();
        explicit         CxIni             (const std::tstring &csFilePath);
        virtual         ~CxIni             ();

        //creation
        BOOL             bCreateDefault    (const std::tstring &csContent);
        std::tstring          sGetPath          ();
        BOOL             bSetPath          (const std::tstring &csFilePath);
        BOOL             bFlush            ();
        BOOL             bClear            ();

        //key
        BOOL             bKeyIsExists      (const std::tstring &csSection, const std::tstring &csKey);

        INT              iKeyReadInt       (const std::tstring &csSection, const std::tstring &csKey, LONG   iDefaultValue);
        BOOL             bKeyWriteInt      (const std::tstring &csSection, const std::tstring &csKey, LONG   iValue);

        double           dKeyReadFloat     (const std::tstring &csSection, const std::tstring &csKey, double dDefaultValue);
        BOOL             bKeyWriteFloat    (const std::tstring &csSection, const std::tstring &csKey, double dValue);

        BOOL             bKeyReadBool      (const std::tstring &csSection, const std::tstring &csKey, BOOL   bDefaultValue);
        BOOL             bKeyWriteBool     (const std::tstring &csSection, const std::tstring &csKey, BOOL   bValue);

        std::tstring          sKeyReadString    (const std::tstring &csSection, const std::tstring &csKey, const std::tstring &csDefaultValue);
        BOOL             bKeyWriteString   (const std::tstring &csSection, const std::tstring &csKey, const std::tstring &csValue);

        std::ustring          usKeyReadBin      (const std::tstring &csSection, const std::tstring &csKey, const std::ustring &cusDefaultValue);
        BOOL             bKeyWriteBin      (const std::tstring &csSection, const std::tstring &csKey, const std::ustring &cusValue);

        BOOL             bKeyClear         (const std::tstring &csSection, const std::tstring &csKey);
        BOOL             bKeyDelete        (const std::tstring &csSection, const std::tstring &csKey);

        //section
        BOOL             bSectionIsExists  (const std::tstring &csSection);
        BOOL             bSectionRead      (const std::tstring &csSection, std::map<std::tstring, std::tstring> *pmsContent);
        BOOL             bSectionWrite     (const std::tstring &csSection, const std::map<std::tstring, std::tstring> &msContent);
        BOOL             bSectionsReadNames(std::vector<std::tstring> *pvsNames);
        BOOL             bSectionClear     (const std::tstring &csSection);
        BOOL             bSectionDelete    (const std::tstring &csSection);

        //function ValueExists(const Section, Ident: string): Boolean;

    private:
        BOOL             _m_bRes;
        std::tstring          _m_sFilePath;
};
#elif defined(xOS_LINUX)

#endif
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_Win_CxIniH
