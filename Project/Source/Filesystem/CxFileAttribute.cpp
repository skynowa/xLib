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
    const std::tstring_t &a_csFilePath,
    const ExAttribute    &a_cfaValue
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_cfaValue);

#if xTEMP_DISABLED
    #if xOS_ENV_WIN
        xCHECK_RET((atGet(a_csFilePath) & BS_TYPEMASK) == cfaValue, true);
    #endif
#endif

    xCHECK_RET(a_cfaValue == (atGet(a_csFilePath) & a_cfaValue), true);

    return false;
}
//---------------------------------------------------------------------------
/* static */
CxFileAttribute::ExAttribute
CxFileAttribute::atGet(
    const std::tstring_t &a_csFilePath
)
{
    xTEST_EQ(false, a_csFilePath.empty());

    ExAttribute faRes = faInvalid;

#if   xOS_ENV_WIN
    faRes = static_cast<ExAttribute>( ::GetFileAttributes(a_csFilePath.c_str()) );
    xTEST_NA(faRes);
#elif xOS_ENV_UNIX
    xTSTAT_STRUCT stInfo = {0};

    int iRv = ::xTSTAT(a_csFilePath.c_str(), &stInfo);
    xTEST_NA(iRv);
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
    const std::tstring_t &a_csFilePath,
    const ExAttribute    &a_cfaValue
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_cfaValue);

#if   xOS_ENV_WIN
    BOOL blRes = ::SetFileAttributes(a_csFilePath.c_str(), static_cast<ulong_t>( a_cfaValue ));
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int iRv = ::xTCHMOD(a_csFilePath.c_str(), static_cast<mode_t>( a_cfaValue ));
    xTEST_DIFF(- 1, iRv);
#endif
}
//---------------------------------------------------------------------------
/* static */
void
CxFileAttribute::vAdd(
    const std::tstring_t &a_csFilePath,
    const ExAttribute    &a_cfaValue
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_cfaValue);

    vModify(a_csFilePath, static_cast<ExAttribute>( 0 ), a_cfaValue);
}
//---------------------------------------------------------------------------
/* static */
void
CxFileAttribute::vRemove(
    const std::tstring_t &a_csFilePath,
    const ExAttribute    &a_cfaValue
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_cfaValue);

    vModify(a_csFilePath, a_cfaValue, static_cast<ExAttribute>( 0 ));
}
//---------------------------------------------------------------------------
/* static */
void
CxFileAttribute::vModify(
    const std::tstring_t &a_csFilePath,
    const ExAttribute    &a_cfaRemoveValue,
    const ExAttribute    &a_cfaAddValue
)
{
    xTEST_EQ(false, a_csFilePath.empty());
    xTEST_NA(a_cfaRemoveValue);
    xTEST_NA(a_cfaValue);

    // get current attributes
    ExAttribute cfaValue = atGet(a_csFilePath);

    // change bits
    cfaValue = static_cast<ExAttribute>( static_cast<ulong_t>( cfaValue ) & ~a_cfaRemoveValue );
    cfaValue = static_cast<ExAttribute>( static_cast<ulong_t>( cfaValue ) |  a_cfaAddValue    );

    // change the attributes
    vSet(a_csFilePath, cfaValue);
}
//---------------------------------------------------------------------------
/* static */
void
CxFileAttribute::vClear(
    const std::tstring_t &csFilePath
)
{
    xTEST_EQ(false, csFilePath.empty());

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
