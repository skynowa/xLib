/* 	auto_array_ptr.h - auto_ptr for arrays
	Copyright (C) 2001-2002 Mark Weaver
	Written by Mark Weaver <mark@npsl.co.uk>

	Part of the Open-Win32 library.
	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Library General Public
	License as published by the Free Software Foundation; either
	version 2 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Library General Public License for more details.

	You should have received a copy of the GNU Library General Public
	License along with this library; if not, write to the
	Free Software Foundation, Inc., 59 Temple Place - Suite 330,
	Boston, MA  02111-1307, USA.
*/

/*! \file auto_array_ptr.h
	\brief auto_ptr for arrays
 */

#ifndef auto_array_ptr_h
#define auto_array_ptr_h

namespace OW32
{

template<class _Tp1> struct auto_array_ptr_ref {
  _Tp1* _M_ptr;
  auto_array_ptr_ref(_Tp1* __p) : _M_ptr(__p) {}
};

template <class _Tp> class auto_array_ptr {
private:
  _Tp* _M_ptr;

public:
  typedef _Tp element_type;

  explicit auto_array_ptr(_Tp* __p = 0) throw() : _M_ptr(__p) {}
  auto_array_ptr(auto_array_ptr& __a) throw() : _M_ptr(__a.release()) {}

#if 0 // member templates not supported
  template <class _Tp1> auto_array_ptr(auto_array_ptr<_Tp1>& __a) throw()
    : _M_ptr(__a.release()) {}
#endif

  auto_array_ptr& operator=(auto_array_ptr& __a) throw() {
    if (&__a != this) {
      delete [] _M_ptr;
      _M_ptr = __a.release();
    }
    return *this;
  }

#if 0 // member templates not supported
  template <class _Tp1>
  auto_array_ptr& operator=(auto_array_ptr<_Tp1>& __a) throw() {
    if (__a.get() != this->get()) {
      delete [] _M_ptr;
      _M_ptr = __a.release();
    }
    return *this;
  }
#endif

  // Note: The C++ standard says there is supposed to be an empty throw
  // specification here, but omitting it is standard conforming.  Its 
  // presence can be detected only if _Tp::~_Tp() throws, but (17.4.3.6/2)
  // this is prohibited.
  ~auto_array_ptr() { delete [] _M_ptr; }

  _Tp& operator*() const throw() {
    return *_M_ptr;
  }
  _Tp& operator[](size_t index) throw() {
	  return _M_ptr[index];
  }
  const _Tp& operator[](size_t index) const throw() {
	  return _M_ptr[index];
  }
/*  _Tp* operator->() const throw() {
    return _M_ptr;
  }*/
  _Tp* get() const throw() {
    return _M_ptr;
  }
  _Tp* release() throw() {
    _Tp* __tmp = _M_ptr;
    _M_ptr = 0;
    return __tmp;
  }
  void reset(_Tp* __p = 0) throw() {
    if (__p != _M_ptr) {
      delete [] _M_ptr;
      _M_ptr = __p;
    }
  }

  // According to the C++ standard, these conversions are required.  Most
  // present-day compilers, however, do not enforce that requirement---and, 
  // in fact, most present-day compilers do not support the language 
  // features that these conversions rely on.

#if 0 // member templates not supported
public:
  auto_array_ptr(auto_array_ptr_ref<_Tp> __ref) throw()
    : _M_ptr(__ref._M_ptr) {}

  auto_array_ptr& operator=(auto_array_ptr_ref<_Tp> __ref) throw() {
    if (__ref._M_ptr != this->get()) {
      delete [] _M_ptr;
      _M_ptr = __ref._M_ptr;
    }
    return *this;
  }

  template <class _Tp1> operator auto_array_ptr_ref<_Tp1>() throw() 
    { return auto_array_ptr_ref<_Tp1>(this->release()); }
  template <class _Tp1> operator auto_array_ptr<_Tp1>() throw()
    { return auto_array_ptr<_Tp1>(this->release()); }
#endif
};

} // namespace OW32

#endif // auto_array_ptr