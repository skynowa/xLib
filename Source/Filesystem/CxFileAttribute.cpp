/**
 * \file  CxFileAttribute.cpp
 * \brief file attributes
 */


#include <xLib/Filesystem/CxFileAttribute.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
BOOL
CxFileAttribute::bIsExists(
    const std::tstring &csFilePath,
    const EAttribute   cfaValue
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// cfaValue

#if xTEMP_DISABLED
    #if defined(xOS_ENV_WIN)
        xCHECK_RET((atGet(csFilePath) & BS_TYPEMASK) == cfaValue, TRUE);
    #endif
#endif

    xCHECK_RET(cfaValue == (atGet(csFilePath) & cfaValue), TRUE);

    return FALSE;
}
//---------------------------------------------------------------------------
/*static*/
CxFileAttribute::EAttribute
CxFileAttribute::atGet(
    const std::tstring &csFilePath
)
{
    /*DEBUG*/// csFilePath - n/a

    EAttribute faRes = faInvalid;

#if defined(xOS_ENV_WIN)
    faRes = static_cast<EAttribute>( ::GetFileAttributes(csFilePath.c_str()) );
    /*DEBUG*/// n/a
#elif defined(xOS_ENV_UNIX)
    xTSTAT_STRUCT stInfo = {0};

    INT iRes = xTSTAT(csFilePath.c_str(), &stInfo);
    /*DEBUG*/// n/a
    if (- 1 == iRes) {
        faRes = faInvalid;
    } else {
        faRes = static_cast<EAttribute>( stInfo.st_mode & S_IFMT );
    }
#endif

    return faRes;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFileAttribute::bSet(
    const std::tstring &csFilePath,
    const EAttribute    cfaValue
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// cfaValue

#if defined(xOS_ENV_WIN)
    BOOL bRes = ::SetFileAttributes(csFilePath.c_str(), static_cast<ULONG>(cfaValue));
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_ENV_UNIX)
    INT iRes = xTCHMOD(csFilePath.c_str(), static_cast<mode_t>(cfaValue));
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFileAttribute::bAdd(
    const std::tstring &csFilePath,
    const EAttribute    cfaValue
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// cfaValue

    return bModify(csFilePath, static_cast<EAttribute>(0), cfaValue);
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFileAttribute::bRemove(
    const std::tstring &csFilePath,
    const EAttribute    cfaValue
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// cfaValue

    return bModify(csFilePath, cfaValue, static_cast<EAttribute>(0));
}
//---------------------------------------------------------------------------
/*static*/
BOOL
CxFileAttribute::bModify(
    const std::tstring &csFilePath,
    const EAttribute    cfaRemoveValue,
    const EAttribute    cfaAddValue
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// cfaRemoveValue
    /*DEBUG*/// cfaAddValue

    //get the current attributes
    EAttribute cfaValue = atGet(csFilePath);

    //change bits:
    cfaValue = static_cast<EAttribute>( static_cast<ULONG>(cfaValue) & ~cfaRemoveValue );
    cfaValue = static_cast<EAttribute>( static_cast<ULONG>(cfaValue) |  cfaAddValue    );

    //change the attributes
    BOOL bRes = bSet(csFilePath, cfaValue);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bClear ()
/*static*/
BOOL
CxFileAttribute::bClear(
    const std::tstring &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);

    return bSet(csFilePath, faNormal);
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxFileAttribute::CxFileAttribute() {

}
//---------------------------------------------------------------------------
/*virtual*/
CxFileAttribute::~CxFileAttribute() {

}
//---------------------------------------------------------------------------
