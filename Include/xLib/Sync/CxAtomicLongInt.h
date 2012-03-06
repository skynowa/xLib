/**
 * \file  CxAtomicLongInt.h
 * \brief atomic operartions with long_t
 */


#ifndef xLib_Sync_CxAtomicLongIntH
#define xLib_Sync_CxAtomicLongIntH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxAtomicLongInt :
    private CxNonCopyable
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
        CxAtomicLongInt& operator ++     (const long_t cliPos);
        CxAtomicLongInt& operator --     (const long_t cliPos);

    private:
        volatile long_t  _m_liValue;
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif    //xLib_Sync_CxAtomicLongIntH
