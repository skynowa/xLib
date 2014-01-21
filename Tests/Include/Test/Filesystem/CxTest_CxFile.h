/**
 * \file   CxTest_CxFile.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxFile.h>
//-------------------------------------------------------------------------------------------------
class CxTest_CxFile :
    public CxTest
{
public:
                    CxTest_CxFile() {}

    virtual  void_t unit(culonglong_t &caseLoops);

private:
    void_t          unit1(culonglong_t &caseLoops);
    void_t          unitPrivate(culonglong_t &caseLoops);
};
//-------------------------------------------------------------------------------------------------
