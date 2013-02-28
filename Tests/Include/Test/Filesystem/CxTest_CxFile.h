/**
 * \file   CxTest_CxFile.h
 * \brief
 */


#ifndef CxTest_CxFileH
#define CxTest_CxFileH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxFile.h>
//------------------------------------------------------------------------------
class CxTest_CxFile :
    public CxTest
{
public:
                   CxTest_CxFile();
    virtual       ~CxTest_CxFile();

    virtual  void  unit        (culonglong_t &cullCaseLoops);

private:
    void           vUnit1       (culonglong_t &cullCaseLoops);
    void           vUnitPrivate (culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
#endif //CxTest_CxFileH
