/**
 * \file  Sleeper.h
 * \brief sleeper
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Sync/Event.h>
//-------------------------------------------------------------------------------------------------
namespace xl::sync
{

class Sleeper
    /// sleeper
{
public:
///@name ctors, dtor
///@{
			 Sleeper();
	virtual ~Sleeper() = default;

	xNO_COPY_ASSIGN(Sleeper)
///@}

    void_t sleep(culong_t &timeoutMsec);
        ///< sleep
    void_t wakeUp();
        ///< wake up
    bool_t isSleeping() const;
        ///< check for sleeping

private:
    Event _event;    ///< event object
};

} // namespace
//-------------------------------------------------------------------------------------------------
