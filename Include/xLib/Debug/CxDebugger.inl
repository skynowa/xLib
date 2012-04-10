/**
 * \file  CxDebugger.h
 * \brief debugger
 */


xNAMESPACE_BEGIN(NxLib)

//---------------------------------------------------------------------------
template<class T>
CxDebugger &
operator << (
    CxDebugger &dbgDebugger,
    const T    &cMessageT
)
{
    dbgDebugger._m_ossTracer << cMessageT;

    return dbgDebugger;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
