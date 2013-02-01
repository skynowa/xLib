/**
 * \file   CxTest_CxCrc32.h
 * \brief
 */


#ifndef CxTest_CxCrc32H
#define CxTest_CxCrc32H
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Crypt/CxCrc32.h>
#include <xLib/Filesystem/CxFile.h>
//---------------------------------------------------------------------------
class CxTest_CxCrc32 :
    public CxTest
{
public:
                 CxTest_CxCrc32();
    virtual     ~CxTest_CxCrc32();

    virtual void unit(const ulonglong_t &cullCaseLoops);
};
//---------------------------------------------------------------------------
#endif //CxTest_CxCrc32H
