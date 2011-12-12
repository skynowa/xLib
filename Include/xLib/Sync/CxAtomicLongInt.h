/**
 * \file  CxAtomicLongInt.h
 * \brief atomic operartions with long_t
 */


#ifndef xLib_Sync_CxAtomicLongIntH
#define xLib_Sync_CxAtomicLongIntH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

class CxAtomicLongInt :
    public CxNonCopyable
    /// atomic operartions with long_t
{
    public:
                         CxAtomicLongInt ();
        virtual         ~CxAtomicLongInt ();

        CxAtomicLongInt& operator +=     (const CxAtomicLongInt &cRight);
        CxAtomicLongInt& operator -=     (const CxAtomicLongInt &cRight);
        CxAtomicLongInt& operator =      (const CxAtomicLongInt &cRight);
        CxAtomicLongInt& operator +=     (const long_t cliRight);
        CxAtomicLongInt& operator -=     (const long_t cliRight);
        CxAtomicLongInt& operator =      (const long_t cliRight);
        bool             operator ==     (const CxAtomicLongInt &cRight) const ;
        bool             operator !=     (const CxAtomicLongInt &cRight) const ;
        bool             operator ==     (const long_t cliRight) const ;
        bool             operator !=     (const long_t cliRight) const ;
                         operator long_t () const ;
                         operator bool   () const ;
        CxAtomicLongInt& operator ++     (int iPos);
        CxAtomicLongInt& operator --     (int iPos);

    private:
        long_t           _m_liValue;
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxAtomicLongIntH
