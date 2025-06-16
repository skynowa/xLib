/**
 * \file  IpcSemaphore.cpp
 * \brief semaphore
 */


#include "IpcSemaphore.h"

#include <xLib/Core/Const.h>
#include <xLib/Fs/Path.h>
#include <xLib/Log/LogStream.h>

#if   xENV_WIN
    #include "Platform/Win/IpcSemaphore_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/IpcSemaphore_unix.inl"
#endif


namespace xl::sync
{

/**************************************************************************************************
*    public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
IpcSemaphore::IpcSemaphore()
{
    xTEST(!_isValid());

    _ctor_impl();
}
//-------------------------------------------------------------------------------------------------
IpcSemaphore::~IpcSemaphore()
{
    xTEST(_isValid());

    _dtor_impl();
}
//-------------------------------------------------------------------------------------------------
long_t
IpcSemaphore::valueMax() const
{
    return _valueMax_impl();
}
//-------------------------------------------------------------------------------------------------
const IpcSemaphore::handle_t &
IpcSemaphore::handle() const
{
    xTEST(_isValid());

    return _handle;
}
//-------------------------------------------------------------------------------------------------
void_t
IpcSemaphore::create(
    clong_t          a_initialValue,
    std::ctstring_t &a_name
)
{
    xTEST(!_isValid());
    xTEST_LESS_EQ(a_name.size(), Path::maxSize());
    xTEST(0L <= a_initialValue && a_initialValue <= valueMax());

    _create_impl(a_initialValue, a_name);
}
//-------------------------------------------------------------------------------------------------
void_t
IpcSemaphore::open(
    std::ctstring_t &a_name
)
{
    xTEST(_isValid());
    xTEST_NA(a_name);

    _open_impl(a_name);
}
//-------------------------------------------------------------------------------------------------
void_t
IpcSemaphore::post() const
{
	xTEST(_isValid());

    _post_impl();
}
//-------------------------------------------------------------------------------------------------
void_t
IpcSemaphore::wait(
    culong_t a_timeoutMsec
) const
{
    xTEST(_isValid());
    xTEST_NA(a_timeoutMsec);

    _wait_impl(a_timeoutMsec);
}
//-------------------------------------------------------------------------------------------------
long_t
IpcSemaphore::value() const
{
    xTEST(_isValid());

    return _value_impl();
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
bool_t
IpcSemaphore::_isValid() const
{
    return _isValid_impl();
}
//-------------------------------------------------------------------------------------------------

} // namespace
