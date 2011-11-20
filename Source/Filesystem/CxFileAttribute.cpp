/**
 * \file  CxFileAttribute.cpp
 * \brief file attributes
 */


#include <xLib/Filesystem/CxFileAttribute.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
/*static*/
bool
CxFileAttribute::bIsExists(
    const std::tstring &csFilePath,
    const EAttribute   cfaValue
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);
    /*DEBUG*/// cfaValue

#if xTEMP_DISABLED
    #if xOS_ENV_WIN
        xCHECK_RET((atGet(csFilePath) & BS_TYPEMASK) == cfaValue, true);
    #endif
#endif

    xCHECK_RET(cfaValue == (atGet(csFilePath) & cfaValue), true);

    return false;
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

#if xOS_ENV_WIN
    faRes = static_cast<EAttribute>( ::GetFileAttributes(csFilePath.c_str()) );
    /*DEBUG*/// n/a
#elif xOS_ENV_UNIX
    xTSTAT_STRUCT stInfo = {0};

    int iRes = ::xTSTAT(csFilePath.c_str(), &stInfo);
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
bool
CxFileAttribute::bSet(
    const std::tstring &csFilePath,
    const EAttribute    cfaValue
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);
    /*DEBUG*/// cfaValue

#if xOS_ENV_WIN
    BOOL bRes = ::SetFileAttributes(csFilePath.c_str(), static_cast<ULONG>(cfaValue));
    /*DEBUG*/xASSERT_RET(FALSE != bRes, false);
#elif xOS_ENV_UNIX
    int iRes = ::xTCHMOD(csFilePath.c_str(), static_cast<mode_t>(cfaValue));
    /*DEBUG*/xASSERT_RET(- 1 != iRes, false);
#endif

    return true;
}
//---------------------------------------------------------------------------
/*static*/
bool
CxFileAttribute::bAdd(
    const std::tstring &csFilePath,
    const EAttribute    cfaValue
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);
    /*DEBUG*/// cfaValue

    return bModify(csFilePath, static_cast<EAttribute>(0), cfaValue);
}
//---------------------------------------------------------------------------
/*static*/
bool
CxFileAttribute::bRemove(
    const std::tstring &csFilePath,
    const EAttribute    cfaValue
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);
    /*DEBUG*/// cfaValue

    return bModify(csFilePath, cfaValue, static_cast<EAttribute>(0));
}
//---------------------------------------------------------------------------
/*static*/
bool
CxFileAttribute::bModify(
    const std::tstring &csFilePath,
    const EAttribute    cfaRemoveValue,
    const EAttribute    cfaAddValue
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);
    /*DEBUG*/// cfaRemoveValue
    /*DEBUG*/// cfaAddValue

    //get the current attributes
    EAttribute cfaValue = atGet(csFilePath);

    //change bits:
    cfaValue = static_cast<EAttribute>( static_cast<ULONG>(cfaValue) & ~cfaRemoveValue );
    cfaValue = static_cast<EAttribute>( static_cast<ULONG>(cfaValue) |  cfaAddValue    );

    //change the attributes
    bool bRes = bSet(csFilePath, cfaValue);
    /*DEBUG*/xASSERT_RET(false != bRes, false);

    return true;
}
//---------------------------------------------------------------------------
//DONE: bClear ()
/*static*/
bool
CxFileAttribute::bClear(
    const std::tstring &csFilePath
)
{
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), false);

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

xNAMESPACE_END(NxLib)
