/**
 * \file  CxDir.cpp
 * \brief directory
 */


#include <xLib/Filesystem/CxDir.h>

#include <xLib/Common/CxChar.h>
#include <xLib/Common/CxString.h>
#include <xLib/Debug/CxException.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxFile.h>
#include <xLib/Filesystem/CxFileAttribute.h>
#include <xLib/Filesystem/CxEnvironment.h>
#include <xLib/Sync/CxCurrentThread.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxDir::CxDir(
    const std::tstring_t &a_csDirPath
) :
    _m_csDirPath(a_csDirPath)
{
    xTEST_EQ(false, a_csDirPath.empty());
}
//---------------------------------------------------------------------------
/* virtual */
CxDir::~CxDir() {

}
//---------------------------------------------------------------------------
const std::tstring_t &
CxDir::sDirPath() const {
    xTEST_EQ(false, _m_csDirPath.empty());

    return _m_csDirPath;
}
//---------------------------------------------------------------------------
bool
CxDir::bIsExists() {
    xCHECK_RET(true == sDirPath().empty(), false);

    CxFileAttribute faAttr(sDirPath());

    xCHECK_RET(CxFileAttribute::faInvalid == faAttr.atGet(), false);

    bool bRv = faAttr.bIsExists(CxFileAttribute::faDirectory);
    xCHECK_RET(false == bRv, false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxDir::bIsEmpty(
    const std::tstring_t &a_csPattern
)
{
    xTEST_EQ(false, a_csPattern.empty());

    bool bRv = false;

    // TODO: CxPath::sToNative + CxPath::sSlashAppend

#if   xOS_ENV_WIN
    WIN32_FIND_DATA fdData    = {0};
    std::tstring_t  _sDirPath = CxPath::sToNative( CxPath::sSlashAppend(sDirPath()) + a_csPattern, false );

    HANDLE hFile = ::FindFirstFile(_sDirPath.c_str(), &fdData);
    xCHECK_RET(INVALID_HANDLE_VALUE == hFile, true);

    do {
        std::tstring_t sFileName = fdData.cFileName;

        if (CxConst::xDOT != sFileName && CxConst::x2DOT != sFileName) {
            bRv = false;    // not empty
            break;
        } else {
            bRv = true;     // empty
        }
    }
    while (FALSE != ::FindNextFile(hFile, &fdData));

    BOOL blRes = ::FindClose(hFile);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    DIR *pDir = ::opendir(sDirPath().c_str());
    xTEST_PTR(pDir);

    dirent *pdrEntry = ::readdir(pDir);
    xCHECK_RET(NULL == pdrEntry, true);

    do {
        std::tstring_t sFileName = pdrEntry->d_name;

        if (CxConst::xDOT != sFileName && CxConst::x2DOT != sFileName) {
            bRv = false;   // not empty
            break;
        } else {
            bRv = true;    // empty
        }
    }
    while (NULL != (pdrEntry = ::readdir(pDir)));

    int iRv = ::closedir(pDir); pDir = NULL;
    xTEST_DIFF(- 1, iRv);
#endif

    return bRv;
}
//---------------------------------------------------------------------------
bool
CxDir::bIsRoot() {
#if   xOS_ENV_WIN
    xCHECK_RET(3 != sDirPath().size(), false);

    bool bRes1 = CxChar::bIsAlpha(sDirPath().at(0));
    bool bRes2 = (sDirPath().at(1) == CxConst::xCOLON.at(0));
    bool bRes3 = (sDirPath().at(2) == CxConst::xWIN_SLASH.at(0) || sDirPath().at(2) == CxConst::xUNIX_SLASH.at(0));

    xCHECK_RET(false == bRes1 || false == bRes2 || false == bRes3, false);
#elif xOS_ENV_UNIX
    xCHECK_RET(CxConst::xSLASH != sDirPath(), false);
#endif

    return true;
}
//---------------------------------------------------------------------------
bool
CxDir::bIsDir() {
    bool bRv = CxFileAttribute(sDirPath()).bIsExists(CxFileAttribute::faDirectory);
    xCHECK_RET(false == bRv, false);

    return true;
}
//--------------------------------------------------------------------------
void
CxDir::vCreate() {
    bool bRv = bIsExists();
    xCHECK_DO(true == bRv, return);

#if   xOS_ENV_WIN
    BOOL blRes = ::CreateDirectory(sDirPath().c_str(), NULL);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int iRv = ::mkdir(sDirPath().c_str(), 0755);
    xTEST_DIFF(- 1, iRv);
#endif

    xTEST_EQ(true, bIsExists());
}
//---------------------------------------------------------------------------
void
CxDir::vCreatePath() {
    std::vec_tstring_t vsPathParts;
    std::tstring_t     sBuildPath;

    //-------------------------------------
    // split csDirPath into parts
     CxString::vSplit( CxPath::sToNative(sDirPath(), false), CxConst::xSLASH, &vsPathParts );

    //-------------------------------------
    // create dirs by steps
    xFOREACH_CONST(std::vec_tstring_t, it, vsPathParts) {
        sBuildPath.append(*it).append(CxConst::xSLASH);

        CxDir(sBuildPath).vCreate();
    }

    xTEST_EQ(true, bIsExists());
}
//---------------------------------------------------------------------------
void
CxDir::vCopy(
    const std::tstring_t &a_csDirPathTo,
    const bool           &a_cbFailIfExists
)
{
    xTEST_EQ(true,  bIsExists());
    xTEST_EQ(false, a_csDirPathTo.empty());
    xTEST_NA(a_cbFailIfExists);

    //-------------------------------------
    // sets attribute "normal"
    bool bRv = CxDir(a_csDirPathTo).bIsExists();
    if (true == bRv) {
        CxFileAttribute(a_csDirPathTo).vSet(CxFileAttribute::faNormal);
    }

    CxFileAttribute(sDirPath()).vSet(CxFileAttribute::faNormal);

    //--------------------------------------------------
    // get lists of files
    std::vec_tstring_t vsFilePathes;

    vsFilePathes.clear();
    CxDir(sDirPath()).vFindFiles(CxConst::xMASK_ALL, true, &vsFilePathes);

    //--------------------------------------------------
    // copy
    xFOREACH_R_CONST(std::vec_tstring_t, it, vsFilePathes) {
        std::tstring_t sFilePathTo = *it;

        size_t uiPosBegin = sFilePathTo.find(sDirPath());
        xTEST_DIFF(std::tstring_t::npos, uiPosBegin);

        sFilePathTo.replace(uiPosBegin, uiPosBegin + sDirPath().size(), a_csDirPathTo);

        CxDir( CxPath::sDir(sFilePathTo) ).vCreatePath();

        CxFile::vCopy(*it, sFilePathTo, a_cbFailIfExists);
    }

    //--------------------------------------------------
    // TODO: rollback
}
//---------------------------------------------------------------------------
void
CxDir::vMove(
    const std::tstring_t &a_csDirPathTo,
    const bool           &a_cbFailIfExists
)
{
    xTEST_EQ(true,  bIsExists());
    xTEST_EQ(false, a_csDirPathTo.empty());
    xTEST_NA(a_cbFailIfExists);

    CxDir drDir(sDirPath());

    drDir.vCopy(a_csDirPathTo, a_cbFailIfExists);
    drDir.vDeleteForce();
}
//---------------------------------------------------------------------------
void
CxDir::vDelete() {
    bool bRv = bIsExists();
    xCHECK_DO(false == bRv, return);

    CxFileAttribute(sDirPath()).vSet(CxFileAttribute::faNormal);

#if   xOS_ENV_WIN
    BOOL blRes = ::RemoveDirectory(sDirPath().c_str());
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int iRv = ::rmdir(sDirPath().c_str());
    xTEST_DIFF(- 1, iRv);
#endif

    xTEST_EQ(false, bIsExists());
}
//---------------------------------------------------------------------------
void
CxDir::vTryDelete(
    const size_t  &a_cuiAttempts,
    const ulong_t &a_culTimeoutMsec
)
{
    xTEST_LESS(size_t(0U), a_cuiAttempts);

    const size_t cuiMaxAttempts  = 100;  // MAGIC_NUMBER: cuiMaxAttempts
    const size_t cuiRealAttempts = (cuiMaxAttempts < a_cuiAttempts) ? cuiMaxAttempts : a_cuiAttempts;

    for (size_t i = 0; i < cuiRealAttempts; ++ i) {
        try {
            vDelete();
            break;
        }
        catch (const CxException &) {
            xNA;
        }

        CxCurrentThread::vSleep(a_culTimeoutMsec);
    }
}
//---------------------------------------------------------------------------
void
CxDir::vClearForce() {
    xTEST_EQ(true, bIsExists());

    //-------------------------------------
    // checks
    bool bRv = bIsEmpty(CxConst::xMASK_ALL);
    xCHECK_DO(true == bRv, return);

    //-------------------------------------
    // delete files
    {
        std::vec_tstring_t vsFilePathes;

        vsFilePathes.clear();
        vFindFiles(CxConst::xMASK_ALL, true, &vsFilePathes);

        xFOREACH_R(std::vec_tstring_t, it, vsFilePathes) {
            CxFile::vDelete(*it);
        }
    }

    //-------------------------------------
    // delete subdirs
    {
        std::vec_tstring_t vsDirPathes;

        vsDirPathes.clear();
        vFindDirs(CxConst::xMASK_ALL, true, &vsDirPathes);

        xFOREACH_R(std::vec_tstring_t, it, vsDirPathes) {
            CxDir(*it).vDelete();
        }
    }

    xTEST_EQ(true, bIsEmpty());
}
//---------------------------------------------------------------------------
void
CxDir::vDeleteForce() {
    bool bRv = bIsExists();
    xCHECK_DO(false == bRv, return);

    vClearForce();
    vDelete();

    xTEST_EQ(false, bIsExists());
}
//--------------------------------------------------------------------------
// TODO: vFindFiles
// http://www.metalshell.com/source_code/86/List_Contents_of_a_Directory.html
void
CxDir::vFindFiles(
    const std::tstring_t &a_csPattern,          ///< pattern
    const bool           &a_cbIsRecursively,    ///< recursively scan
    std::vec_tstring_t   *a_pvsFilePathes       ///< output file paths (must be empty)
)
{
    xTEST_EQ(false, a_csPattern.empty());
    xTEST_NA(a_cbIsRecursively);
    xTEST_PTR(a_pvsFilePathes);

    // TODO: CxDir::vFindFiles
    #if xTODO
        (*pvsFilePathes).clear();
    #endif

#if   xOS_ENV_WIN
    std::tstring_t  sFilePath     = CxPath::sToNative( CxPath::sSlashAppend(sDirPath()) + a_csPattern, false );
    std::tstring_t  sFileFullName = CxPath::sFileName(sFilePath);
    std::tstring_t  sPart;
    std::tstring_t  sTmpPath;
    WIN32_FIND_DATA fdData        = {0};

    //-------------------------------------
    // subdirs
    if (true == a_cbIsRecursively) {
        sPart    = CxConst::xMASK_ALL;
        sTmpPath = CxPath::sSetFileName(sFilePath, sPart);

        // make search, if dir exists
        fdData.dwFileAttributes = CxFileAttribute::faDirectory;

        HANDLE hFile = ::FindFirstFile(sTmpPath.c_str(), &fdData);
        if (INVALID_HANDLE_VALUE != hFile) {
            do {
                // skip files, dirs "." and ".."
                xCHECK_DO(!(fdData.dwFileAttributes & CxFileAttribute::faDirectory), continue);
                xCHECK_DO(CxConst::xDOT  == std::tstring_t(fdData.cFileName),        continue);
                xCHECK_DO(CxConst::x2DOT == std::tstring_t(fdData.cFileName),        continue);

                sPart    = fdData.cFileName;
                sTmpPath = CxPath::sSetFileName(sTmpPath, sPart);

                CxDir(sTmpPath).vFindFiles(sFileFullName, true, a_pvsFilePathes);
            }
            while (FALSE != ::FindNextFile(hFile, &fdData));

            BOOL blRes = ::FindClose(hFile);
            xTEST_DIFF(FALSE, blRes);
        }
    }

    //-------------------------------------
    // FIX: files (really need)
    HANDLE hFile = ::FindFirstFile(sFilePath.c_str(), &fdData);
    xCHECK_DO(INVALID_HANDLE_VALUE == hFile, return);

    do {
        // skip dirs
        xCHECK_DO(fdData.dwFileAttributes & CxFileAttribute::faDirectory, continue);

        sPart    = fdData.cFileName;
        sTmpPath = CxPath::sSetFileName(sFilePath /*sTmpPath*/, sPart);

        (*a_pvsFilePathes).push_back(sTmpPath);
    }
    while ( FALSE != ::FindNextFile(hFile, &fdData) );

    BOOL blRes = ::FindClose(hFile);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    //-------------------------------------
    // subdirs
    /*if (true == cbIsRecursively)*/ {
        DIR *pDir = ::opendir(sDirPath().c_str());
        xTEST_PTR(pDir);

        dirent *pdrEntry = ::readdir(pDir);
        xTEST_PTR(pdrEntry);

        do {
            // dirs
            if (DT_DIR == pdrEntry->d_type) {
                // skipping "." ".."
                xCHECK_DO(CxConst::xDOT  == std::tstring_t(pdrEntry->d_name), continue);
                xCHECK_DO(CxConst::x2DOT == std::tstring_t(pdrEntry->d_name), continue);

                std::tstring_t _sDirPath = CxPath::sSlashAppend(sDirPath()) + std::tstring_t(pdrEntry->d_name);

                // is search in subdirs ?
                if (true == a_cbIsRecursively) {
                    CxDir(_sDirPath).vFindFiles(a_csPattern, a_cbIsRecursively, a_pvsFilePathes); // recursion
                }
            }
            // TODO: files
            else if (DT_REG == pdrEntry->d_type) {
                std::tstring_t sFileName = pdrEntry->d_name;

                // filter by pattern
                {
                    int iRv = ::fnmatch(a_csPattern.c_str(), sFileName.c_str(), 0);
                    xTEST_EQ(true, (0 == iRv) || (FNM_NOMATCH == iRv));

                    xCHECK_DO(0 != iRv, continue);
                }

                std::tstring_t sFilePath = CxPath::sSlashAppend(sDirPath()) + sFileName;

                (*a_pvsFilePathes).push_back(sFilePath);
            }
        }
        while ( NULL != (pdrEntry = ::readdir(pDir)) );

        int iRv = ::closedir(pDir); pDir = NULL;
        xTEST_DIFF(- 1, iRv);
    }

    //-------------------------------------
    // FIX: files (!!!! bad code !!!!)
    #if xTODO
        if (true != cbIsRecurse) {
            DIR    *pDir     = NULL;
            dirent *pdrEntry = {0};

            pDir = opendir(sDirPath().c_str());
            xTEST_PTR(pDir, false);

            pdrEntry = readdir(pDir);
            xCHECK_RET(NULL == pdrEntry, false);

            do {
                // skip dirs
                xCHECK_DO(DT_DIR == pdrEntry->d_type, continue);

                std::tstring_t sFilePath = CxPath::sSlashAppend(sDirPath()) + pdrEntry->d_name;

                (*pvsFilePathes).push_back(sFilePath);
            }
            while ( NULL != (pdrEntry = readdir(pDir)) );

            int iRv = closedir(pDir); pDir = NULL;
            xTEST_DIFF(- 1, iRv);
        }
    #endif
#endif
}
//--------------------------------------------------------------------------
void
CxDir::vFindDirs(
    const std::tstring_t &a_csPattern,          ///< pattern
    const bool           &a_cbIsRecursively,    ///< recursively scan
    std::vec_tstring_t   *a_pvsDirPathes        ///< output directory paths (must be empty)
)
{
    xTEST_NA(a_cbIsRecursively);
    xTEST_PTR(a_pvsDirPathes);

    // TODO: CxDir::vFindDirs
    #if xTODO
        (*a_pvsDirPathes).clear();
    #endif

#if   xOS_ENV_WIN
    std::tstring_t  sRootDirPath = CxPath::sToNative( CxPath::sSlashAppend(sDirPath()) + a_csPattern, false );
    WIN32_FIND_DATA fdData       = {0};

    HANDLE hFile = ::FindFirstFile(sRootDirPath.c_str(), &fdData);
    xTEST_DIFF(xNATIVE_HANDLE_INVALID, hFile);

    do {
        // dirs
        if (CxFileAttribute::faDirectory == (fdData.dwFileAttributes & CxFileAttribute::faDirectory)) {
            std::tstring_t sFileName = fdData.cFileName;

            // skip "." ".."
            xCHECK_DO(CxConst::xDOT  == sFileName, continue);
            xCHECK_DO(CxConst::x2DOT == sFileName, continue);

            std::tstring_t _sDirPath = CxPath::sSlashAppend(sDirPath()) + sFileName;

            (*a_pvsDirPathes).push_back(_sDirPath);

            // is search in subdirs ?
            if (true == a_cbIsRecursively) {
                CxDir(_sDirPath).vFindDirs(a_csPattern, a_cbIsRecursively, a_pvsDirPathes);  // recursion
            }
        }
        // files, etc
        else {
            xNA;
        }
    }
    while ( FALSE != ::FindNextFile(hFile, &fdData) );

    BOOL blRes = ::FindClose(hFile);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    DIR *pDir = ::opendir(sDirPath().c_str());
    xTEST_PTR(pDir);

    dirent *pdrEntry = ::readdir(pDir);
    xTEST_PTR(pdrEntry);

    do {
        // dirs
        if (DT_DIR == pdrEntry->d_type) {
            std::tstring_t sFileName = pdrEntry->d_name;

            // skip "." ".."
            xCHECK_DO(CxConst::xDOT  == sFileName, continue);
            xCHECK_DO(CxConst::x2DOT == sFileName, continue);

            // filter by pattern
            {
                int iRv = ::fnmatch(a_csPattern.c_str(), sFileName.c_str(), 0);
                xTEST_EQ(true, (0 == iRv) || (FNM_NOMATCH == iRv));

                xCHECK_DO(0 != iRv, continue);
            }

            std::tstring_t _sDirPath = CxPath::sSlashAppend(sDirPath()) + sFileName;

            (*a_pvsDirPathes).push_back(_sDirPath);

            // is search in subdirs ?
            if (true == a_cbIsRecursively) {
                CxDir(_sDirPath).vFindDirs(a_csPattern, a_cbIsRecursively, a_pvsDirPathes);  // recursion
            }
        }
        // files, etc
        else {
            xNA;
        }
    }
    while ( NULL != (pdrEntry = ::readdir(pDir)) );

    int iRv = ::closedir(pDir); pDir = NULL;
    xTEST_DIFF(- 1, iRv);
#endif
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public
*
*****************************************************************************/

//--------------------------------------------------------------------------
std::tstring_t
CxDir::sCurrent() {
    std::tstring_t sRv;
    std::tstring_t sBuff(xPATH_MAX + 1, 0);

#if   xOS_ENV_WIN
    DWORD ulRv = ::GetCurrentDirectory(static_cast<DWORD>( xPATH_MAX ), &sBuff[0]);
    xTEST_DIFF(0UL, ulRv);
    xTEST_LESS(ulRv, static_cast<ulong_t>( xPATH_MAX ));

    sRv.assign(sBuff, 0, ulRv);
#elif xOS_ENV_UNIX
    tchar_t *pszRes = ::getcwd(&sBuff[0], xPATH_MAX);
    xTEST_PTR(pszRes);
    xTEST_EQ(sBuff.c_str(), const_cast<const tchar_t *>( pszRes ));

    sRv.assign(pszRes);
#endif

    return sRv;
}
//--------------------------------------------------------------------------
void
CxDir::vSetCurrent(
    const std::tstring_t &a_csDirPath
) {
    std::tstring_t sDirPath = CxPath::sSlashAppend(a_csDirPath);

#if   xOS_ENV_WIN
    BOOL blRes = ::SetCurrentDirectory(sDirPath.c_str());
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int iRv = ::chdir(a_csDirPath.c_str());
    xTEST_DIFF(- 1, iRv);
#endif
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxDir::sTemp() {
    std::tstring_t sRv;

#if   xOS_ENV_WIN
    std::tstring_t sBuff(xPATH_MAX + 1, 0);

    DWORD ulRv = ::GetTempPath(static_cast<DWORD>( xPATH_MAX ), &sBuff[0]);
    xTEST_DIFF(0UL, ulRv);
    xTEST_LESS(ulRv, static_cast<ulong_t>( xPATH_MAX ));

    sRv.assign(sBuff, 0, ulRv);
#elif xOS_ENV_UNIX
    const std::tstring_t csEnvDirTemp = xT("TMPDIR");

    bool bRv = CxEnvironment::bIsExists(csEnvDirTemp);
    if (true == bRv) {
        sRv = CxEnvironment::sVar(csEnvDirTemp);
    } else {
        sRv = xDIR_TEMP;
    }
#endif

    xTEST_EQ(true, CxDir(sRv).bIsExists());

    return sRv;
}
//--------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
