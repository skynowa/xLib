/****************************************************************************
* Class name:  CxFileAttribute
* Description: file attribute
* File name:   CxFileAttribute.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     06.04.2010 13:37:54
*
*****************************************************************************/


#include <xLib/Filesystem/CxFileAttribute.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bIsExists (is exists)
/*static*/
BOOL
CxFileAttribute::bIsExists(
    const tString    &csFilePath,
    const EAttribute  cfaValue
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// cfaValue

#if xTEMP_DISABLED
    #if defined(xOS_WIN)
        xCHECK_RET((atGet(csFilePath) & BS_TYPEMASK) == cfaValue, TRUE);
    #endif
#endif

    xCHECK_RET(cfaValue == (atGet(csFilePath) & cfaValue), TRUE);

    return FALSE;
}
//---------------------------------------------------------------------------
//DONE: atGet (get)
/*static*/
CxFileAttribute::EAttribute
CxFileAttribute::atGet(
    const tString &csFilePath
)
{
    /*DEBUG*/// csFilePath - n/a

    EAttribute faRes = faInvalid;

#if defined(xOS_WIN)
    faRes = static_cast<EAttribute>( ::GetFileAttributes(csFilePath.c_str()) );
    /*DEBUG*/// n/a
#elif defined(xOS_LINUX)
    struct stat stInfo = {0};

    INT iRes = _tstat(csFilePath.c_str(), &stInfo);
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
//DONE: bSet (set)
/*static*/
BOOL
CxFileAttribute::bSet(
    const tString    &csFilePath,
    const EAttribute  cfaValue
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// cfaValue

#if defined(xOS_WIN)
    BOOL bRes = ::SetFileAttributes(csFilePath.c_str(), static_cast<ULONG>(cfaValue));
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    INT iRes = _tchmod(csFilePath.c_str(), static_cast<mode_t>(cfaValue));
    /*DEBUG*/xASSERT_RET(- 1 != iRes, FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bAdd (add)
/*static*/
BOOL
CxFileAttribute::bAdd(
    const tString    &csFilePath,
    const EAttribute  cfaValue
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// cfaValue

    return bModify(csFilePath, static_cast<EAttribute>(0), cfaValue);
}
//---------------------------------------------------------------------------
//DONE: bRemove (remove)
/*static*/
BOOL
CxFileAttribute::bRemove(
    const tString    &csFilePath,
    const EAttribute  cfaValue
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// cfaValue

    return bModify(csFilePath, cfaValue, static_cast<EAttribute>(0));
}
//---------------------------------------------------------------------------
//DONE: bModify (modify)
/*static*/
BOOL
CxFileAttribute::bModify(
    const tString    &csFilePath,
    const EAttribute  cfaRemoveValue,
    const EAttribute  cfaAddValue
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// cfaRemoveValue
    /*DEBUG*/// cfaAddValue

    BOOL bRes = FALSE;

    //get the current attributes
    EAttribute cfaValue = atGet(csFilePath);

    //change bits:
    cfaValue = static_cast<EAttribute>( static_cast<ULONG>(cfaValue) & ~cfaRemoveValue );
    cfaValue = static_cast<EAttribute>( static_cast<ULONG>(cfaValue) |  cfaAddValue    );

    //change the attributes
    bRes = bSet(csFilePath, cfaValue);
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bClear (clear)
/*static*/
BOOL
CxFileAttribute::bClear(
    const tString &csFilePath
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
//DONE: CxFileAttribute
CxFileAttribute::CxFileAttribute() {

}
//---------------------------------------------------------------------------
//DONE: ~CxFileAttribute
/*virtual*/
CxFileAttribute::~CxFileAttribute() {

}
//---------------------------------------------------------------------------
