/**
 * \file  CxArray.h
 * \brief fixed-size array
 */


#pragma once

#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

template<typename T, std::size_t N>
class CxArray
    /// array
{
public:
    T elems[N];    // fixed-size array of elements of type T

public:
    // type definitions
    typedef T              value_type;
    typedef T*             iterator;
    typedef const T*       const_iterator;
    typedef T&             reference;
    typedef const T&       const_reference;
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;

    // iterator support
    iterator        begin()        { return elems; }
    const_iterator  begin()  const { return elems; }
    const_iterator  cbegin() const { return elems; }

    iterator        end()          { return elems + N; }
    const_iterator  end()    const { return elems + N; }
    const_iterator  cend()   const { return elems + N; }

    // reverse iterator support
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(BOOST_MSVC_STD_ITERATOR) && !defined(BOOST_NO_STD_ITERATOR_TRAITS)
    typedef std::reverse_iterator<iterator>       reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
#else
    // workaround for broken reverse_iterator implementations
    typedef std::reverse_iterator<iterator,T>       reverse_iterator;
    typedef std::reverse_iterator<const_iterator,T> const_reverse_iterator;
#endif

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }
    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }
    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }
    const_reverse_iterator crend() const {
        return const_reverse_iterator(begin());
    }

    // operator[]
    reference operator[](size_type i) {
        ////BOOST_ASSERT( i < N && "out of range" );
        return elems[i];
    }

    const_reference operator[](size_type i) const {
        ////BOOST_ASSERT( i < N && "out of range" );
        return elems[i];
    }

    // at() with range check
    reference       at(size_type i)       { rangecheck(i); return elems[i]; }
    const_reference at(size_type i) const { rangecheck(i); return elems[i]; }

    // front() and back()
    reference front() {
        return elems[0];
    }

    const_reference front() const {
        return elems[0];
    }

    reference back() {
        return elems[N - 1];
    }

    const_reference back() const {
        return elems[N - 1];
    }

    // size is constant
    static size_type size    () { return N; }
    static bool_t      empty   () { return false; }
    static size_type max_size() { return N; }
    enum { static_size = N };

    // swap (note: linear complexity)
    void_t swap (CxArray<T, N> &y) {
        for (size_type i = 0; i < N; ++ i) {
            /*boost*/std::swap(elems[i], y.elems[i]);
        }
    }

    // direct access to data (read-only)
    const T* data() const {
        return elems;
    }
    T* data() {
        return elems;
    }

    // use array as C array (direct read/write access to data)
    T* c_array() {
        return elems;
    }

    // assignment with type conversion
    template <typename T2>
    CxArray<T,N>& operator= (const CxArray<T2, N> &rhs) {
    std::copy(rhs.begin(), rhs.end(), begin());
        return *this;
    }

    // assign one value to all elements
    void_t assign(const T &value) {
        fill(value);
    }    // A synonym for fill

    void_t fill(const T &value) {
        std::fill_n(begin(),size(),value);
    }

    void_t clear() {
        fill(0);
    }

    // check range (may be private because it is static)
    static void_t rangecheck (size_type i) {
        if (i >= size()) {
            std::out_of_range e("array<>: index out of range");
            ////boost::throw_exception(e);
        }
    }
};


// comparisons
namespace NxArray {
    template<typename T, std::size_t N>
    bool_t operator == (const CxArray<T, N> &x, const CxArray<T, N> &y) {
        return std::equal(x.begin(), x.end(), y.begin());
    }
    template<typename T, std::size_t N>
    bool_t operator< (const CxArray<T, N> &x, const CxArray<T, N> &y) {
        return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
    }
    template<typename T, std::size_t N>
    bool_t operator != (const CxArray<T, N> &x, const CxArray<T, N> &y) {
        return !(x == y);
    }
    template<typename T, std::size_t N>
    bool_t operator > (const CxArray<T, N> &x, const CxArray<T, N> &y) {
        return (y < x);
    }
    template<typename T, std::size_t N>
    bool_t operator <= (const CxArray<T, N> &x, const CxArray<T, N> &y) {
        return !(y < x);
    }
    template<typename T, std::size_t N>
    bool_t operator >= (const CxArray<T, N> &x, const CxArray<T, N> &y) {
        return !(x < y);
    }

    // global swap()
    template<typename T, std::size_t N>
    inline void_t swap(CxArray<T, N> &x, CxArray<T, N> &y) {
        x.swap(y);
    }
}

#if xTEMP_DISABLED
    // Specific for boost::array: simply returns its elems data member.
    template <typename T, std::size_t N>
    T(&get_c_array(boost::CxArray<T, N> &arg))[N] {
        return arg.elems;
    }

    // Const version.
    template <typename T, std::size_t N>
    const T(&get_c_array(const boost::CxArray<T, N> &arg))[N] {
        return arg.elems;
    }
#endif

#if 0
    // Overload for std::array, assuming that std::array will have
    // explicit conversion functions as discussed at the WG21 meeting
    // in Summit, March 2009.
    template <typename T, std::size_t N>
    T(&get_c_array(std::array<T,N> &arg))[N] {
        return static_cast<T(&)[N]>(arg);
    }

    // Const version.
    template <typename T, std::size_t N>
    const T(&get_c_array(const std::array<T, N> &arg))[N] {
        return static_cast<T(&)[N]>(arg);
    }
#endif
//------------------------------------------------------------------------------
namespace NxArray {
    //make_array (2 elements)
    template<typename T>
    CxArray<T, 2>
    make_array(const T &t1, const T &t2) {
        CxArray<T, 2> aArrayT = {{t1, t2}};

        return aArrayT;
    }

    //make_array (3 elements)
    template<typename T>
    CxArray<T, 3>
    make_array(const T &t1, const T &t2, const T &t3) {
        CxArray<T, 3> aArrayT = {{t1, t2, t3}};

        return aArrayT;
    }
}

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------

#include "CxArray.inl"
