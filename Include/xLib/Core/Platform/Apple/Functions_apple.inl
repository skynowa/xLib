/**
 * \file   Functions_apple.inl
 * \brief  function macroses
 */


/**************************************************************************************************
* TODO: [Apple] Sem API
*
* https://stackoverflow.com/questions/641126/posix-semaphores-on-mac-os-x-sem-timedwait-alternative
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
typedef struct
{
	pthread_mutex_t count_lock;
	pthread_cond_t  count_bump;
	unsigned count;
}
bosal_sem_t;
//-------------------------------------------------------------------------------------------------
int sem_init(sem_t *psem, int flags, unsigned count)
{
#if 0
	bosal_sem_t *pnewsem {};
	int result;

	pnewsem = (bosal_sem_t *)malloc(sizeof(bosal_sem_t));
	if (! pnewsem)
	{
		return -1;
	}
	result = pthread_mutex_init(&pnewsem->count_lock, NULL);
	if (result)
	{
		free(pnewsem);
		return result;
	}
	result = pthread_cond_init(&pnewsem->count_bump, NULL);
	if (result)
	{
		pthread_mutex_destroy(&pnewsem->count_lock);
		free(pnewsem);
		return result;
	}
	pnewsem->count = count;
	*psem = static_cast<sem_t>(pnewsem);
#endif

	return 0;
}
//-------------------------------------------------------------------------------------------------
int sem_destroy(sem_t *psem)
{
#if 0
	bosal_sem_t *poldsem {};

	if (! psem)
	{
		return EINVAL;
	}
	poldsem = (bosal_sem_t *)*psem;

	pthread_mutex_destroy(&poldsem->count_lock);
	pthread_cond_destroy(&poldsem->count_bump);
	free(poldsem);
#endif

	return 0;
}
//-------------------------------------------------------------------------------------------------
int sem_post(sem_t *psem)
{
#if 0
	bosal_sem_t *pxsem {};
	int result, xresult;

	if (! psem)
	{
	   return EINVAL;
	}
	pxsem = (bosal_sem_t *)*psem;

	result = pthread_mutex_lock(&pxsem->count_lock);
	if (result)
	{
	   return result;
	}
	pxsem->count = pxsem->count + 1;

	xresult = pthread_cond_signal(&pxsem->count_bump);

	result = pthread_mutex_unlock(&pxsem->count_lock);
	if (result)
	{
	   return result;
	}
	if (xresult)
	{
	   errno = xresult;
	   return -1;
	}
#endif

	return 0;
}
//-------------------------------------------------------------------------------------------------
int sem_trywait(sem_t *psem)
{
#if 0
	bosal_sem_t *pxsem {};
	int result, xresult;

	if (! psem)
	{
		return EINVAL;
	}
	pxsem = (bosal_sem_t *)*psem;

	result = pthread_mutex_lock(&pxsem->count_lock);
	if (result)
	{
		return result;
	}
	xresult = 0;

	if (pxsem->count > 0)
	{
		pxsem->count--;
	}
	else
	{
		xresult = EAGAIN;
	}
	result = pthread_mutex_unlock(&pxsem->count_lock);
	if (result)
	{
		return result;
	}
	if (xresult)
	{
		errno = xresult;
		return -1;
	}
#endif

	return 0;
}
//-------------------------------------------------------------------------------------------------
int sem_wait(sem_t *psem)
{
#if 0
	bosal_sem_t *pxsem {};
	int result, xresult;

	if (! psem)
	{
		return EINVAL;
	}
	pxsem = (bosal_sem_t *)*psem;

	result = pthread_mutex_lock(&pxsem->count_lock);
	if (result)
	{
		return result;
	}
	xresult = 0;

	if (pxsem->count == 0)
	{
		xresult = pthread_cond_wait(&pxsem->count_bump, &pxsem->count_lock);
	}
	if (! xresult)
	{
		if (pxsem->count > 0)
		{
			pxsem->count--;
		}
	}
	result = pthread_mutex_unlock(&pxsem->count_lock);
	if (result)
	{
		return result;
	}
	if (xresult)
	{
		errno = xresult;
		return -1;
	}
#endif

	return 0;
}
//-------------------------------------------------------------------------------------------------
int sem_timedwait(sem_t *psem, const struct timespec *abstim)
{
#if 0
	bosal_sem_t *pxsem {};
	int result, xresult;

	if (! psem)
	{
		return EINVAL;
	}
	pxsem = (bosal_sem_t *)*psem;

	result = pthread_mutex_lock(&pxsem->count_lock);
	if (result)
	{
		return result;
	}
	xresult = 0;

	if (pxsem->count == 0)
	{
		xresult = pthread_cond_timedwait(&pxsem->count_bump, &pxsem->count_lock, abstim);
	}
	if (! xresult)
	{
		if (pxsem->count > 0)
		{
			pxsem->count--;
		}
	}
	result = pthread_mutex_unlock(&pxsem->count_lock);
	if (result)
	{
		return result;
	}
	if (xresult)
	{
		errno = xresult;
		return -1;
	}
#endif

	return 0;
}
//-------------------------------------------------------------------------------------------------
