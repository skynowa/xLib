/**
 * \file   FsWatcher.h
 * \brief  File system watcher
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, io)

class FsWatcher
    ///< File system watcher
{
public:
             FsWatcher();
        ///< constructor
    virtual ~FsWatcher();
        ///< destructor

private:
    xNO_COPY_ASSIGN(FsWatcher)

xPLATFORM_IMPL:
    void_t   _construct_impl();
    void_t   _destruct_impl();
};

xNAMESPACE_END2(xl, io)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "FsWatcher.cpp"
#endif
