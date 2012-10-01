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
/* static */
bool
CxFileAttribute::bIsExists(
    const std::tstring_t &csFilePath,
    const ExAttribute     cfaValue
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// cfaValue

#if xTEMP_DISABLED
    #if   xOS_ENV_WIN
        xCHECK_RET((atGet(csFilePath) & BS_TYPEMASK) == cfaValue, true);
    #endif
#endif

    xCHECK_RET(cfaValue == (atGet(csFilePath) & cfaValue), true);

    return false;
}
//---------------------------------------------------------------------------
/* static */
CxFileAttribute::ExAttribute
CxFileAttribute::atGet(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/// csFilePath - n/a

    ExAttribute faRes = faInvalid;

#if   xOS_ENV_WIN
    faRes = static_cast<ExAttribute>( ::GetFileAttributes(csFilePath.c_str()) );
    /*DEBUG*/// n/a
#elif xOS_ENV_UNIX
    xTSTAT_STRUCT stInfo = {0};

    int iRv = ::xTSTAT(csFilePath.c_str(), &stInfo);
    /*DEBUG*/// n/a
    if (- 1 == iRv) {
        faRes = faInvalid;
    } else {
        faRes = static_cast<ExAttribute>( stInfo.st_mode & S_IFMT );
    }
#endif

    return faRes;
}
//---------------------------------------------------------------------------
/* static */
bool
CxFileAttribute::bSet(
    const std::tstring_t &csFilePath,
    const ExAttribute      cfaValue
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// cfaValue

#if   xOS_ENV_WIN
    BOOL blRes = ::SetFileAttributes(csFilePath.c_str(), static_cast<ulong_t>( cfaValue ));
    /*DEBUG*/xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int iRv = ::xTCHMOD(csFilePath.c_str(), static_cast<mode_t>( cfaValue ));
    /*DEBUG*/xTEST_DIFF(- 1, iRv);
#endif

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxFileAttribute::bAdd(
    const std::tstring_t &csFilePath,
    const ExAttribute     cfaValue
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// cfaValue

    return bModify(csFilePath, static_cast<ExAttribute>( 0 ), cfaValue);
}
//---------------------------------------------------------------------------
/* static */
bool
CxFileAttribute::bRemove(
    const std::tstring_t &csFilePath,
    const ExAttribute     cfaValue
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// cfaValue

    return bModify(csFilePath, cfaValue, static_cast<ExAttribute>( 0 ));
}
//---------------------------------------------------------------------------
/* static */
bool
CxFileAttribute::bModify(
    const std::tstring_t &csFilePath,
    const ExAttribute     cfaRemoveValue,
    const ExAttribute     cfaAddValue
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// cfaRemoveValue
    /*DEBUG*/// cfaAddValue

    // get the current attributes
    ExAttribute cfaValue = atGet(csFilePath);

    // change bits
    cfaValue = static_cast<ExAttribute>( static_cast<ulong_t>( cfaValue ) & ~cfaRemoveValue );
    cfaValue = static_cast<ExAttribute>( static_cast<ulong_t>( cfaValue ) |  cfaAddValue    );

    // change the attributes
    bool bRv = bSet(csFilePath, cfaValue);
    /*DEBUG*/xTEST_EQ(true, bRv);

    return true;
}
//---------------------------------------------------------------------------
/* static */
bool
CxFileAttribute::bClear(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());

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
/* virtual */
CxFileAttribute::~CxFileAttribute() {

}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
