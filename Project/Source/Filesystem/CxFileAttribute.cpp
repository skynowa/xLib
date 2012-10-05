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
    const ExAttribute    &cfaValue
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
void
CxFileAttribute::vSet(
    const std::tstring_t &csFilePath,
    const ExAttribute    &cfaValue
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
}
//---------------------------------------------------------------------------
/* static */
void
CxFileAttribute::vAdd(
    const std::tstring_t &csFilePath,
    const ExAttribute    &cfaValue
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// cfaValue

    vModify(csFilePath, static_cast<ExAttribute>( 0 ), cfaValue);
}
//---------------------------------------------------------------------------
/* static */
void
CxFileAttribute::vRemove(
    const std::tstring_t &csFilePath,
    const ExAttribute    &cfaValue
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());
    /*DEBUG*/// cfaValue

    vModify(csFilePath, cfaValue, static_cast<ExAttribute>( 0 ));
}
//---------------------------------------------------------------------------
/* static */
void
CxFileAttribute::vModify(
    const std::tstring_t &csFilePath,
    const ExAttribute    &cfaRemoveValue,
    const ExAttribute    &cfaAddValue
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
    vSet(csFilePath, cfaValue);
}
//---------------------------------------------------------------------------
/* static */
void
CxFileAttribute::vClear(
    const std::tstring_t &csFilePath
)
{
    /*DEBUG*/xTEST_EQ(false, csFilePath.empty());

    vSet(csFilePath, faNormal);
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
