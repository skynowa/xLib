/**
 * \file  CxDir.cpp
 * \brief directory
 */


#include <xLib/Filesystem/CxDir.h>

#include <xLib/Common/CxChar.h>
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
/*static*/
bool
CxDir::bIsExists(
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), false);

    CxFileAttribute::EAttribute atAttr = CxFileAttribute::atGet(csDirPath);
    /*DEBUG*/// n/a
    xCHECK_RET(CxFileAttribute::faInvalid == atAttr, false);

    bool bRes = CxFileAttribute::bIsExists(csDirPath, CxFileAttribute::faDirectory);

    return bRes;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDir::bIsEmpty(
    const std::tstring_t &csDirPath,
    const std::tstring_t &csMask
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == csMask.empty(),    false);

    bool bRes = false;

    //TODO: CxPath::sToCurrentOs + CxPath::sSlashAppend

#if xOS_ENV_WIN
    HANDLE          hFile    = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA fdData   = {0};
    std::tstring_t  sDirPath = CxPath::sToCurrentOs( CxPath::sSlashAppend(csDirPath) + csMask, false );

    hFile = ::FindFirstFile(sDirPath.c_str(), &fdData);
    xCHECK_RET(INVALID_HANDLE_VALUE == hFile, true);

    do {
        std::tstring_t sFileName = fdData.cFileName;

        if (CxConst::xDOT != sFileName && CxConst::x2DOT != sFileName) {
            bRes = false;   // not empty
            break;
        } else {
            bRes = true;    // empty
        }
    }
    while (false != ::FindNextFile(hFile, &fdData));

    BOOL blRes = ::FindClose(hFile);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    DIR    *pDir     = NULL;
    dirent *pdrEntry = {0};

    pDir = ::opendir(csDirPath.c_str());
    /*DEBUG*/xASSERT_RET(NULL != pDir, true);

    pdrEntry = ::readdir(pDir);
    xCHECK_RET(NULL == pdrEntry, true);

    do {
        std::tstring_t sFileName = pdrEntry->d_name;

        if (CxConst::xDOT != sFileName && CxConst::x2DOT != sFileName) {
            bRes = false;   // not empty
            break;
        } else {
            bRes = true;    // empty
        }
    }
    while (NULL != (pdrEntry = ::readdir(pDir)));

    int iRes = ::closedir(pDir); pDir = NULL;
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);
#endif

    return bRes;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDir::bIsRoot(
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/// n/a

#if xOS_ENV_WIN
    xCHECK_RET(3 != csDirPath.size(), false);

    bool bRes1 = CxChar::bIsAlpha(csDirPath.at(0));
    bool bRes2 = (csDirPath.at(1) == CxConst::xCOLON.at(0));
    bool bRes3 = (csDirPath.at(2) == CxConst::xWIN_SLASH.at(0) || csDirPath.at(2) == CxConst::xNIX_SLASH.at(0));

    xCHECK_RET(false == bRes1 || false == bRes2 || false == bRes3, false);
#elif xOS_ENV_UNIX
    xCHECK_RET(CxConst::xSLASH != csDirPath, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDir::bIsDir(
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), false);

    bool bRes = CxFileAttribute::bIsExists(csDirPath, CxFileAttribute::faDirectory);
    xCHECK_RET(false == bRes, false);

    return true;
}
//--------------------------------------------------------------------------
/*static*/
std::tstring_t
CxDir::sGetCurrent() {
    /*DEBUG*/// n/a

    std::tstring_t sRes;
    std::tstring_t sBuff(xPATH_MAX + 1, 0);

#if xOS_ENV_WIN
    DWORD ulRes = ::GetCurrentDirectory(xPATH_MAX, &sBuff[0]);
    /*DEBUG*/xASSERT_RET(0UL   != ulRes,     std::tstring_t());
    /*DEBUG*/xASSERT_RET(ulRes <  xPATH_MAX, std::tstring_t());

    sRes.assign(sBuff, 0, ulRes);
#elif xOS_ENV_UNIX
    tchar_t *pszRes = ::getcwd(&sBuff[0], xPATH_MAX);
    /*DEBUG*/xASSERT_RET(NULL         != pszRes, std::tstring_t());
    /*DEBUG*/xASSERT_RET(&sBuff.at(0) == pszRes, std::tstring_t());

    sRes.assign(pszRes);
#endif

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
bool
CxDir::bSetCurrent(
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), false);

    std::tstring_t sDirPath = CxPath::sSlashAppend(csDirPath);

#if xOS_ENV_WIN
    BOOL blRes = ::SetCurrentDirectory(sDirPath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    int iRes = ::chdir(sDirPath.c_str());
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);
#endif

    return true;
}
//--------------------------------------------------------------------------
/*static*/
std::tstring_t
CxDir::sGetTemp() {
    /*DEBUG*/// n/a

    std::tstring_t sRes;

#if xOS_ENV_WIN
    std::tstring_t sBuff(xPATH_MAX + 1, 0);

    DWORD ulRes = ::GetTempPath(xPATH_MAX, &sBuff[0]);
    /*DEBUG*/xASSERT_RET(0UL   != ulRes,     std::tstring_t());
    /*DEBUG*/xASSERT_RET(ulRes <  xPATH_MAX, std::tstring_t());

    sRes.assign(sBuff, 0, ulRes);
#elif xOS_ENV_UNIX
    const std::tstring_t csEnvDirTemp = xT("TMPDIR");

    bool bRes = CxEnvironment::bIsExists(csEnvDirTemp);
    if (true == bRes) {
        sRes = CxEnvironment::sGetVar(csEnvDirTemp);
    } else {
        sRes = xDIR_TEMP;
    }
#endif

    /*DEBUG*/xASSERT_RET(true == bIsExists(sRes), std::tstring_t());

    return sRes;
}
//--------------------------------------------------------------------------
/*static*/
bool
CxDir::bCreate(
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), false);

    bool bRes = bIsExists(csDirPath);
    xCHECK_RET(true == bRes, true);

#if xOS_ENV_WIN
    BOOL blRes = ::CreateDirectory(csDirPath.c_str(), NULL);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    int iRes = ::mkdir(csDirPath.c_str(), 0755);
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);
#endif

    /*DEBUG*/xASSERT_RET(true == bIsExists(csDirPath), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxDir::bCreateForce(
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), false);

    bool                        bRes = false;
    std::vector<std::tstring_t> vsPathParts;
    std::tstring_t              sBuildPath;

    //-------------------------------------
    //split csDirPath into parts
    bRes = CxString::bSplit( CxPath::sToCurrentOs(csDirPath, false), CxConst::xSLASH, &vsPathParts );
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    //-------------------------------------
    //create dirs by steps
    xFOREACH_CONST(std::vector<std::tstring_t>, it, vsPathParts) {
        sBuildPath.append(*it).append(CxConst::xSLASH);

        bRes = bCreate(sBuildPath);
        /*DEBUG*/xASSERT_RET(true == bRes, false);
    }

    /*DEBUG*/xASSERT_RET(true == bIsExists(csDirPath), false);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDir::bCopy(
    const std::tstring_t &csDirPathFrom,
    const std::tstring_t &csDirPathTo,
    const bool            cbFailIfExists
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPathFrom.empty(),    false);
    /*DEBUG*/xASSERT_RET(true  == bIsExists(csDirPathFrom), false);
    /*DEBUG*/xASSERT_RET(false == csDirPathTo.empty(),      false);
    /*DEBUG*/// cbFailIfExists - n/a

    //-------------------------------------
    //sets attr "normal"
    bool bRes = bIsExists(csDirPathTo);
    if (true == bRes) {
        bRes = CxFileAttribute::bSet(csDirPathTo, CxFileAttribute::faNormal);
        /*DEBUG*/xASSERT_RET(true == bRes, false);
    }

    bRes = CxFileAttribute::bSet(csDirPathFrom, CxFileAttribute::faNormal);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    //--------------------------------------------------
    //get lists of files
    std::vector<std::tstring_t> vsFilePathes;

    vsFilePathes.clear();
    bRes = bFindFiles(csDirPathFrom, CxConst::xMASK_ALL, true, &vsFilePathes);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    //--------------------------------------------------
    //copy
    xFOREACH_R_CONST(std::vector<std::tstring_t>, it, vsFilePathes) {
        std::tstring_t sFilePathTo = *it;

        size_t uiPosBegin = sFilePathTo.find(csDirPathFrom);
        /*DEBUG*/xASSERT_RET(std::tstring_t::npos != uiPosBegin, false);

        sFilePathTo.replace(uiPosBegin, uiPosBegin + csDirPathFrom.size(), csDirPathTo);

        bRes = bCreateForce(CxPath::sGetDir(sFilePathTo));
        /*DEBUG*/xASSERT_RET(true == bRes, false);

        bRes = CxFile::bCopy(*it, sFilePathTo, cbFailIfExists);
        /*DEBUG*/xASSERT_RET(true == bRes, false);
    }

    //--------------------------------------------------
    //TODO: rollback

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDir::bMove(
    const std::tstring_t &csDirPathFrom,
    const std::tstring_t &csDirPathTo,
    const bool            cbFailIfExists
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPathFrom.empty(),    false);
    /*DEBUG*/xASSERT_RET(true  == bIsExists(csDirPathFrom), false);
    /*DEBUG*/xASSERT_RET(false == csDirPathTo.empty(),      false);
    /*DEBUG*/// cbFailIfExists - n/a

    bool bRes = bCopy(csDirPathFrom, csDirPathTo, cbFailIfExists);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    bRes = bDeleteForce(csDirPathFrom);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDir::bDelete(
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), false);

    bool bRes = bIsExists(csDirPath);
    xCHECK_RET(false == bRes, true);

    bRes = CxFileAttribute::bSet(csDirPath, CxFileAttribute::faNormal);
    /*DEBUG*/xASSERT_RET(true == bRes, false);

#if xOS_ENV_WIN
    BOOL blRes = ::RemoveDirectory(csDirPath.c_str());
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    int iRes = ::rmdir(csDirPath.c_str());
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);
#endif

    /*DEBUG*/xASSERT_RET(false == bIsExists(csDirPath), false);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDir::bTryDelete(
    const std::tstring_t &csDirPath,
    const size_t          cuiAttempts,
    const ulong_t         culTimeoutMsec
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), false);
    /*DEBUG*/xASSERT_RET(0     <  cuiAttempts,       false);

    const size_t cuiMaxAttempts  = 100;  //MAGIC_NUMBER: cuiMaxAttempts
    const size_t cuiRealAttempts = (cuiMaxAttempts < cuiAttempts) ? cuiMaxAttempts : cuiAttempts;

    bool bIsDeleted = false;

    for (size_t i = 0; i < cuiRealAttempts; ++ i) {
        bool bRes = bDelete(csDirPath);
        xCHECK_DO(true == bRes, bIsDeleted = true; break);

        bRes = CxCurrentThread::bSleep(culTimeoutMsec);
        /*DEBUG*/xASSERT_RET(true == bRes, false);
    }

    return bIsDeleted;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDir::bClearForce(
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(),    false);
    /*DEBUG*/xASSERT_RET(true  == bIsExists(csDirPath), false);

    //-------------------------------------
    //checks
    bool bRes = bIsEmpty(csDirPath, CxConst::xMASK_ALL);
    xCHECK_RET(true == bRes, true);

    //-------------------------------------
    //delete files
    {
        std::vector<std::tstring_t> vsFilePathes;

        vsFilePathes.clear();
        bRes = bFindFiles(csDirPath, CxConst::xMASK_ALL, true, &vsFilePathes);
        /*DEBUG*/xASSERT_RET(true == bRes, false);

        xFOREACH_R(std::vector<std::tstring_t>, it, vsFilePathes) {
            (void)CxFile::bDelete(*it);
        }
    }

    //-------------------------------------
    //delete subdirs
    {
        std::vector<std::tstring_t> vsDirPathes;

        vsDirPathes.clear();
        bRes = bFindDirs(csDirPath, CxConst::xMASK_ALL, true, &vsDirPathes);
        /*DEBUG*/xASSERT_RET(true == bRes, false);

        xFOREACH_R(std::vector<std::tstring_t>, it, vsDirPathes) {
            (void)bDelete(*it);
        }
    }

    /*DEBUG*/xASSERT_RET(true == bIsEmpty(csDirPath), false);

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxDir::bDeleteForce(
    const std::tstring_t &csDirPath
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), false);

    bool bRes = bIsExists(csDirPath);
    xCHECK_RET(false == bRes, true);

    (void)bClearForce(csDirPath);

    bRes = bDelete(csDirPath);
    /*DEBUG*/// n/a

    /*DEBUG*/xASSERT_RET(false == bIsExists(csDirPath), false);

    return bRes;  /*true*/
}
//--------------------------------------------------------------------------
//TODO: bFindFiles
//http://www.metalshell.com/source_code/86/List_Contents_of_a_Directory.html
/*static*/
bool
CxDir::bFindFiles(
    const std::tstring_t        &csDirPath,
    const std::tstring_t        &cMask,
    const bool                   cbIsRecurse,
    std::vector<std::tstring_t> *pvsFilePathes    ///< \note must be empty
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), false);
    /*DEBUG*/xASSERT_RET(false == cMask.empty(),     false);
    /*DEBUG*/// cbIsRecurse - n/a
    /*DEBUG*/xASSERT_RET(NULL  != pvsFilePathes,     false);

    #if xTODO
        (*pvsFilePathes).clear();
    #endif

#if xOS_ENV_WIN
    HANDLE          hFile         = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA fdData        = {0};
    std::tstring_t  sFilePath     = CxPath::sToCurrentOs( CxPath::sSlashAppend(csDirPath) + cMask, false );
    std::tstring_t  sFileFullName = CxPath::sGetFullName(sFilePath);
    std::tstring_t  sPart;
    std::tstring_t  sTmpPath;

    //-------------------------------------
    //subdirs
    if (true == cbIsRecurse) {
        sPart    = CxConst::xMASK_ALL;
        sTmpPath = CxPath::sSetFullName(sFilePath, sPart);

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
                sTmpPath = CxPath::sSetFullName(sTmpPath, sPart);

                (void)bFindFiles(sTmpPath, sFileFullName, true, pvsFilePathes);
            }
            while (false != ::FindNextFile(hFile, &fdData));

            BOOL blRes = ::FindClose(hFile);
            /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
        }
    }

    //-------------------------------------
    //FIX: files (realy need)
    hFile = ::FindFirstFile(sFilePath.c_str(), &fdData);
    xCHECK_RET(INVALID_HANDLE_VALUE == hFile, true);

    do {
        //skipping dirs
        xCHECK_DO(fdData.dwFileAttributes & CxFileAttribute::faDirectory, continue);

        sPart    = fdData.cFileName;
        sTmpPath = CxPath::sSetFullName(sFilePath/*sTmpPath*/, sPart);

        (*pvsFilePathes).push_back(sTmpPath);
    }
    while (false != ::FindNextFile(hFile, &fdData));

    BOOL blRes = ::FindClose(hFile);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    //-------------------------------------
    //subdirs
    /*if (true == cbIsRecurse)*/ {
        DIR    *pDir     = NULL;
        dirent *pdrEntry = {0};

        pDir = ::opendir(csDirPath.c_str());
        /*DEBUG*/xASSERT_RET(NULL != pDir, false);

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

                (void)bFindFiles(sDirPath, cMask, cbIsRecurse, pvsFilePathes); //recursion
            }
            //TODO: files
            else if (DT_REG == pdrEntry->d_type) {
                std::tstring_t sFilePath = csDirPath + CxConst::xSLASH + std::tstring_t(pdrEntry->d_name);

                (*pvsFilePathes).push_back(sFilePath);
            }
        }
        while (NULL != (pdrEntry = ::readdir(pDir)));

        int iRes = ::closedir(pDir); pDir = NULL;
        /*DEBUG*/xASSERT_RET(- 1 != iRes, false);
    }

    //-------------------------------------
    //FIX: files (!!!! krivo napisano !!!!)
    #if xTODO
        if (true != cbIsRecurse) {
            DIR    *pDir     = NULL;
            dirent *pdrEntry = {0};

            pDir = opendir(csDirPath.c_str());
            /*DEBUG*/xASSERT_RET(NULL != pDir, false);

            pdrEntry = readdir(pDir);
            xCHECK_RET(NULL == pdrEntry, false);

            do {
                //skipping dirs
                xCHECK_DO(DT_DIR == pdrEntry->d_type, continue);

                std::tstring_t sFilePath = csDirPath + CxConst::xSLASH + pdrEntry->d_name;

                (*pvsFilePathes).push_back(sFilePath);
            }
            while ( NULL != (pdrEntry = readdir(pDir)) );

            int iRes = closedir(pDir); pDir = NULL;
            /*DEBUG*/xASSERT_RET(- 1 != iRes, false);
        }
    #endif
#endif

    return true;
}
//--------------------------------------------------------------------------
/*static*/
bool
CxDir::bFindDirs(
    const std::tstring_t        &csDirPath,
    const std::tstring_t        &cMask,
    const bool                   cbIsRecurse,
    std::vector<std::tstring_t> *pvsDirPathes    ///< \note must be empty
)
{
    /*DEBUG*/xASSERT_RET(false == csDirPath.empty(), false);
    /*DEBUG*/// cbIsRecurse - n/a
    /*DEBUG*/xASSERT_RET(NULL  != pvsDirPathes,      false);

    #if xTODO
        (*pvsDirPathes).clear();
    #endif

#if xOS_ENV_WIN
    HANDLE          hFile        = INVALID_HANDLE_VALUE;
    WIN32_FIND_DATA fdData       = {0};
    std::tstring_t  sRootDirPath = CxPath::sToCurrentOs( CxPath::sSlashAppend(csDirPath) + cMask, false );

    hFile = ::FindFirstFile(sRootDirPath.c_str(), &fdData);
    xCHECK_RET(INVALID_HANDLE_VALUE == hFile, false);

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

            (void)bFindDirs(sDirPath, cMask, cbIsRecurse, pvsDirPathes);    //recursion
        }
        //files
        else {
            // n/a
        }
    }
    while (false != ::FindNextFile(hFile, &fdData));

    BOOL blRes = ::FindClose(hFile);
    /*DEBUG*/xASSERT_RET(FALSE != blRes, false);
#elif xOS_ENV_UNIX
    DIR    *pDir     = NULL;
    dirent *pdrEntry = {0};

    pDir = ::opendir(csDirPath.c_str());
    /*DEBUG*/xASSERT_RET(NULL != pDir, false);

    pdrEntry = ::readdir(pDir);
    xCHECK_RET(NULL == pdrEntry, false);

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

    int iRes = ::closedir(pDir); pDir = NULL;
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);
#endif

    return true;
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
/*virtual*/
CxDir::~CxDir() {

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
