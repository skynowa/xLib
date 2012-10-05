/**
 * \file  CxDir.cpp
 * \brief directory
 */


#include <xLib/Filesystem/CxDir.h>

#include <xLib/Common/CxChar.h>
#include <xLib/Common/CxString.h>
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
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/// n/a

    xCHECK_RET(true == csDirPath.empty(), false);

    CxFileAttribute::ExAttribute atAttr = CxFileAttribute::atGet(csDirPath);
    xCHECK_RET(CxFileAttribute::faInvalid == atAttr, false);

    bool bRv = CxFileAttribute::bIsExists(csDirPath, CxFileAttribute::faDirectory);
    xCHECK_RET(false == bRv, false);

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxDir::bIsEmpty(
    const std::tstring_t &csDirPath,
    const std::tstring_t &csMask
)
{
    /*DEBUG*/xTEST_EQ(false, csDirPath.empty());
    /*DEBUG*/xTEST_EQ(false, csMask.empty());

    bool bRv = false;

    //TODO: CxPath::sToCurrentOs + CxPath::sSlashAppend

#if   xOS_ENV_WIN
    HANDLE          hFile    = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA fdData   = {0};
    std::tstring_t  sDirPath = CxPath::sToCurrentOs( CxPath::sSlashAppend(csDirPath) + csMask, false );

    hFile = ::FindFirstFile(sDirPath.c_str(), &fdData);
    xCHECK_RET(INVALID_HANDLE_VALUE == hFile, true);

    do {
        std::tstring_t sFileName = fdData.cFileName;

        if (CxConst::xDOT != sFileName && CxConst::x2DOT != sFileName) {
            bRv = false;   // not empty
            break;
        } else {
            bRv = true;    // empty
        }
    }
    while (false != ::FindNextFile(hFile, &fdData));

    BOOL blRes = ::FindClose(hFile);
    /*DEBUG*/xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    DIR    *pDir     = NULL;
    dirent *pdrEntry = {0};

    pDir = ::opendir(csDirPath.c_str());
    /*DEBUG*/xTEST_PTR(pDir);

    pdrEntry = ::readdir(pDir);
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
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
#endif

    return bRv;
}
//---------------------------------------------------------------------------
/* static */
bool
CxDir::bIsRoot(
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/// n/a

#if   xOS_ENV_WIN
    xCHECK_RET(3 != csDirPath.size(), false);

    bool bRes1 = CxChar::bIsAlpha(csDirPath.at(0));
    bool bRes2 = (csDirPath.at(1) == CxConst::xCOLON.at(0));
    bool bRes3 = (csDirPath.at(2) == CxConst::xWIN_SLASH.at(0) || csDirPath.at(2) == CxConst::xUNIX_SLASH.at(0));

    xCHECK_RET(false == bRes1 || false == bRes2 || false == bRes3, false);
#elif xOS_ENV_UNIX
    xCHECK_RET(CxConst::xSLASH != csDirPath, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxDir::bIsDir(
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xTEST_EQ(false, csDirPath.empty());

    bool bRv = CxFileAttribute::bIsExists(csDirPath, CxFileAttribute::faDirectory);
    xCHECK_RET(false == bRv, false);

    return true;
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxDir::sGetCurrent() {
    /*DEBUG*/// n/a

    std::tstring_t sRv;
    std::tstring_t sBuff(xPATH_MAX + 1, 0);

#if   xOS_ENV_WIN
    DWORD ulRv = ::GetCurrentDirectory(xPATH_MAX, &sBuff[0]);
    /*DEBUG*/xTEST_DIFF(0UL, ulRv);
    /*DEBUG*/xTEST_LESS(ulRv, static_cast<ulong_t>( xPATH_MAX ));

    sRv.assign(sBuff, 0, ulRv);
#elif xOS_ENV_UNIX
    tchar_t *pszRes = ::getcwd(&sBuff[0], xPATH_MAX);
    /*DEBUG*/xTEST_PTR(pszRes);
    /*DEBUG*/xTEST_EQ(&sBuff.at(0), pszRes);

    sRv.assign(pszRes);
#endif

    return sRv;
}
//--------------------------------------------------------------------------
/* static */
void
CxDir::vSetCurrent(
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xTEST_EQ(false, csDirPath.empty());

    std::tstring_t sDirPath = CxPath::sSlashAppend(csDirPath);

#if   xOS_ENV_WIN
    BOOL blRes = ::SetCurrentDirectory(sDirPath.c_str());
    /*DEBUG*/xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int iRv = ::chdir(sDirPath.c_str());
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
#endif
}
//--------------------------------------------------------------------------
/* static */
std::tstring_t
CxDir::sGetTemp() {
    /*DEBUG*/// n/a

    std::tstring_t sRv;

#if   xOS_ENV_WIN
    std::tstring_t sBuff(xPATH_MAX + 1, 0);

    DWORD ulRv = ::GetTempPath(xPATH_MAX, &sBuff[0]);
    /*DEBUG*/xTEST_DIFF(0UL, ulRv);
    /*DEBUG*/xTEST_LESS(ulRv, static_cast<ulong_t>( xPATH_MAX ));

    sRv.assign(sBuff, 0, ulRv);
#elif xOS_ENV_UNIX
    const std::tstring_t csEnvDirTemp = xT("TMPDIR");

    bool bRv = CxEnvironment::bIsExists(csEnvDirTemp);
    if (true == bRv) {
        sRv = CxEnvironment::sGetVar(csEnvDirTemp);
    } else {
        sRv = xDIR_TEMP;
    }
#endif

    /*DEBUG*/xTEST_EQ(true, bIsExists(sRv));

    return sRv;
}
//--------------------------------------------------------------------------
/* static */
void
CxDir::vCreate(
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xTEST_EQ(false, csDirPath.empty());

    bool bRv = bIsExists(csDirPath);
    xCHECK_DO(true == bRv, return);

#if   xOS_ENV_WIN
    BOOL blRes = ::CreateDirectory(csDirPath.c_str(), NULL);
    /*DEBUG*/xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int iRv = ::mkdir(csDirPath.c_str(), 0755);
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
#endif

    /*DEBUG*/xTEST_EQ(true, bIsExists(csDirPath));
}
//---------------------------------------------------------------------------
void
CxDir::vCreateForce(
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xTEST_EQ(false, csDirPath.empty());

    bool               bRv = false;
    std::vec_tstring_t vsPathParts;
    std::tstring_t     sBuildPath;

    //-------------------------------------
    //split csDirPath into parts
     CxString::vSplit( CxPath::sToCurrentOs(csDirPath, false), CxConst::xSLASH, &vsPathParts );

    //-------------------------------------
    //create dirs by steps
    xFOREACH_CONST(std::vec_tstring_t, it, vsPathParts) {
        sBuildPath.append(*it).append(CxConst::xSLASH);

        vCreate(sBuildPath);
    }

    /*DEBUG*/xTEST_EQ(true, bIsExists(csDirPath));
}
//---------------------------------------------------------------------------
/* static */
void
CxDir::vCopy(
    const std::tstring_t &csDirPathFrom,
    const std::tstring_t &csDirPathTo,
    const bool           &cbFailIfExists
)
{
    /*DEBUG*/xTEST_EQ(false, csDirPathFrom.empty());
    /*DEBUG*/xTEST_EQ(true, bIsExists(csDirPathFrom));
    /*DEBUG*/xTEST_EQ(false, csDirPathTo.empty());
    /*DEBUG*/// cbFailIfExists - n/a

    //-------------------------------------
    //sets attr "normal"
    bool bRv = bIsExists(csDirPathTo);
    if (true == bRv) {
        CxFileAttribute::vSet(csDirPathTo, CxFileAttribute::faNormal);
    }

    CxFileAttribute::vSet(csDirPathFrom, CxFileAttribute::faNormal);

    //--------------------------------------------------
    //get lists of files
    std::vec_tstring_t vsFilePathes;

    vsFilePathes.clear();
    vFindFiles(csDirPathFrom, CxConst::xMASK_ALL, true, &vsFilePathes);

    //--------------------------------------------------
    //copy
    xFOREACH_R_CONST(std::vec_tstring_t, it, vsFilePathes) {
        std::tstring_t sFilePathTo = *it;

        size_t uiPosBegin = sFilePathTo.find(csDirPathFrom);
        /*DEBUG*/xTEST_DIFF(std::tstring_t::npos, uiPosBegin);

        sFilePathTo.replace(uiPosBegin, uiPosBegin + csDirPathFrom.size(), csDirPathTo);

        vCreateForce(CxPath::sGetDir(sFilePathTo));

        CxFile::vCopy(*it, sFilePathTo, cbFailIfExists);
    }

    //--------------------------------------------------
    //TODO: rollback
}
//---------------------------------------------------------------------------
/* static */
void
CxDir::vMove(
    const std::tstring_t &csDirPathFrom,
    const std::tstring_t &csDirPathTo,
    const bool           &cbFailIfExists
)
{
    /*DEBUG*/xTEST_EQ(false, csDirPathFrom.empty());
    /*DEBUG*/xTEST_EQ(true, bIsExists(csDirPathFrom));
    /*DEBUG*/xTEST_EQ(false, csDirPathTo.empty());
    /*DEBUG*/// cbFailIfExists - n/a

    vCopy(csDirPathFrom, csDirPathTo, cbFailIfExists);
    vDeleteForce(csDirPathFrom);
}
//---------------------------------------------------------------------------
/* static */
void
CxDir::vDelete(
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xTEST_EQ(false, csDirPath.empty());

    bool bRv = bIsExists(csDirPath);
    xCHECK_DO(false == bRv, return);

    CxFileAttribute::vSet(csDirPath, CxFileAttribute::faNormal);

#if   xOS_ENV_WIN
    BOOL blRes = ::RemoveDirectory(csDirPath.c_str());
    /*DEBUG*/xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int iRv = ::rmdir(csDirPath.c_str());
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
#endif

    /*DEBUG*/xTEST_EQ(false, bIsExists(csDirPath));
}
//---------------------------------------------------------------------------
/* static */
void
CxDir::vTryDelete(
    const std::tstring_t &csDirPath,
    const size_t         &cuiAttempts,
    const ulong_t        &culTimeoutMsec
)
{
    /*DEBUG*/xTEST_EQ(false, csDirPath.empty());
    /*DEBUG*/xTEST_LESS(size_t(0U), cuiAttempts);

    const size_t cuiMaxAttempts  = 100;  //MAGIC_NUMBER: cuiMaxAttempts
    const size_t cuiRealAttempts = (cuiMaxAttempts < cuiAttempts) ? cuiMaxAttempts : cuiAttempts;

    for (size_t i = 0; i < cuiRealAttempts; ++ i) {
        try {
            vDelete(csDirPath);
            break;
        } 
        catch(const CxException &) {
            xNA;
        }

        bool bRv = CxCurrentThread::bSleep(culTimeoutMsec);
        /*DEBUG*/xTEST_EQ(true, bRv);
    }
}
//---------------------------------------------------------------------------
/* static */
void
CxDir::vClearForce(
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xTEST_EQ(false, csDirPath.empty());
    /*DEBUG*/xTEST_EQ(true, bIsExists(csDirPath));

    //-------------------------------------
    //checks
    bool bRv = bIsEmpty(csDirPath, CxConst::xMASK_ALL);
    xCHECK_DO(true == bRv, return);

    //-------------------------------------
    //delete files
    {
        std::vec_tstring_t vsFilePathes;

        vsFilePathes.clear();
        vFindFiles(csDirPath, CxConst::xMASK_ALL, true, &vsFilePathes);

        xFOREACH_R(std::vec_tstring_t, it, vsFilePathes) {
            CxFile::vDelete(*it);
        }
    }

    //-------------------------------------
    //delete subdirs
    {
        std::vec_tstring_t vsDirPathes;

        vsDirPathes.clear();
        vFindDirs(csDirPath, CxConst::xMASK_ALL, true, &vsDirPathes);

        xFOREACH_R(std::vec_tstring_t, it, vsDirPathes) {
            vDelete(*it);
        }
    }

    /*DEBUG*/xTEST_EQ(true, bIsEmpty(csDirPath));
}
//---------------------------------------------------------------------------
/* static */
void
CxDir::vDeleteForce(
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xTEST_EQ(false, csDirPath.empty());

    bool bRv = bIsExists(csDirPath);
    xCHECK_DO(false == bRv, return);

    vClearForce(csDirPath);
    vDelete(csDirPath);

    /*DEBUG*/xTEST_EQ(false, bIsExists(csDirPath));
}
//--------------------------------------------------------------------------
//TODO: bFindFiles
//http://www.metalshell.com/source_code/86/List_Contents_of_a_Directory.html
/* static */
void
CxDir::vFindFiles(
    const std::tstring_t &csDirPath,
    const std::tstring_t &cMask,
    const bool           &cbIsRecurse,
    std::vec_tstring_t   *pvsFilePathes    ///< \note must be empty
)
{
    /*DEBUG*/xTEST_EQ(false, csDirPath.empty());
    /*DEBUG*/xTEST_EQ(false, cMask.empty());
    /*DEBUG*/// cbIsRecurse - n/a
    /*DEBUG*/xTEST_PTR(pvsFilePathes);

    #if xTODO
        (*pvsFilePathes).clear();
    #endif

#if   xOS_ENV_WIN
    HANDLE          hFile         = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA fdData        = {0};
    std::tstring_t  sFilePath     = CxPath::sToCurrentOs( CxPath::sSlashAppend(csDirPath) + cMask, false );
    std::tstring_t  sFileFullName = CxPath::sGetFileName(sFilePath);
    std::tstring_t  sPart;
    std::tstring_t  sTmpPath;

    //-------------------------------------
    //subdirs
    if (true == cbIsRecurse) {
        sPart    = CxConst::xMASK_ALL;
        sTmpPath = CxPath::sSetFileName(sFilePath, sPart);

        //make search, if dir exists
        fdData.dwFileAttributes = CxFileAttribute::faDirectory;

        hFile = ::FindFirstFile(sTmpPath.c_str(), &fdData);
        if (INVALID_HANDLE_VALUE != hFile) {
            do {
                //skipping files, dirs "." and ".."
                xCHECK_DO(!(fdData.dwFileAttributes & CxFileAttribute::faDirectory), continue);
                xCHECK_DO(CxConst::xDOT  == std::tstring_t(fdData.cFileName),        continue);
                xCHECK_DO(CxConst::x2DOT == std::tstring_t(fdData.cFileName),        continue);

                sPart    = fdData.cFileName;
                sTmpPath = CxPath::sSetFileName(sTmpPath, sPart);

                vFindFiles(sTmpPath, sFileFullName, true, pvsFilePathes);
            }
            while (false != ::FindNextFile(hFile, &fdData));

            BOOL blRes = ::FindClose(hFile);
            /*DEBUG*/xTEST_DIFF(FALSE, blRes);
        }
    }

    //-------------------------------------
    //FIX: files (realy need)
    hFile = ::FindFirstFile(sFilePath.c_str(), &fdData);
    xCHECK_DO(INVALID_HANDLE_VALUE == hFile, return);

    do {
        //skipping dirs
        xCHECK_DO(fdData.dwFileAttributes & CxFileAttribute::faDirectory, continue);

        sPart    = fdData.cFileName;
        sTmpPath = CxPath::sSetFileName(sFilePath/*sTmpPath*/, sPart);

        (*pvsFilePathes).push_back(sTmpPath);
    }
    while (false != ::FindNextFile(hFile, &fdData));

    BOOL blRes = ::FindClose(hFile);
    /*DEBUG*/xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    //-------------------------------------
    //subdirs
    /*if (true == cbIsRecurse)*/ {
        DIR    *pDir     = NULL;
        dirent *pdrEntry = {0};

        pDir = ::opendir(csDirPath.c_str());
        /*DEBUG*/xTEST_PTR(pDir);

        pdrEntry = ::readdir(pDir);
        xCHECK_RET(NULL == pdrEntry, false);

        do {
            //dirs
            if (DT_DIR == pdrEntry->d_type) {
                //skipping "." ".."
                xCHECK_DO(CxConst::xDOT  == std::tstring_t(pdrEntry->d_name), continue);
                xCHECK_DO(CxConst::x2DOT == std::tstring_t(pdrEntry->d_name), continue);

                std::tstring_t sDirPath = csDirPath + CxConst::xSLASH + std::tstring_t(pdrEntry->d_name);

                //is search in subdirs ?
                xCHECK_DO(false == cbIsRecurse, continue);

                vFindFiles(sDirPath, cMask, cbIsRecurse, pvsFilePathes); //recursion
            }
            //TODO: files
            else if (DT_REG == pdrEntry->d_type) {
                std::tstring_t sFilePath = csDirPath + CxConst::xSLASH + std::tstring_t(pdrEntry->d_name);

                (*pvsFilePathes).push_back(sFilePath);
            }
        }
        while (NULL != (pdrEntry = ::readdir(pDir)));

        int iRv = ::closedir(pDir); pDir = NULL;
        /*DEBUG*/xTEST_DIFF(- 1, iRv);
    }

    //-------------------------------------
    //FIX: files (!!!! krivo napisano !!!!)
    #if xTODO
        if (true != cbIsRecurse) {
            DIR    *pDir     = NULL;
            dirent *pdrEntry = {0};

            pDir = opendir(csDirPath.c_str());
            /*DEBUG*/xTEST_PTR(pDir, false);

            pdrEntry = readdir(pDir);
            xCHECK_RET(NULL == pdrEntry, false);

            do {
                //skipping dirs
                xCHECK_DO(DT_DIR == pdrEntry->d_type, continue);

                std::tstring_t sFilePath = csDirPath + CxConst::xSLASH + pdrEntry->d_name;

                (*pvsFilePathes).push_back(sFilePath);
            }
            while ( NULL != (pdrEntry = readdir(pDir)) );

            int iRv = closedir(pDir); pDir = NULL;
            /*DEBUG*/xTEST_DIFF(- 1, iRv);
        }
    #endif
#endif
}
//--------------------------------------------------------------------------
/* static */
void
CxDir::vFindDirs(
    const std::tstring_t &csDirPath,
    const std::tstring_t &cMask,
    const bool           &cbIsRecurse,
    std::vec_tstring_t   *pvsDirPathes    ///< \note must be empty
)
{
    /*DEBUG*/xTEST_EQ(false, csDirPath.empty());
    /*DEBUG*/// cbIsRecurse - n/a
    /*DEBUG*/xTEST_PTR(pvsDirPathes);

    #if xTODO
        (*pvsDirPathes).clear();
    #endif

#if   xOS_ENV_WIN
    HANDLE          hFile        = xNATIVE_HANDLE_INVALID;
    WIN32_FIND_DATA fdData       = {0};
    std::tstring_t  sRootDirPath = CxPath::sToCurrentOs( CxPath::sSlashAppend(csDirPath) + cMask, false );

    hFile = ::FindFirstFile(sRootDirPath.c_str(), &fdData);
    xTEST_DIFF(xNATIVE_HANDLE_INVALID, hFile);

    do {
        //dirs
        if (CxFileAttribute::faDirectory == (fdData.dwFileAttributes & CxFileAttribute::faDirectory)) {
            //skipping "." ".."
            xCHECK_DO(CxConst::xDOT  == std::tstring_t(fdData.cFileName), continue);
            xCHECK_DO(CxConst::x2DOT == std::tstring_t(fdData.cFileName), continue);

            std::tstring_t sDirPath = csDirPath + CxConst::xWIN_SLASH + std::tstring_t(fdData.cFileName);

            (*pvsDirPathes).push_back(sDirPath);

            //is search in subdirs ?
            xCHECK_DO(false == cbIsRecurse, continue);

            vFindDirs(sDirPath, cMask, cbIsRecurse, pvsDirPathes);    //recursion
        }
        //files
        else {
            // n/a
        }
    }
    while (false != ::FindNextFile(hFile, &fdData));

    BOOL blRes = ::FindClose(hFile);
    /*DEBUG*/xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    DIR    *pDir     = NULL;
    dirent *pdrEntry = {0};

    pDir = ::opendir(csDirPath.c_str());
    /*DEBUG*/xTEST_PTR(pDir);

    pdrEntry = ::readdir(pDir);
    xTEST_PTR(pdrEntry);

    do {
        //dirs
        if (DT_DIR == pdrEntry->d_type) {
            //skipping "." ".."
            xCHECK_DO(CxConst::xDOT  == std::tstring_t(pdrEntry->d_name), continue);
            xCHECK_DO(CxConst::x2DOT == std::tstring_t(pdrEntry->d_name), continue);

            std::tstring_t sDirPath = csDirPath + CxConst::xSLASH + std::tstring_t(pdrEntry->d_name);

            (*pvsDirPathes).push_back(sDirPath);

            //is search in subdirs ?
            xCHECK_DO(false == cbIsRecurse, continue);

            (void)bFindDirs(sDirPath, cMask, cbIsRecurse, pvsDirPathes); //recursion
        }
        //TODO: files
        else if (DT_REG == pdrEntry->d_type) {
            // n/a
        }
    }
    while ( NULL != (pdrEntry = ::readdir(pDir)) );

    int iRv = ::closedir(pDir); pDir = NULL;
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
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
