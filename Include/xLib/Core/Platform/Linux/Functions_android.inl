/**
 * \file   Functions_android.inl
 * \brief  function macroses
 */


//-------------------------------------------------------------------------------------------------
#define F_LOCK  LOCK_EX
#define F_TEST  LOCK_EX // TODO: [skynowa] lockf() - F_TEST - n/a
#define F_ULOCK LOCK_UN

int
lockf(
    int   a_fd,
    int   a_cmd,
    off_t a_len_unused
) /* xWARN_UNUSED_RV */
{
    xUNUSED(a_len_unused);

    return ::flock(a_fd, a_cmd);
}
//-------------------------------------------------------------------------------------------------
