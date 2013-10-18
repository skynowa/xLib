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
    std::ctstring_t &a_filePath
) :
    _filePath(a_filePath)
{
    xTEST_EQ(false, a_filePath.empty());
}
//------------------------------------------------------------------------------
/* virtual */
CxFileType::~CxFileType()
{
}
 //------------------------------------------------------------------------------
std::ctstring_t &
CxFileType::filePath() const
{
    xTEST_EQ(false, _filePath.empty());

    return _filePath;
}
//------------------------------------------------------------------------------
/* static */
bool_t
CxFileType::isExists(
    cExType &a_value
)
{
    xTEST_EQ(false, filePath().empty());
    xTEST_NA(a_value);

    xCHECK_RET(a_value == (get() & a_value), true);

    return false;
}
//------------------------------------------------------------------------------
CxFileType::types_t
CxFileType::get()
{
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
    ctypes_t &a_values
)
{
    xTEST_EQ(false, filePath().empty());
    xTEST_NA(a_values);

#if xOS_ENV_WIN
    BOOL blRes = ::SetFileAttributes(filePath().c_str(), a_values);
    xTEST_DIFF(FALSE, blRes);
#else
    int_t iRv = ::xTCHMOD(filePath().c_str(), a_values);
    xTEST_DIFF(- 1, iRv);
#endif
}
//------------------------------------------------------------------------------
void_t
CxFileType::add(
    cExType &a_value
)
{
    xTEST_EQ(false, filePath().empty());
    xTEST_NA(a_value);

    modify(static_cast<ExType>( 0 ), a_value);
}
//------------------------------------------------------------------------------
void_t
CxFileType::remove(
    cExType &a_value
)
{
    xTEST_EQ(false, filePath().empty());
    xTEST_NA(a_value);

    modify(a_value, static_cast<ExType>( 0 ));
}
//------------------------------------------------------------------------------
void_t
CxFileType::modify(
    cExType &a_valueRemove,
    cExType &a_valueAdd
)
{
    xTEST_EQ(false, filePath().empty());
    xTEST_NA(a_valueRemove);
    xTEST_NA(a_valueAdd);

    // get current attributes
    types_t cfaValues = get();

    // change bits
    cfaValues &= ~a_valueRemove;
    cfaValues |= a_valueAdd;

    // change the attributes
    set(cfaValues);
}
//------------------------------------------------------------------------------
void_t
CxFileType::clear()
{
    xTEST_EQ(false, filePath().empty());

#if xOS_ENV_WIN
    set(faNormal);
#endif
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
