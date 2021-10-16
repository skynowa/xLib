/**
 * \file   Signal.h
 * \brief  signal
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::sync
{

class Signal
    ///< signal
{
public:
#if   xENV_WIN
    using on_info_t = void_t(*) (int_t sig);
#elif xENV_UNIX
    using on_info_t = void_t(*) (int_t sig, siginfo_t* siginfo, void_t* context);
#endif
        ///< signal info handler type
    using on_exit_t = void_t (*)();
        ///< exit handler type

///@name ctors, dtor
///@{
			 Signal() = default;
	virtual ~Signal() = default;

	xNO_COPY_ASSIGN(Signal)
///@}

    std::sig_atomic_t state() const;
        ///< get state flag
    void_t   setState(const std::sig_atomic_t &state);
        ///< set state flag

    void_t   connect(const std::vector<int_t> &signalNums, const sighandler_t onSignals) const;
        ///< set signal handle
    void_t   connectAll(const sighandler_t onSignals) const;
        ///< set all signal handle
    void_t   connectInfo(const std::vector<int_t> &signalNums, const on_info_t onInfo) const;
        ///< set signal handle
    void_t   connectInfoAll(const on_info_t onInfo) const;
        ///< set all signal handle
    void_t   connectExit(const on_exit_t onExit) const;
        ///< set exit handle
    void_t   connectTerminate(const std::terminate_handler onTerminate) const;
        ///< set terminate handle (by default, the terminate handler calls abort)
    void_t   connectUnexpected(const std::unexpected_handler onUnexpected) const;
        ///< set unexpected handler
    void_t   raise(cint_t &signalNum) const;
        ///< sends signal to the current executing program

    static
    bool_t   isValid(cint_t &signalNum);
        ///< check whether a given signal is valid for the current machine
    static
    std::tstring_t decription(cint_t &signalNum);
        ///< string describing signal
    static
    std::tstring_t infoDescription(const siginfo_t &info);
        ///< string describing signal code

private:
    volatile
    std::sig_atomic_t _state {};
        ///< Integral type of an object that can be accessed as an atomic entity,
        ///< even in the presence of asynchronous signals.

xPLATFORM_IMPL:
    static
    std::tstring_t _decription_impl(cint_t &signalNum);
        ///< string describing signal
};

} // namespace
//-------------------------------------------------------------------------------------------------
