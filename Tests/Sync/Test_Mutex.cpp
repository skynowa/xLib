/**
 * \file   Test_Mutex.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_Mutex)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_Mutex::unit()
{
    int_t value {};

    auto worker = [](int *out_value) -> void_t
	{
		++ (* out_value);
	};

    xTEST_CASE("lock, unlock")
    {
        Mutex mutex;
        mutex.create();

        // Lock
		{
			mutex.lock();

			worker(&value);

			mutex.unlock();
		}

        xTEST_EQ(value, 1);
    }

    xTEST_CASE("tryLock, unlock")
    {
        Mutex mutex;
        mutex.create();

        // Lock
		{
			m_bRv = mutex.tryLock();
			xTEST(m_bRv);

			worker(&value);

			mutex.unlock();
		}

        xTEST_EQ(value, 2);
    }

    xTEST_CASE("lock, unlock")
    {
        std::csize_t locksNum = 10;

        Mutex mutex;
        mutex.create();

        // Lock
		{
			for (std::size_t i = 0; i < locksNum; ++ i) {
				mutex.lock();
			}

			worker(&value);

			for (size_t i = 0; i < locksNum; ++ i) {
				mutex.unlock();
			}
		}

        xTEST_EQ(value, 3);
    }

    xTEST_CASE("tryLock, unlock")
    {
        std::csize_t locksNum = 10;

        Mutex mutex;
        mutex.create();

        // Lock
		{
			for (std::size_t i = 0; i < locksNum; ++ i) {
				m_bRv = mutex.tryLock();
				xTEST(m_bRv);
			}

			worker(&value);

			for (size_t i = 0; i < locksNum; ++ i) {
				mutex.unlock();
			}
		}

        xTEST_EQ(value, 4);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
