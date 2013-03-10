/**
 * \file   CxTest_CxFileType.h
 * \brief
 */


#ifndef CxTest_CxFileTypeH
#define CxTest_CxFileTypeH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxFileType.h>
//------------------------------------------------------------------------------
class CxTest_CxFileType :
    public CxTest
{
public:
                     CxTest_CxFileType();
    virtual         ~CxTest_CxFileType();

    virtual  void_t  unit(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxFileTypeH
