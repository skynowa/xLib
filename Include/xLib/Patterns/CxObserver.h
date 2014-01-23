/**
 * \file  CxObserver.h
 * \brief observer
 */


#pragma once


#ifndef xLib_CxObserverH
#define xLib_CxObserverH
//-------------------------------------------------------------------------------------------------
#include <xLib/Core/xCore.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE2_BEGIN(xlib, patterns)

template <class T>
class IxObserver
{
public:
                    IxObserver() {}
    virtual        ~IxObserver() {}

    virtual void_t  update(cint_t &type, const T &message) = 0;
};
//-------------------------------------------------------------------------------------------------
template <class T>
class CxObserver
{
public:
    CxObserver()
    {
    }
        ///< constructor
    virtual ~CxObserver()
    {
        _observers.clear();
    }
        ///< destructor

    void_t attach(IxObserver<T> *a_observer)
    {
        _observers.push_back(a_observer);
    }
        ///< attach object
    void_t detach(IxObserver<T> *a_observer)
    {
        xFOREACH(typename std::vector<IxObserver<T> *>, it, _observers) {
            if (*it == a_observer) {
                _observers.erase(it);
            }
        }
    }
        ///< dettach object
    void_t updateAll(cint_t &a_type, const T &a_message)
    {
        xFOREACH(typename std::vector<IxObserver<T> *>, it, _observers) {
            (*it)->update(a_type, a_message);
        }
    }
        ///< update all objects

private:
    std::vector<IxObserver<T> *> _observers;    ///< objects container

    xNO_COPY_ASSIGN(CxObserver)
};

xNAMESPACE2_END(xlib, patterns)
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxObserverH
