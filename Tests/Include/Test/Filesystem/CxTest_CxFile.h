/**
 * \file   CxTest_CxFile.h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
#include <xLib/Test/CxTest.h>
#include <xLib/Filesystem/CxFile.h>
//------------------------------------------------------------------------------
class CxTest_CxFile :
    public CxTest
{
public:
                    CxTest_CxFile() {}

    virtual  void_t unit(culonglong_t &cullCaseLoops);

private:
    void_t          vUnit1(culonglong_t &cullCaseLoops);
    void_t          vUnitPrivate(culonglong_t &cullCaseLoops);
};
//------------------------------------------------------------------------------
