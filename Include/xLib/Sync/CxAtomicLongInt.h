/**
 * \file  CxAtomicLongInt.h
 * \brief CxAtomicLongInt operartions with long_t
 */


#ifndef xLib_Sync_CxAtomicLongIntH
#define xLib_Sync_CxAtomicLongIntH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxAtomicLongInt :
    private CxNonCopyable
    /// CxAtomicLongInt operartions with long_t
{
    public:
                         CxAtomicLongInt();
        virtual         ~CxAtomicLongInt();

        CxAtomicLongInt& operator +=    (const CxAtomicLongInt &calValue);
        CxAtomicLongInt& operator +=    (const long_t cliRight);

        CxAtomicLongInt& operator -=    (const CxAtomicLongInt &calValue);
        CxAtomicLongInt& operator -=    (const long_t cliRight);

        CxAtomicLongInt& operator =     (const CxAtomicLongInt &calValue);
        CxAtomicLongInt& operator =     (const long_t cliRight);

        bool             operator ==    (const CxAtomicLongInt &calValue) const ;
        bool             operator ==    (const long_t cliRight) const ;

        bool             operator !=    (const CxAtomicLongInt &calValue) const ;
        bool             operator !=    (const long_t cliRight) const ;

        bool             operator <     (const long_t &cliValue) const;
        bool             operator <     (const CxAtomicLongInt &calValue) const;

        bool             operator <=    (const long_t &cliValue) const;
        bool             operator <=    (const CxAtomicLongInt &calValue) const;

        bool             operator >     (const long_t &cliValue) const;
        bool             operator >     (const CxAtomicLongInt &calValue) const;

        bool             operator >=    (const long_t &cliValue) const;
        bool             operator >=    (const CxAtomicLongInt &calValue) const;

        CxAtomicLongInt& operator ++    (const int ciValue);
        CxAtomicLongInt& operator --    (const int ciValue);

        long_t           liGetValue     () const;

    private:
        volatile long_t  _m_liValue;
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxAtomicLongIntH


/*
    InterlockedCompareExchange - __sync_val_compare_and_swap

*/
