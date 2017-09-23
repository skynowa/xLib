/**
 * \file  Observer.h
 * \brief observer
 */


#pragma once


#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, patterns)

template<typename T>
class xNO_VTABLE IObserver
    /// observer interface
{
public:
                    IObserver() {}
    virtual        ~IObserver() {}

    virtual void_t  update(cint_t &type, const T &message) = 0;
};
//-------------------------------------------------------------------------------------------------
template<typename T>
class Observer
    /// observer
{
public:
    Observer()
    {
    }
        ///< constructor
    virtual ~Observer()
    {
        _observers.clear();
    }
        ///< destructor

    void_t attach(IObserver<T> *a_observer)
    {
        _observers.push_back(a_observer);
    }
        ///< attach object
    void_t detach(IObserver<T> *a_observer)
    {
        xFOR_EACH(typename std::vector<IObserver<T> *>, it, _observers) {
            if (*it == a_observer) {
                _observers.erase(it);
            }
        }
    }
        ///< dettach object
    void_t updateAll(cint_t &a_type, const T &a_message)
    {
        xFOR_EACH(typename std::vector<IObserver<T> *>, it, _observers) {
            (*it)->update(a_type, a_message);
        }
    }
        ///< update all objects

private:
    std::vector<IObserver<T> *> _observers;    ///< objects container

    xNO_COPY_ASSIGN(Observer)
};

xNAMESPACE_END2(xl, patterns)
//-------------------------------------------------------------------------------------------------
