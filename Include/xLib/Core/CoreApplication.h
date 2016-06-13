/**
 * \file   CoreApplication.h
 * \brief
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/Application.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, core)

class CoreApplication :
    public Application
    /// application
{
public:
                   CoreApplication(std::ctstring_t &appGuid, std::ctstring_t &locale);
        ///< constructor
    virtual       ~CoreApplication();
        ///< destructor

    int_t          run();
        ///< run

    // handles
    virtual int_t  onRun() = 0;
        ///< run handle
    static  void_t onSignals(int_t a_signal);
        ///< signals handle
    static  void_t onExit();
        ///< exit handle
    static  void_t onTerminate();
        ///< terminate handle
    static  void_t onUnexpected();
        ///< unexpected handle

private:
    xNO_COPY_ASSIGN(CoreApplication)
};

xNAMESPACE_END2(xlib, core)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "CoreApplication.cpp"
#endif
