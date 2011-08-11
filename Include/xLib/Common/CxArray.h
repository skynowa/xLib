/****************************************************************************
* Class name:  CxArray
* Description: fixed-size array
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     28.03.2011 14:40:50
*
*****************************************************************************/


#ifndef xLib_Common_CxArrayH
#define xLib_Common_CxArrayH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
template <class TypeT, std::size_t uiNumT>
class CxArray {
    public:
        TypeT tArray[uiNumT];

    public:
        //--------------------------------------------------
        //types
        typedef TypeT           value_type;
        typedef TypeT         * iterator;
        typedef const TypeT   * const_iterator;
        typedef TypeT         & reference;
        typedef const TypeT   & const_reference;
        typedef std::size_t     size_type;
        typedef std::ptrdiff_t  difference_type;

        //--------------------------------------------------
        //iterators
        iterator
        begin() {
            return tArray;
        }

        const_iterator
        begin() const {
            return tArray;
        }

        iterator
        end() {
            return tArray + uiNumT;
        }

        const_iterator
        end() const {
            return tArray + uiNumT;
        }

        //--------------------------------------------------
        //reverse iterators
        typedef std::reverse_iterator<iterator>       reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        reverse_iterator
        rbegin() {
            return reverse_iterator(end());
        }

        const_reverse_iterator
        rbegin() const {
            return const_reverse_iterator(end());
        }

        reverse_iterator
        rend() {
            return reverse_iterator(begin());
        }

        const_reverse_iterator
        rend() const {
            return const_reverse_iterator(begin());
        }

        //--------------------------------------------------
        //operator[]
        reference
        operator[](size_type i) {
            /*DEBUG*/xASSERT_MSG(i < uiNumT, xT("out of range"));

            return tArray[i];
        }

        const_reference
        operator[](size_type i) const {
            /*DEBUG*/xASSERT_MSG(i < uiNumT, xT("out of range"));

            return tArray[i];
        }

        //--------------------------------------------------
        //at() with range check
        reference
        at(size_type i) {
            rangecheck(i);

            return tArray[i];
        }

        const_reference
        at(size_type i) const {
            rangecheck(i);

            return tArray[i];
        }

        //--------------------------------------------------
        //front(), back()
        reference
        front() {
            return tArray[0];
        }

        const_reference
        front() const {
            return tArray[0];
        }

        reference
        back() {
            return tArray[uiNumT - 1];
        }

        const_reference
        back() const {
            return tArray[uiNumT - 1];
        }

        //--------------------------------------------------
        //size is constant
        static
        size_type
        size() {
            return uiNumT;
        }

        static
        bool
        empty() {
            return false;
        }

        static
        size_type
        max_size() {
            return uiNumT;
        }

        enum {
            static_size = uiNumT
        };

        //--------------------------------------------------
        //swap (note: linear complexity)
        void
        swap(CxArray<TypeT,uiNumT> &y) {
            for (size_type i = 0; i < uiNumT; ++ i) {
                std::swap(tArray[i], y.tArray[i]);
            }
        }

        //--------------------------------------------------
        //direct access to data (read-only)
        const TypeT *
        data() const {
            return tArray;
        }

        TypeT *
        data() {
            return tArray;
        }

        //--------------------------------------------------
        //use CxArray as C array (direct read/write access to data)
        TypeT*
        c_array() {
            return tArray;
        }

        //--------------------------------------------------
        //assignment with type conversion
        template <typename T2>
        CxArray<TypeT, uiNumT> &
        operator = (const CxArray<T2, uiNumT> &rhs) {
            std::copy(rhs.begin(), rhs.end(), begin());

            return *this;
        }

        //--------------------------------------------------
        //assign one value to all elements
        void
        assign(const TypeT &value) { // A synonym for fill
            fill(value);
        }

        void
        fill(const TypeT &value) {
            std::fill_n(begin(), size(), value);
        }

        void
        clear() {
            fill(0);
        }

        //--------------------------------------------------
        // check range (may be private because it is static)
        static
        void
        rangecheck(size_type i) {
            if (i >= size()) {
                /////boost::out_of_range e("CxArray<>: index out of range");
                /////boost::throw_exception(e);

                std::out_of_range e("CxArray<>: index out of range");
                throw std::exception(e);
            }
        }
};
//---------------------------------------------------------------------------
namespace NxArray {
    //comparisons
    template<class T, std::size_t N>
    bool
    operator == (const CxArray<T,N> &x, const CxArray<T,N> &y) {
        return std::equal(x.begin(), x.end(), y.begin());
    }

    template<class T, std::size_t N>
    bool
    operator < (const CxArray<T, N> &x, const CxArray<T, N> &y) {
        return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
    }

    template<class T, std::size_t N>
    bool
    operator != (const CxArray<T, N> &x, const CxArray<T,N> &y) {
        return !(x == y);
    }

    template<class T, std::size_t N>
    bool
    operator > (const CxArray<T, N> &x, const CxArray<T, N> &y) {
        return y < x;
    }

    template<class T, std::size_t N>
    bool
    operator <= (const CxArray<T, N> &x, const CxArray<T, N> &y) {
        return !(y < x);
    }

    template<class T, std::size_t N>
    bool
    operator >= (const CxArray<T, N> &x, const CxArray<T, N> &y) {
        return !(x < y);
    }

    //global swap()
    template<class T, std::size_t N>
    inline
    void
    swap (CxArray<T, N > &x, CxArray<T, N> &y) {
        x.swap(y);
    }
}

namespace NxArray {
    //DONE: make_array (2 elements)
    template<typename T>
    CxArray<T, 2>
    make_array(const T &t1, const T &t2) {
        CxArray<T, 2> aArrayT = {{t1, t2}};

        return aArrayT;
    }

    //DONE: make_array (3 elements)
    template<typename T>
    CxArray<T, 3>
    make_array(const T &t1, const T &t2, const T &t3) {
        CxArray<T, 3> aArrayT = {{t1, t2, t3}};

        return aArrayT;
    }
}
//---------------------------------------------------------------------------
#include <Common/CxArray.inl>
//---------------------------------------------------------------------------
#endif //xLib_Common_CxArrayH
