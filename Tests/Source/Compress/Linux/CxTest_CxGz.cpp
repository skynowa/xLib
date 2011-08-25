/****************************************************************************
* Class name:  CxTest_CxGz
* Description: test CxGz
* File name:   CxTest_CxGz.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#include <Test/Compress/Linux/CxTest_CxGz.h>


//---------------------------------------------------------------------------
//DONE: CxTest_CxGz
CxTest_CxGz::CxTest_CxGz() {

}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxGz
CxTest_CxGz::~CxTest_CxGz() {

}
//---------------------------------------------------------------------------
//DONE: bUnit ()
/*virtual*/
BOOL
CxTest_CxGz::bUnit(
    const ULONGLONG cullBlockLoops
)
{
    CxGz gzGz;

    #if xTODO
        INT   iFileIn,
        INT   iFileOut,
        const std::tstring csOriginName = xT("OriginName");

        m_bRes = gzGz.bCompress(INT iFileIn, INT iFileOut, const std::tstring &csOriginName);
        xASSERT_NOT_EQ(FALSE, m_bRes);

        m_bRes = gzGz.bUncompress(INT iFileIn, INT iFileOut);
        xASSERT_NOT_EQ(FALSE, m_bRes);
    #endif

    return TRUE;
}
//---------------------------------------------------------------------------
