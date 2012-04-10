/**
 * \file  CxDebugger.h
 * \brief debugger
 */


#include <xLib/Common/CxString.h>


xNAMESPACE_BEGIN(NxLib)

//---------------------------------------------------------------------------
template<class T>
CxDebugger &
operator << (
    CxDebugger &dbgDebugger,
    const T    &cMessage
)
{
    dbgDebugger._m_ossTracer << CxString::lexical_cast(cMessage);

    return dbgDebugger;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
