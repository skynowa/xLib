/**
 * \file  CxIpcSemaphore.inl
 * \brief semaphore
 */


#include <xLib/Core/CxConst.h>
#include <xLib/Filesystem/CxPath.h>

#if   xENV_WIN
    #include "Platform/Win/CxIpcSemaphore_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/CxIpcSemaphore_unix.inl"

    #if   xENV_LINUX
        // #include "Platform/Linux/CxIpcSemaphore_linux.inl"
    #elif xENV_BSD
        // #include "Platform/Bsd/CxIpcSemaphore_bsd.inl"
    #elif xENV_APPLE
        // #include "Platform/Unix/CxIpcSemaphore_apple.inl"
    #endif
#endif


xNAMESPACE_BEGIN2(xlib, sync)

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxIpcSemaphore::CxIpcSemaphore() :
#if   xENV_WIN
    _handle(),
#elif xENV_UNIX
    _handle(xPTR_NULL),
#endif
    _name  ()
{
    xTEST_EQ(_isValid(), false);

    _construct_impl();
}
//-------------------------------------------------------------------------------------------------
inline
CxIpcSemaphore::~CxIpcSemaphore()
{
    xTEST_EQ(_isValid(), true);

    _destruct_impl();
}
//-------------------------------------------------------------------------------------------------
inline const CxIpcSemaphore::handle_t &
CxIpcSemaphore::handle() const
{
    xTEST_EQ(_isValid(), true);

    return _handle;
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcSemaphore::create(
    clong_t         &a_initialValue,
    std::ctstring_t &a_name
)
{
    xTEST_EQ(_isValid(), false);
    xTEST_GR(CxPath::maxSize(), a_name.size());
    xTEST_EQ(0L <= a_initialValue && a_initialValue <= xSEMAPHORE_VALUE_MAX, true);

    _create_impl(a_initialValue, a_name);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcSemaphore::open(
    std::ctstring_t &a_name
)
{
    xTEST_EQ(_isValid(), true);
    //name    - n/a

    _open_impl(a_name);
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcSemaphore::post() const
{
    xTEST_EQ(_isValid(), true);

    _post_impl();
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxIpcSemaphore::wait(
    culong_t &a_timeoutMsec
) const
{
    xTEST_EQ(_isValid(), true);
    xTEST_NA(a_timeoutMsec);

    _wait_impl(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------
inline long_t
CxIpcSemaphore::value() const
{
    xTEST_EQ(_isValid(), true);

    return _value_impl();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline bool_t
CxIpcSemaphore::_isValid() const
{
    return _isValid_impl();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, sync)
