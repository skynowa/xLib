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
CxFileAttribute::filePath() const {
    xTEST_EQ(false, _m_csFilePath.empty());

    return _m_csFilePath;
}
//---------------------------------------------------------------------------
/* static */
bool
CxFileAttribute::isExists(
    const ExAttribute &a_cfaValue
)
{
    xTEST_EQ(false, filePath().empty());
    xTEST_NA(a_cfaValue);

#if xTEMP_DISABLED
    #if xOS_ENV_WIN
        xCHECK_RET(cfaValue == (get() & BS_TYPEMASK), true);
    #endif
#endif

    xCHECK_RET(a_cfaValue == (get() & a_cfaValue), true);

    return false;
}
//---------------------------------------------------------------------------
CxFileAttribute::ExAttribute
CxFileAttribute::get() {
    xTEST_EQ(false, filePath().empty());

    ExAttribute faRes = faInvalid;

#if   xOS_ENV_WIN
    faRes = static_cast<ExAttribute>( ::GetFileAttributes(filePath().c_str()) );
    xTEST_NA(faRes);
#elif xOS_ENV_UNIX
    xTSTAT_STRUCT stInfo = {0};

    int iRv = ::xTSTAT(filePath().c_str(), &stInfo);
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
CxFileAttribute::set(
    const ExAttribute &a_cfaValue
)
{
    xTEST_EQ(false, filePath().empty());
    xTEST_NA(a_cfaValue);

#if   xOS_ENV_WIN
    BOOL blRes = ::SetFileAttributes(filePath().c_str(), static_cast<ulong_t>( a_cfaValue ));
    xTEST_DIFF(FALSE, blRes);
#elif xOS_ENV_UNIX
    int iRv = ::xTCHMOD(filePath().c_str(), static_cast<mode_t>( a_cfaValue ));
    xTEST_DIFF(- 1, iRv);
#endif
}
//---------------------------------------------------------------------------
void
CxFileAttribute::add(
    const ExAttribute &a_cfaValue
)
{
    xTEST_EQ(false, filePath().empty());
    xTEST_NA(a_cfaValue);

    modify(static_cast<ExAttribute>( 0 ), a_cfaValue);
}
//---------------------------------------------------------------------------
void
CxFileAttribute::remove(
    const ExAttribute &a_cfaValue
)
{
    xTEST_EQ(false, filePath().empty());
    xTEST_NA(a_cfaValue);

    modify(a_cfaValue, static_cast<ExAttribute>( 0 ));
}
//---------------------------------------------------------------------------
void
CxFileAttribute::modify(
    const ExAttribute &a_cfaRemoveValue,
    const ExAttribute &a_cfaAddValue
)
{
    xTEST_EQ(false, filePath().empty());
    xTEST_NA(a_cfaRemoveValue);
    xTEST_NA(a_cfaValue);

    // get current attributes
    ExAttribute cfaValue = get();

    // change bits
    cfaValue = static_cast<ExAttribute>( static_cast<ulong_t>( cfaValue ) & ~a_cfaRemoveValue );
    cfaValue = static_cast<ExAttribute>( static_cast<ulong_t>( cfaValue ) |  a_cfaAddValue    );

    // change the attributes
    set(cfaValue);
}
//---------------------------------------------------------------------------
void
CxFileAttribute::clear() {
    xTEST_EQ(false, filePath().empty());

    set(faNormal);
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
