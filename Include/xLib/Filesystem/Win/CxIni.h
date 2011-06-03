/****************************************************************************
* Class name:  CxIni
* Description: ini
* File name:   CxIni.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     23.04.2009 12:10:56
*
*****************************************************************************/


#ifndef xLib_Filesystem_Win_CxIniH
#define xLib_Filesystem_Win_CxIniH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxIni :
    public CxNonCopyable
{
    public:
                         CxIni             ();
        explicit         CxIni             (const tString &csFilePath);
        virtual         ~CxIni             ();

        //creation
        BOOL             bCreateDefault    (const tString &csContent);
        tString          sGetPath          ();
        BOOL             bSetPath          (const tString &csFilePath);
        BOOL             bFlush            ();
        BOOL             bClear            ();

        //key
        BOOL             bKeyIsExists      (const tString &csSection, const tString &csKey);

        INT              iKeyReadInt       (const tString &csSection, const tString &csKey, LONG   iDefaultValue);
        BOOL             bKeyWriteInt      (const tString &csSection, const tString &csKey, LONG   iValue);

        double           dKeyReadFloat     (const tString &csSection, const tString &csKey, double dDefaultValue);
        BOOL             bKeyWriteFloat    (const tString &csSection, const tString &csKey, double dValue);

        BOOL             bKeyReadBool      (const tString &csSection, const tString &csKey, BOOL   bDefaultValue);
        BOOL             bKeyWriteBool     (const tString &csSection, const tString &csKey, BOOL   bValue);

        tString          sKeyReadString    (const tString &csSection, const tString &csKey, const tString &csDefaultValue);
        BOOL             bKeyWriteString   (const tString &csSection, const tString &csKey, const tString &csValue);

        uString          usKeyReadBin      (const tString &csSection, const tString &csKey, const uString &cusDefaultValue);
        BOOL             bKeyWriteBin      (const tString &csSection, const tString &csKey, const uString &cusValue);

        BOOL             bKeyClear         (const tString &csSection, const tString &csKey);
        BOOL             bKeyDelete        (const tString &csSection, const tString &csKey);

        //section
        BOOL             bSectionIsExists  (const tString &csSection);
        BOOL             bSectionRead      (const tString &csSection, std::map<tString, tString> *pmapsContent);
        BOOL             bSectionWrite     (const tString &csSection, const std::map<tString, tString> &mapsContent);
        BOOL             bSectionsReadNames(std::vector<tString> *pvecsNames);
        BOOL             bSectionClear     (const tString &csSection);
        BOOL             bSectionDelete    (const tString &csSection);

        //function ValueExists(const Section, Ident: string): Boolean;

    private:
        BOOL             _m_bRes;
        tString          _m_sFilePath;
};
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_Win_CxIniH
