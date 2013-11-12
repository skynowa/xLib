/**
 * \file  CxExecInfo.h
 * \brief
 */


#pragma once

#ifndef xLib_CxExecInfoH
#define xLib_CxExecInfoH
//-------------------------------------------------------------------------------------------------
inline int
backtrace(void **buffer, int size)
{
    (void)buffer;
    (void)size;

    return 0;
}
//-------------------------------------------------------------------------------------------------
inline char **
backtrace_symbols(void *const *buffer, int size)
{
    (void)buffer;
    (void)size;

    return NULL;
}
//-------------------------------------------------------------------------------------------------
inline void
backtrace_symbols_fd(void *const *buffer, int size, int fd)
{
    (void)buffer;
    (void)size;
    (void)fd;
}
//-------------------------------------------------------------------------------------------------
#endif // xLib_CxExecInfoH
