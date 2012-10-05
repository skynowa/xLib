/**
 * \file   CxTest_CxFileAttribute.h
 * \brief
 */


#ifndef CxTest_CxFileAttributeH
#define CxTest_CxFileAttributeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxFileAttribute.h>
//---------------------------------------------------------------------------
class CxTest_CxFileAttribute :
    public CxTest
{
    public:
                       CxTest_CxFileAttribute();
        virtual       ~CxTest_CxFileAttribute();

        virtual  void  vUnit(const ulonglong_t &cullCaseLoops);

    private:
};
//---------------------------------------------------------------------------
#endif //CxTest_CxFileAttributeH
