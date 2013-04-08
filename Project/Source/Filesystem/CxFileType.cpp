/**
 * \file  CxFileType.cpp
 * \brief file type
 */


#include <xLib/Filesystem/CxFileType.h>


xNAMESPACE_BEGIN(NxLib)

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxFileType::CxFileType(
    std::ctstring_t &a_csFilePath
) :
    _m_csFilePath(a_csFilePath)
{
    xTEST_EQ(false, a_csFilePath.empty());
}
//------------------------------------------------------------------------------
/* virtual */
CxFileType::~CxFileType() {

}
 //------------------------------------------------------------------------------
std::ctstring_t &
CxFileType::filePath() const {
    xTEST_EQ(false, _m_csFilePath.empty());

    return _m_csFilePath;
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxFileType::isExists(
    cExType &a_cftValue
)
{
    xTEST_EQ(false, filePath().empty());
    xTEST_NA(a_cftValue);

    xCHECK_RET(a_cftValue == (get() & a_cftValue), true);

    return false;
}
//------------------------------------------------------------------------------
CxFileType::types_t
CxFileType::get() {
    xTEST_EQ(false, filePath().empty());

    types_t ftRv = faInvalid;

#if xOS_ENV_WIN
    ftRv = ::GetFileAttributes(filePath().c_str());
    xTEST_NA(ftRv);
#else
    xTSTAT_STRUCT stInfo = {0};

    int_t iRv = ::xTSTAT(filePath().c_str(), &stInfo);
    xTEST_NA(iRv);
    if (- 1 == iRv) {
        ftRv = faInvalid;
    } else {
        ftRv = (stInfo.st_mode & S_IFMT);
    }
#endif

    return ftRv;
}
//------------------------------------------------------------------------------
void_t
CxFileType::set(
    ctypes_t &a_cftValues
)
{
    xTEST_EQ(false, filePath().empty());
    xTEST_NA(a_cftValue);

#if xOS_ENV_WIN
    BOOL blRes = ::SetFileAttributes(filePath().c_str(), a_cftValues);
    xTEST_DIFF(FALSE, blRes);
#else
    int_t iRv = ::xTCHMOD(filePath().c_str(), a_cftValues);
    xTEST_DIFF(- 1, iRv);
#endif
}
//------------------------------------------------------------------------------
void_t
CxFileType::add(
    cExType &a_cftValue
)
{
    xTEST_EQ(false, filePath().empty());
    xTEST_NA(a_cftValue);

    modify(static_cast<ExType>( 0 ), a_cftValue);
}
//------------------------------------------------------------------------------
void_t
CxFileType::remove(
    cExType &a_cftValue
)
{
    xTEST_EQ(false, filePath().empty());
    xTEST_NA(a_cftValue);

    modify(a_cftValue, static_cast<ExType>( 0 ));
}
//------------------------------------------------------------------------------
void_t
CxFileType::modify(
    cExType &a_cftRemoveValue,
    cExType &a_cftAddValue
)
{
    xTEST_EQ(false, filePath().empty());
    xTEST_NA(a_cftRemoveValue);
    xTEST_NA(a_cftAddValue);

    // get current attributes
    types_t cfaValues = get();

    // change bits
    cfaValues &= ~a_cftRemoveValue;
    cfaValues |= a_cftAddValue;

    // change the attributes
    set(cfaValues);
}
//------------------------------------------------------------------------------
void_t
CxFileType::clear() {
    xTEST_EQ(false, filePath().empty());

#if xOS_ENV_WIN
    set(faNormal);
#endif
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
