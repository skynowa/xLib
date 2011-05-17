/****************************************************************************
* Class name:  CxDebugger
* Description: debugger
* File name:   CxDebugger.inl
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     17.05.20011
*
*****************************************************************************/


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: vStdVectorPrintT (printing std::vector to std::out)
template<class T>
/*static*/
VOID
CxDebugger::vStdVectorPrintT(
    const std::vector<T> &cvecT
)
{
    tcout << tendl;
    tcout << xT("std::vector (") << cvecT.size() << (" elements):") << tendl;
    tcout << tendl;

    typename std::vector<T>::const_iterator it;
    size_t                                  i = 0;
    for (it = cvecT.begin(), i = 0; it != cvecT.end(); ++ it, ++ i) {
        tcout << xT("Value[") << i << xT("]: ") << (*it) << tendl;
    }

    tcout << tendl;
    tcout << tendl;
}
//---------------------------------------------------------------------------
//DONE: vStdMultiMapPrintT (printing std::map to std::out)
template<class T1, class T2>
/*static*/
VOID
CxDebugger::vStdMapPrintT(
    const std::map<T1, T2> &cmapT
)
{
    tcout << tendl;
    tcout << xT("std::map (") << cmapT.size() << (" elements):") << tendl;
    tcout << tendl;

    typename std::map<T1, T2>::const_iterator it;
    for (it = cmapT.begin(); it != cmapT.end(); ++ it) {
        tcout << xT("Key: ")   << (*it).first  << xT("\t\t")
              << xT("Value: ") << (*it).second << tendl;
    }

    tcout << tendl;
    tcout << tendl;
}
//---------------------------------------------------------------------------
//DONE: vStdMultiMapPrintT (printing std::multimap to std::out)
template<class T1, class T2>
/*static*/
VOID
CxDebugger::vStdMultiMapPrintT(
    const std::multimap<T1, T2> &cmmapT
)
{
    tcout << tendl;
    tcout << xT("std::multimap (") << cmmapT.size() << (" elements):") << tendl;
    tcout << tendl;

    typename std::multimap<T1, T2>::const_iterator it;
    for (it = cmmapT.begin(); it != cmmapT.end(); ++ it) {
        tcout << xT("Key: ")   << (*it).first  << xT("\t\t")
              << xT("Value: ") << (*it).second << tendl;
    }

    tcout << tendl;
    tcout << tendl;
}
//---------------------------------------------------------------------------
