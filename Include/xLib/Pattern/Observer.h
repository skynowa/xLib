/**
 * \file  Observer.h
 * \brief observer
 */


#pragma once


#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::patterns
{

template<typename T>
class IObserver
    /// Observer interface
{
public:
///\name ctors, dtor
///\{
			 IObserver() = default;
	virtual ~IObserver() = default;
///\}

    virtual void_t update(cint_t &type, const T &message) = 0;
};
//-------------------------------------------------------------------------------------------------
template<typename T>
class Observers
    /// Observers
{
public:
///\name ctors, dtor
///\{
		Observers() = default;

	virtual ~Observers()
	{
		_observers.clear();
	}

	xNO_COPY_ASSIGN(Observers)
///\}

    void_t attach(IObserver<T> *a_observer)
    {
        _observers.push_back(a_observer);
    }
        ///< attach object
    void_t detach(IObserver<T> *a_observer)
    {
        for (const auto &it_observer : _observers) {
            if (*it_observer == a_observer) {
                _observers.erase(it_observer);
            }
        }
    }
        ///< dettach object
    void_t updateAll(cint_t a_type, const T &a_message)
    {
        for (const auto &it_observer: _observers) {
        	it_observer->update(a_type, a_message);
        }
    }
        ///< update all objects

private:
    std::vector<IObserver<T> *> _observers;    ///< objects container
};

} // namespace
//-------------------------------------------------------------------------------------------------
