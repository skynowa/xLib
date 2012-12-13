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
/* static */
bool
CxDir::bIsExists(
    const std::tstring_t &a_csDirPath
)
{
    // n/a

    xCHECK_RET(true == a_csDirPath.empty(), false);

    CxFileAttribute::ExAttribute atAttr = CxFileAttribute::atGet(a_csDirPath);
    xCHECK_RET(CxFileAttribute::faInvalid == atAttr, false);

    bool bRv = CxFileAttribute::bIsExists(a_csDirPath, CxFileAttribute::faDirectory);
    xCHECK_RET(false == bRv, false);

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxDir::bIsEmpty(
    const std::tstring_t &a_csDirPath,
    const std::tstring_t &a_csPattern
)
{
    xTEST_EQ(false, a_csDirPath.empty());
    xTEST_EQ(false, a_csPattern.empty());

    bool bRv = false;

    // TODO: CxPath::sToCurrentOs + CxPath::sSlashAppend

#if   xOS_ENV_WIN
    WIN32_FIND_DATA fdData   = {0};
    std::tstring_t  sDirPath = CxPath::sToCurrentOs( CxPath::sSlashAppend(a_csDirPath) + a_csPattern, false );

    HANDLE hFile = ::FindFirstFile(sDirPath.c_str(), &fdData);
    xCHECK_RET(INVALID_HANDLE_VALUE == hFile, true);

    do {
        std::tstring_t sFileName = fdData.cFileName;

        if (CxConst::xDOT != sFileName && CxConst::x2DOT != sFileName) {
            bRv = false;    // not empty
            break;
        } else {
            bRv = true;    // empty
        }
    }
    while (FALSE != ::FindNextFile(hFile, &fdData));

    BOOL blRes = ::FindClose(hFile);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    DIR *pDir = ::opendir(a_csDirPath.c_str());
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
/* static */
bool
CxDir::bIsRoot(
    const std::tstring_t &a_csDirPath
)
{
    // n/a

#if   xOS_ENV_WIN
    xCHECK_RET(3 != a_csDirPath.size(), false);

    bool bRes1 = CxChar::bIsAlpha(a_csDirPath.at(0));
    bool bRes2 = (a_csDirPath.at(1) == CxConst::xCOLON.at(0));
    bool bRes3 = (a_csDirPath.at(2) == CxConst::xWIN_SLASH.at(0) || a_csDirPath.at(2) == CxConst::xUNIX_SLASH.at(0));

    xCHECK_RET(false == bRes1 || false == bRes2 || false == bRes3, false);
#elif xOS_ENV_UNIX
    xCHECK_RET(CxConst::xSLASH != a_csDirPath, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxDir::bIsDir(
    const std::tstring_t &a_csDirPath
)
{
    xTEST_EQ(false, a_csDirPath.empty());

    bool bRv = CxFileAttribute::bIsExists(a_csDirPath, CxFileAttribute::faDirectory);
    xCHECK_RET(false == bRv, false);

    return true;
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxDir::sCurrent() {
    // n/a

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
    xTEST_EQ(&sBuff.at(0), pszRes);

    sRv.assign(pszRes);
#endif

    return sRv;
}
//--------------------------------------------------------------------------
/* static */
void
CxDir::vSetCurrent(
    const std::tstring_t &a_csDirPath
)
{
    xTEST_EQ(false, a_csDirPath.empty());

    std::tstring_t sDirPath = CxPath::sSlashAppend(a_csDirPath);

#if   xOS_ENV_WIN
    BOOL blRes = ::SetCurrentDirectory(sDirPath.c_str());
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int iRv = ::chdir(sDirPath.c_str());
    xTEST_DIFF(- 1, iRv);
#endif
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxDir::sTemp() {
    // n/a

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

    xTEST_EQ(true, bIsExists(sRv));

    return sRv;
}
//--------------------------------------------------------------------------
/* static */
void
CxDir::vCreate(
    const std::tstring_t &a_csDirPath
)
{
    xTEST_EQ(false, a_csDirPath.empty());

    bool bRv = bIsExists(a_csDirPath);
    xCHECK_DO(true == bRv, return);

#if   xOS_ENV_WIN
    BOOL blRes = ::CreateDirectory(a_csDirPath.c_str(), NULL);
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int iRv = ::mkdir(a_csDirPath.c_str(), 0755);
    xTEST_DIFF(- 1, iRv);
#endif

    xTEST_EQ(true, bIsExists(a_csDirPath));
}
//---------------------------------------------------------------------------
void
CxDir::vCreatePath(
    const std::tstring_t &a_csDirPath
)
{
    xTEST_EQ(false, a_csDirPath.empty());

    std::vec_tstring_t vsPathParts;
    std::tstring_t     sBuildPath;

    //-------------------------------------
    // split csDirPath into parts
     CxString::vSplit( CxPath::sToCurrentOs(a_csDirPath, false), CxConst::xSLASH, &vsPathParts );

    //-------------------------------------
    // create dirs by steps
    xFOREACH_CONST(std::vec_tstring_t, it, vsPathParts) {
        sBuildPath.append(*it).append(CxConst::xSLASH);

        vCreate(sBuildPath);
    }

    xTEST_EQ(true, bIsExists(a_csDirPath));
}
//---------------------------------------------------------------------------
/* static */
void
CxDir::vCopy(
    const std::tstring_t &a_csDirPathFrom,
    const std::tstring_t &a_csDirPathTo,
    const bool           &a_cbFailIfExists
)
{
    xTEST_EQ(false, a_csDirPathFrom.empty());
    xTEST_EQ(true,  bIsExists(a_csDirPathFrom));
    xTEST_EQ(false, a_csDirPathTo.empty());
    // a_cbFailIfExists - n/a

    //-------------------------------------
    // sets attr "normal"
    bool bRv = bIsExists(a_csDirPathTo);
    if (true == bRv) {
        CxFileAttribute::vSet(a_csDirPathTo, CxFileAttribute::faNormal);
    }

    CxFileAttribute::vSet(a_csDirPathFrom, CxFileAttribute::faNormal);

    //--------------------------------------------------
    // get lists of files
    std::vec_tstring_t vsFilePathes;

    vsFilePathes.clear();
    vFindFiles(a_csDirPathFrom, CxConst::xMASK_ALL, true, &vsFilePathes);

    //--------------------------------------------------
    // copy
    xFOREACH_R_CONST(std::vec_tstring_t, it, vsFilePathes) {
        std::tstring_t sFilePathTo = *it;

        size_t uiPosBegin = sFilePathTo.find(a_csDirPathFrom);
        xTEST_DIFF(std::tstring_t::npos, uiPosBegin);

        sFilePathTo.replace(uiPosBegin, uiPosBegin + a_csDirPathFrom.size(), a_csDirPathTo);

        vCreatePath(CxPath::sDir(sFilePathTo));

        CxFile::vCopy(*it, sFilePathTo, a_cbFailIfExists);
    }

    //--------------------------------------------------
    // TODO: rollback
}
//---------------------------------------------------------------------------
/* static */
void
CxDir::vMove(
    const std::tstring_t &a_csDirPathFrom,
    const std::tstring_t &a_csDirPathTo,
    const bool           &a_cbFailIfExists
)
{
    xTEST_EQ(false, a_csDirPathFrom.empty());
    xTEST_EQ(true,  bIsExists(a_csDirPathFrom));
    xTEST_EQ(false, a_csDirPathTo.empty());
    // a_cbFailIfExists - n/a

    vCopy(a_csDirPathFrom, a_csDirPathTo, a_cbFailIfExists);
    vDeleteForce(a_csDirPathFrom);
}
//---------------------------------------------------------------------------
/* static */
void
CxDir::vDelete(
    const std::tstring_t &a_csDirPath
)
{
    xTEST_EQ(false, a_csDirPath.empty());

    bool bRv = bIsExists(a_csDirPath);
    xCHECK_DO(false == bRv, return);

    CxFileAttribute::vSet(a_csDirPath, CxFileAttribute::faNormal);

#if   xOS_ENV_WIN
    BOOL blRes = ::RemoveDirectory(a_csDirPath.c_str());
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int iRv = ::rmdir(a_csDirPath.c_str());
    xTEST_DIFF(- 1, iRv);
#endif

    xTEST_EQ(false, bIsExists(a_csDirPath));
}
//---------------------------------------------------------------------------
/* static */
void
CxDir::vTryDelete(
    const std::tstring_t &a_csDirPath,
    const size_t         &a_cuiAttempts,
    const ulong_t        &a_culTimeoutMsec
)
{
    xTEST_EQ(false, a_csDirPath.empty());
    xTEST_LESS(size_t(0U), a_cuiAttempts);

    const size_t cuiMaxAttempts  = 100;  // MAGIC_NUMBER: cuiMaxAttempts
    const size_t cuiRealAttempts = (cuiMaxAttempts < a_cuiAttempts) ? cuiMaxAttempts : a_cuiAttempts;

    for (size_t i = 0; i < cuiRealAttempts; ++ i) {
        try {
            vDelete(a_csDirPath);
            break;
        }
        catch (const CxException &) {
            xNA;
        }

        CxCurrentThread::vSleep(a_culTimeoutMsec);
    }
}
//---------------------------------------------------------------------------
/* static */
void
CxDir::vClearForce(
    const std::tstring_t &a_csDirPath
)
{
    xTEST_EQ(false, a_csDirPath.empty());
    xTEST_EQ(true, bIsExists(a_csDirPath));

    //-------------------------------------
    // checks
    bool bRv = bIsEmpty(a_csDirPath, CxConst::xMASK_ALL);
    xCHECK_DO(true == bRv, return);

    //-------------------------------------
    // delete files
    {
        std::vec_tstring_t vsFilePathes;

        vsFilePathes.clear();
        vFindFiles(a_csDirPath, CxConst::xMASK_ALL, true, &vsFilePathes);

        xFOREACH_R(std::vec_tstring_t, it, vsFilePathes) {
            CxFile::vDelete(*it);
        }
    }

    //-------------------------------------
    // delete subdirs
    {
        std::vec_tstring_t vsDirPathes;

        vsDirPathes.clear();
        vFindDirs(a_csDirPath, CxConst::xMASK_ALL, true, &vsDirPathes);

        xFOREACH_R(std::vec_tstring_t, it, vsDirPathes) {
            vDelete(*it);
        }
    }

    xTEST_EQ(true, bIsEmpty(a_csDirPath));
}
//---------------------------------------------------------------------------
/* static */
void
CxDir::vDeleteForce(
    const std::tstring_t &a_csDirPath
)
{
    xTEST_EQ(false, a_csDirPath.empty());

    bool bRv = bIsExists(a_csDirPath);
    xCHECK_DO(false == bRv, return);

    vClearForce(a_csDirPath);
    vDelete(a_csDirPath);

    xTEST_EQ(false, bIsExists(a_csDirPath));
}
//--------------------------------------------------------------------------
// TODO: vFindFiles
// http://www.metalshell.com/source_code/86/List_Contents_of_a_Directory.html
/* static */
void
CxDir::vFindFiles(
    const std::tstring_t &a_csDirPath,          ///< directory path
    const std::tstring_t &a_csPattern,          ///< pattern
    const bool           &a_cbIsRecursively,    ///< recursively scan
    std::vec_tstring_t   *a_pvsFilePathes       ///< output file pathes (must be empty)
)
{
    xTEST_EQ(false, a_csDirPath.empty());
    xTEST_EQ(false, a_csPattern.empty());
    // a_cbIsRecursively - n/a
    xTEST_PTR(a_pvsFilePathes);

    // TODO: CxDir::vFindFiles
    #if xTODO
        (*pvsFilePathes).clear();
    #endif

#if   xOS_ENV_WIN
    std::tstring_t  sFilePath     = CxPath::sToCurrentOs( CxPath::sSlashAppend(a_csDirPath) + a_csPattern, false );
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

                vFindFiles(sTmpPath, sFileFullName, true, a_pvsFilePathes);
            }
            while (FALSE != ::FindNextFile(hFile, &fdData));

            BOOL blRes = ::FindClose(hFile);
            xTEST_DIFF(FALSE, blRes);
        }
    }

    //-------------------------------------
    // FIX: files (realy need)
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
        DIR *pDir = ::opendir(a_csDirPath.c_str());
        xTEST_PTR(pDir);

        dirent *pdrEntry = ::readdir(pDir);
        xTEST_PTR(pdrEntry);

        do {
            // dirs
            if (DT_DIR == pdrEntry->d_type) {
                // skipping "." ".."
                xCHECK_DO(CxConst::xDOT  == std::tstring_t(pdrEntry->d_name), continue);
                xCHECK_DO(CxConst::x2DOT == std::tstring_t(pdrEntry->d_name), continue);

                std::tstring_t sDirPath = CxPath::sSlashAppend(a_csDirPath) + std::tstring_t(pdrEntry->d_name);

                // is search in subdirs ?
                if (true == a_cbIsRecursively) {
                    vFindFiles(sDirPath, a_csPattern, a_cbIsRecursively, a_pvsFilePathes); // recursion
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

                std::tstring_t sFilePath = CxPath::sSlashAppend(a_csDirPath) + sFileName;

                (*a_pvsFilePathes).push_back(sFilePath);
            }
        }
        while ( NULL != (pdrEntry = ::readdir(pDir)) );

        int iRv = ::closedir(pDir); pDir = NULL;
        xTEST_DIFF(- 1, iRv);
    }

    //-------------------------------------
    // FIX: files (!!!! krivo napisano !!!!)
    #if xTODO
        if (true != cbIsRecurse) {
            DIR    *pDir     = NULL;
            dirent *pdrEntry = {0};

            pDir = opendir(csDirPath.c_str());
            xTEST_PTR(pDir, false);

            pdrEntry = readdir(pDir);
            xCHECK_RET(NULL == pdrEntry, false);

            do {
                // skip dirs
                xCHECK_DO(DT_DIR == pdrEntry->d_type, continue);

                std::tstring_t sFilePath = CxPath::sSlashAppend(csDirPath) + pdrEntry->d_name;

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
/* static */
void
CxDir::vFindDirs(
    const std::tstring_t &a_csDirPath,          ///< directory path
    const std::tstring_t &a_csPattern,          ///< pattern
    const bool           &a_cbIsRecursively,    ///< recursively scan
    std::vec_tstring_t   *a_pvsDirPathes        ///< output directory pathes (must be empty)
)
{
    xTEST_EQ(false, a_csDirPath.empty());
    // a_cbIsRecursively - n/a
    xTEST_PTR(a_pvsDirPathes);

    // TODO: CxDir::vFindDirs
    #if xTODO
        (*a_pvsDirPathes).clear();
    #endif

#if   xOS_ENV_WIN
    std::tstring_t  sRootDirPath = CxPath::sToCurrentOs( CxPath::sSlashAppend(a_csDirPath) + a_csPattern, false );
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

            std::tstring_t sDirPath = CxPath::sSlashAppend(a_csDirPath) + sFileName;

            (*a_pvsDirPathes).push_back(sDirPath);

            // is search in subdirs ?
            if (true == a_cbIsRecursively) {
                vFindDirs(sDirPath, a_csPattern, a_cbIsRecursively, a_pvsDirPathes);  // recursion
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
    DIR *pDir = ::opendir(a_csDirPath.c_str());
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

            std::tstring_t sDirPath = CxPath::sSlashAppend(a_csDirPath) + sFileName;

            (*a_pvsDirPathes).push_back(sDirPath);

            // is search in subdirs ?
            if (true == a_cbIsRecursively) {
                vFindDirs(sDirPath, a_csPattern, a_cbIsRecursively, a_pvsDirPathes);  // recursion
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
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxDir::CxDir() {

}
//---------------------------------------------------------------------------
/* virtual */
CxDir::~CxDir() {

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
