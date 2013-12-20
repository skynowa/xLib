/**
 * \file  CxFileType.cpp
 * \brief file type
 */


#include <xLib/Test/xTest.h>
#include <xLib/Debug/xDebug.h>
#include <xLib/Debug/CxLastError.h>
#include <xLib/Debug/CxStdError.h>
#include <xLib/Debug/CxStackTrace.h>
#include <xLib/Debug/CxErrorReport.h>
#include <xLib/Debug/CxDebugger.h>
#include <xLib/Log/CxTracer.h>


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxFileType::CxFileType(
    std::ctstring_t &a_filePath
) :
    _filePath(a_filePath)
{
    xTEST_EQ(false, a_filePath.empty());
}
//-------------------------------------------------------------------------------------------------
inline std::ctstring_t &
CxFileType::filePath() const
{
    xTEST_EQ(false, _filePath.empty());

    return _filePath;
}
//-------------------------------------------------------------------------------------------------
/* static */
inline bool_t
CxFileType::isExists(
    cExType &a_value
) const
{
    xTEST_EQ(false, filePath().empty());
    xTEST_NA(a_value);

    xCHECK_RET(a_value == (get() & a_value), true);

    return false;
}
//-------------------------------------------------------------------------------------------------
inline CxFileType::types_t
CxFileType::get() const
{
    xTEST_EQ(false, filePath().empty());

    types_t ftRv = faInvalid;

#if   xOS_ENV_WIN
    ftRv = ::GetFileAttributes(filePath().c_str());
    xTEST_NA(ftRv);
#else xOS_ENV_UNIX
    xTSTAT_STRUCT info;   xSTRUCT_ZERO(info);

    int_t iRv = ::xTSTAT(filePath().c_str(), &info);
    xTEST_NA(iRv);
    if (- 1 == iRv) {
        ftRv = faInvalid;
    } else {
        ftRv = (info.st_mode & S_IFMT);
    }
#endif

    return ftRv;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFileType::set(
    ctypes_t &a_values
) const
{
    xTEST_EQ(false, filePath().empty());
    xTEST_NA(a_values);

#if   xOS_ENV_WIN
    BOOL blRv = ::SetFileAttributes(filePath().c_str(), a_values);
    xTEST_DIFF(FALSE, blRv);
#else xOS_ENV_UNIX
    int_t iRv = ::xTCHMOD(filePath().c_str(), a_values);
    xTEST_DIFF(- 1, iRv);
#endif
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFileType::add(
    cExType &a_value
) const
{
    xTEST_EQ(false, filePath().empty());
    xTEST_NA(a_value);

    modify(static_cast<ExType>( 0 ), a_value);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFileType::remove(
    cExType &a_value
) const
{
    xTEST_EQ(false, filePath().empty());
    xTEST_NA(a_value);

    modify(a_value, static_cast<ExType>( 0 ));
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFileType::modify(
    cExType &a_valueRemove,
    cExType &a_valueAdd
) const
{
    xTEST_EQ(false, filePath().empty());
    xTEST_NA(a_valueRemove);
    xTEST_NA(a_valueAdd);

    // get current attributes
    types_t values = get();

    // change bits
    values &= ~a_valueRemove;
    values |= a_valueAdd;

    // change the attributes
    set(values);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxFileType::clear() const
{
    xTEST_EQ(false, filePath().empty());

#if xOS_ENV_WIN
    set(faNormal);
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
