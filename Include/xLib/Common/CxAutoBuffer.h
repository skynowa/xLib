/**
 * \file  CxAutoBuffer.h
 * \brief auto buffer
 */


//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
template<class T>
class CxAutoBuffer :
    public CxNonCopyable
    /// auto buffer
{
    private:
        T* buffer;

    public:

        explicit CxAutoBuffer (size_t size = 0) throw()
            : buffer (size == 0 ? NULL : new T[size]())
        {
        }

        ~CxAutoBuffer()
        {
            delete[] buffer;
        }

        operator T*() const throw()
        {
            return buffer;
        }

        operator void*() const throw()
        {
            return buffer;
        }

        operator bool() const throw()
        {
            return buffer != NULL;
        }

        T* operator->() const throw()
        {
            return buffer;
        }

        T *get() const throw()
        {
            return buffer;
        }

        T* release() throw()
        {
            T* temp = buffer;
            buffer = NULL;
            return temp;
        }

        void reset (size_t newSize = 0)
        {
            delete[] buffer;
            buffer = (newSize == 0 ? NULL : new T[newSize]);
        }
};
//---------------------------------------------------------------------------
