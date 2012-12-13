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
CxFileAttribute::CxFileAttribute(
    const std::tstring_t &csFilePath
) :
    _m_csFilePath(csFilePath)
{
    xTEST_EQ(false, csFilePath.empty());
}
//---------------------------------------------------------------------------
/* virtual */
CxFileAttribute::~CxFileAttribute() {

}
 //---------------------------------------------------------------------------
const std::tstring_t &
CxFileAttribute::sFilePath() const {
    return _m_csFilePath;
}
//---------------------------------------------------------------------------
/* static */
bool
CxFileAttribute::bIsExists(
    const ExAttribute &a_cfaValue
)
{
    xTEST_EQ(false, sFilePath().empty());
    xTEST_NA(a_cfaValue);

#if xTEMP_DISABLED
    #if xOS_ENV_WIN
        xCHECK_RET(cfaValue == (atGet() & BS_TYPEMASK), true);
    #endif
#endif

    xCHECK_RET(a_cfaValue == (atGet() & a_cfaValue), true);

    return false;
}
//---------------------------------------------------------------------------
CxFileAttribute::ExAttribute
CxFileAttribute::atGet() {
    xTEST_EQ(false, sFilePath().empty());

    ExAttribute faRes = faInvalid;

#if   xOS_ENV_WIN
    faRes = static_cast<ExAttribute>( ::GetFileAttributes(sFilePath().c_str()) );
    xTEST_NA(faRes);
#elif xOS_ENV_UNIX
    xTSTAT_STRUCT stInfo = {0};

    int iRv = ::xTSTAT(sFilePath().c_str(), &stInfo);
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
void
CxFileAttribute::vSet(
    const ExAttribute &a_cfaValue
)
{
    xTEST_EQ(false, sFilePath().empty());
    xTEST_NA(a_cfaValue);

#if   xOS_ENV_WIN
    BOOL blRes = ::SetFileAttributes(sFilePath().c_str(), static_cast<ulong_t>( a_cfaValue ));
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int iRv = ::xTCHMOD(sFilePath().c_str(), static_cast<mode_t>( a_cfaValue ));
    xTEST_DIFF(- 1, iRv);
#endif
}
//---------------------------------------------------------------------------
void
CxFileAttribute::vAdd(
    const ExAttribute &a_cfaValue
)
{
    xTEST_EQ(false, sFilePath().empty());
    xTEST_NA(a_cfaValue);

    vModify(static_cast<ExAttribute>( 0 ), a_cfaValue);
}
//---------------------------------------------------------------------------
void
CxFileAttribute::vRemove(
    const ExAttribute &a_cfaValue
)
{
    xTEST_EQ(false, sFilePath().empty());
    xTEST_NA(a_cfaValue);

    vModify(a_cfaValue, static_cast<ExAttribute>( 0 ));
}
//---------------------------------------------------------------------------
void
CxFileAttribute::vModify(
    const ExAttribute &a_cfaRemoveValue,
    const ExAttribute &a_cfaAddValue
)
{
    xTEST_EQ(false, sFilePath().empty());
    xTEST_NA(a_cfaRemoveValue);
    xTEST_NA(a_cfaValue);

    // get current attributes
    ExAttribute cfaValue = atGet();

    // change bits
    cfaValue = static_cast<ExAttribute>( static_cast<ulong_t>( cfaValue ) & ~a_cfaRemoveValue );
    cfaValue = static_cast<ExAttribute>( static_cast<ulong_t>( cfaValue ) |  a_cfaAddValue    );

    // change the attributes
    vSet(cfaValue);
}
//---------------------------------------------------------------------------
void
CxFileAttribute::vClear() {
    xTEST_EQ(false, sFilePath().empty());

    vSet(faNormal);
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
