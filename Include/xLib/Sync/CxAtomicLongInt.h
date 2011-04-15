/****************************************************************************
* Class name:  CxAtomicLongInt
* Description: atomic operartions with LONG
* File name:   CxAtomicLongInt.h
* Compilers:   Visual C++ 2008
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, xLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     25.11.2009 10:03:17
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef xLib_Sync_CxAtomicLongIntH
#define xLib_Sync_CxAtomicLongIntH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxAtomicLongInt : public CxNonCopyable {  
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
		CxAtomicLongInt& operator ++   (INT iPos);
		CxAtomicLongInt& operator --   (INT iPos);

	private:
		LONG             _m_liValue;
};
//---------------------------------------------------------------------------
#endif	//xLib_Sync_CxAtomicLongIntH

/*
//Performs an atomic addition operation on the specified LONG values.
InterlockedAdd	
//Performs an atomic addition operation on the specified LONGLONG values.
InterlockedAdd64
//Performs an atomic addition operation on the specified LONG values. The operation is performed with acquire memory access semantics.
InterlockedAddAcquire	
//Performs an atomic addition operation on the specified LONGLONG values. The operation is performed with acquire memory access semantics.
InterlockedAddAcquire64
//Performs an atomic addition operation on the specified LONG values. The operation is performed with release memory access semantics.
InterlockedAddRelease
//Performs an atomic addition operation on the specified LONGLONG values. The operation is performed with release memory access semantics.
InterlockedAddRelease64
//Performs an atomic AND operation on the specified LONG values.
InterlockedAnd
//Performs an atomic AND operation on the specified LONG values. The operation is performed with acquire memory access semantics.
InterlockedAndAcquire
//Performs an atomic AND operation on the specified LONG values. The operation is performed with release memory access semantics.
InterlockedAndRelease
//Performs an atomic AND operation on the specified char values.
InterlockedAnd8
//Performs an atomic AND operation on the specified char values. The operation is performed with acquire memory access semantics.
InterlockedAnd8Acquire
//Performs an atomic AND operation on the specified char values. The operation is performed with release memory access semantics.
InterlockedAnd8Release
//Performs an atomic AND operation on the specified SHORT values.
InterlockedAnd16
//Performs an atomic AND operation on the specified SHORT values. The operation is performed with acquire memory access semantics.
InterlockedAnd16Acquire
//Performs an atomic AND operation on the specified SHORT values. The operation is performed with release memory access semantics.
InterlockedAnd16Release
//Performs an atomic AND operation on the specified LONGLONG values.
InterlockedAnd64
//Performs an atomic AND operation on the specified LONGLONG values. The operation is performed with acquire memory access semantics.
InterlockedAnd64Acquire
//Performs an atomic AND operation on the specified LONGLONG values. The operation is performed with release memory access semantics.
InterlockedAnd64Release
//Tests the specified bit of the specified LONG value and sets it to 0.
InterlockedBitTestAndReset
//Tests the specified bit of the specified LONG64 value and sets it to 0.
InterlockedBitTestAndReset64
//Tests the specified bit of the specified LONG value and sets it to 1.
InterlockedBitTestAndSet
//Tests the specified bit of the specified LONG64 value and sets it to 1.
InterlockedBitTestAndSet64
//Performs an atomic compare-and-exchange operation on the specified values. The function compares the specified 64-bit values and exchanges with the specified 128-bit value based on the outcome of the comparison.
InterlockedCompare64Exchange128
//Performs an atomic compare-and-exchange operation on the specified values. The function compares the specified 64-bit values and exchanges with the specified 128-bit value based on the outcome of the comparison. The operation is performed with acquire memory access semantics.
InterlockedCompare64ExchangeAcquire128
//Performs an atomic compare-and-exchange operation on the specified values. The function compares the specified 64-bit values and exchanges with the specified 128-bit value based on the outcome of the comparison. The operation is performed with release memory access semantics.
InterlockedCompare64ExchangeRelease128
//Performs an atomic compare-and-exchange operation on the specified values. The function compares two specified 32-bit values and exchanges with another 32-bit value based on the outcome of the comparison.
InterlockedCompareExchange
//Performs an atomic compare-and-exchange operation on the specified values. The function compares two specified 64-bit values and exchanges with another 64-bit value based on the outcome of the comparison.
InterlockedCompareExchange64
//Performs an atomic compare-and-exchange operation on the specified values. The function compares two specified 32-bit values and exchanges with another 32-bit value based on the outcome of the comparison. The operation is performed with acquire memory access semantics.
InterlockedCompareExchangeAcquire
//Performs an atomic compare-and-exchange operation on the specified values. The function compares two specified 64-bit values and exchanges with another 64-bit value based on the outcome of the comparison. The exchange is performed with acquire memory access semantics.
InterlockedCompareExchangeAcquire64
//Performs an atomic compare-and-exchange operation on the specified pointer values. The function compares two specified pointer values and exchanges with another pointer value based on the outcome of the comparison.
InterlockedCompareExchangePointer
//Performs an atomic compare-and-exchange operation on the specified pointer values. The function compares two specified pointer values and exchanges with another pointer value based on the outcome of the comparison. The operation is performed with acquire memory access semantics.
InterlockedCompareExchangePointerAcquire
//Performs an atomic compare-and-exchange operation on the specified pointer values. The function compares two specified pointer values and exchanges with another pointer value based on the outcome of the comparison. The operation is performed with release memory access semantics.
InterlockedCompareExchangePointerRelease
//Performs an atomic compare-and-exchange operation on the specified values. The function compares two specified 32-bit values and exchanges with another 32-bit value based on the outcome of the comparison. The exchange is performed with release memory access semantics.
InterlockedCompareExchangeRelease
//Performs an atomic compare-and-exchange operation on the specified values. The function compares two specified 64-bit values and exchanges with another 64-bit value based on the outcome of the comparison. The exchange is performed with release memory access semantics.
InterlockedCompareExchangeRelease64
//Decrements (decreases by one) the value of the specified 32-bit variable as an atomic operation.
InterlockedDecrement
//Decrements (decreases by one) the value of the specified 64-bit variable as an atomic operation.
InterlockedDecrement64
//Decrements (decreases by one) the value of the specified 32-bit variable as an atomic operation. The operation is performed with acquire memory access semantics.
InterlockedDecrementAcquire
//Decrements (decreases by one) the value of the specified 64-bit variable as an atomic operation. The operation is performed with acquire memory access semantics.
InterlockedDecrementAcquire64
//Decrements (decreases by one) the value of the specified 32-bit variable as an atomic operation. The operation is performed with release memory access semantics.
InterlockedDecrementRelease
//Decrements (decreases by one) the value of the specified 64-bit variable as an atomic operation. The operation is performed with release memory access semantics.
InterlockedDecrementRelease64
//Sets a 32-bit variable to the specified value as an atomic operation.
InterlockedExchange
//Sets a 64-bit variable to the specified value as an atomic operation.
InterlockedExchange64
//Sets a 32-bit variable to the specified value as an atomic operation. The operation is performed with acquire memory access semantics.
InterlockedExchangeAcquire
//Sets a 32-bit variable to the specified value as an atomic operation. The operation is performed with acquire memory access semantics.
InterlockedExchangeAcquire64
//Performs an atomic addition of two 32-bit values.
InterlockedExchangeAdd
//Performs an atomic addition of two 64-bit values.
InterlockedExchangeAdd64
//Performs an atomic addition of two 32-bit values. The operation is performed with acquire memory access semantics.
InterlockedExchangeAddAcquire
//Performs an atomic addition of two 64-bit values. The operation is performed with acquire memory access semantics.
InterlockedExchangeAddAcquire64
//Performs an atomic addition of two 32-bit values. The operation is performed with release memory access semantics.
InterlockedExchangeAddRelease
//Performs an atomic addition of two 64-bit values. The operation is performed with release memory access semantics.
InterlockedExchangeAddRelease64
//Atomically exchanges a pair of pointer values.
InterlockedExchangePointer
//Atomically exchanges a pair of pointer values. The operation is performed with acquire memory access semantics.
InterlockedExchangePointerAcquire
//Increments (increases by one) the value of the specified 32-bit variable as an atomic operation.
InterlockedIncrement
//Increments (increases by one) the value of the specified 64-bit variable as an atomic operation.
InterlockedIncrement64
//Increments (increases by one) the value of the specified 32-bit variable as an atomic operation. The operation is performed using acquire memory access semantics.
InterlockedIncrementAcquire
//Increments (increases by one) the value of the specified 64-bit variable as an atomic operation. The operation is performed using acquire memory access semantics.
InterlockedIncrementAcquire64
//Increments (increases by one) the value of the specified 32-bit variable as an atomic operation. The operation is performed using release memory access semantics.
InterlockedIncrementRelease
//Increments (increases by one) the value of the specified 64-bit variable as an atomic operation. The operation is performed using release memory access semantics.
InterlockedIncrementRelease64
//Performs an atomic OR operation on the specified LONG values.
InterlockedOr
//Performs an atomic OR operation on the specified LONG values. The operation is performed with acquire memory access semantics.
InterlockedOrAcquire
//Performs an atomic OR operation on the specified LONG values. The operation is performed with release memory access semantics.
InterlockedOrRelease
//Performs an atomic OR operation on the specified char values.
InterlockedOr8
//Performs an atomic OR operation on the specified char values. The operation is performed with acquire memory access semantics.
InterlockedOr8Acquire
//Performs an atomic OR operation on the specified char values. The operation is performed with release memory access semantics.
InterlockedOr8Release
//Performs an atomic OR operation on the specified SHORT values.
InterlockedOr16
//Performs an atomic OR operation on the specified SHORT values. The operation is performed with acquire memory access semantics.
InterlockedOr16Acquire
//Performs an atomic OR operation on the specified SHORT values. The operation is performed with release memory access semantics.
InterlockedOr16Release
//Performs an atomic OR operation on the specified LONGLONG values.
InterlockedOr64
//Performs an atomic OR operation on the specified LONGLONG values. The operation is performed with acquire memory access semantics.
InterlockedOr64Acquire
//Performs an atomic OR operation on the specified LONGLONG values. The operation is performed with release memory access semantics.
InterlockedOr64Release
//Performs an atomic XOR operation on the specified LONG values.
InterlockedXor
//Performs an atomic XOR operation on the specified LONG values. The operation is performed with acquire memory access semantics.
InterlockedXorAcquire
//Performs an atomic XOR operation on the specified LONG values. The operation is performed with release memory access semantics.
InterlockedXorRelease
//Performs an atomic XOR operation on the specified char values.
InterlockedXor8
//Performs an atomic XOR operation on the specified char values. The operation is performed with acquire memory access semantics.
InterlockedXor8Acquire
//Performs an atomic XOR operation on the specified char values. The operation is performed with release memory access semantics.
InterlockedXor8Release
//Performs an atomic XOR operation on the specified SHORT values.
InterlockedXor16
//Performs an atomic XOR operation on the specified SHORT values. The operation is performed with acquire memory access semantics.
InterlockedXor16Acquire
//Performs an atomic XOR operation on the specified SHORT values. The operation is performed with release memory access semantics.
InterlockedXor16Release
//Performs an atomic XOR operation on the specified LONGLONG values.
InterlockedXor64
//Performs an atomic XOR operation on the specified LONGLONG values. The operation is performed with acquire memory access semantics.
InterlockedXor64Acquire
//Performs an atomic XOR operation on the specified LONGLONG values. The operation is performed with release memory access semantics.
InterlockedXor64Release
*/
