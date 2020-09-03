/**
 * \file  DirTemp.h
 * \brief DirTemp
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, fs)

class DirTemp
    /// DirTemp
{
public:
             DirTemp();
        ///< constructor
    virtual ~DirTemp();
        ///< destructor

private:
    xNO_COPY_ASSIGN(DirTemp)

xPLATFORM_IMPL:
    void_t _construct_impl();
    void_t _destruct_impl();
};

xNAMESPACE_END2(xl, fs)
//-------------------------------------------------------------------------------------------------
