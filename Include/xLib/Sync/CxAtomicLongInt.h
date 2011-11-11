/**
 * \file  CxAtomicLongInt.h
 * \brief atomic operartions with LONG
 */


#ifndef xLib_Sync_CxAtomicLongIntH
#define xLib_Sync_CxAtomicLongIntH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
#if defined(xOS_ENV_WIN)

xNAMESPACE_BEGIN(NxLib)

class CxAtomicLongInt :
    public CxNonCopyable
    /// atomic operartions with LONG
{
    public:
                         CxAtomicLongInt();
        virtual         ~CxAtomicLongInt();

        CxAtomicLongInt& operator +=   (const CxAtomicLongInt &cRight);
        CxAtomicLongInt& operator -=   (const CxAtomicLongInt &cRight);
        CxAtomicLongInt& operator =    (const CxAtomicLongInt &cRight);
        CxAtomicLongInt& operator +=   (const LONG cliRight);
        CxAtomicLongInt& operator -=   (const LONG cliRight);
        CxAtomicLongInt& operator =    (const LONG cliRight);
        BOOL             operator ==   (const CxAtomicLongInt &cRight) const ;
        BOOL             operator !=   (const CxAtomicLongInt &cRight) const ;
        BOOL             operator ==   (const LONG cliRight) const ;
        BOOL             operator !=   (const LONG cliRight) const ;
                         operator LONG () const ;
                         operator BOOL () const ;
        CxAtomicLongInt& operator ++   (int iPos);
        CxAtomicLongInt& operator --   (int iPos);

    private:
        LONG             _m_liValue;
};

xNAMESPACE_END(NxLib)

#endif
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxAtomicLongIntH
