/**
 * \file   xFunctions_bsd.inl
 * \brief  function macroses
 */


xNAMESPACE_BEGIN2(xlib, core)

//-------------------------------------------------------------------------------------------------
#define F_LOCK  LOCK_EX
#define F_TEST  LOCK_EX // TODO: lockf() - F_TEST - n/a
#define F_ULOCK LOCK_UN

inline int
lockf(
    int   fd,
    int   cmd,
    off_t len_unused
)
{
    xUNUSED(len_unused);

    return ::flock(fd, cmd);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, core)

