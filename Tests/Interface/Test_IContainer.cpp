/**
 * \file   Test_IContainer.cpp
 * \brief  test IContainer
 */


#include <xLib/xLib.h>


//-------------------------------------------------------------------------------------------------
xTEST_UNIT(Test_IContainer)
//-------------------------------------------------------------------------------------------------
constexpr std::size_t buffSize {10};

template<typename T>
class Container :
    public IContainer<T>
{
public:
	using typename IContainer<T>::size_type;
	using typename IContainer<T>::pointer;
	using typename IContainer<T>::iterator;
	using typename IContainer<T>::const_iterator;

    Container() = default;
    ~Container() = default;

	// iterators
	iterator
	begin() override
	{
		return &buff[0];
	}

	const_iterator
	cbegin() const override
	{
		return &buff[0];
	}

	iterator
	end() override
	{
		return &buff[ size() ];
	}

	const_iterator
	cend() const override
	{
		return &buff[ size() ];
	}

	// capacity
	size_type
	size() const override
	{
		return Utils::arraySizeT(buff);
	}

	// element access
	pointer
	data() override
	{
		return &buff[0];
	}

public:
	T buff[::buffSize] {};
};
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_IContainer::unit()
{
    xTEST_CASE("IContainer")
    {
        Container<int_t> cont;
		xTEST_EQ(cont.size(), ::buffSize);
		xTEST(!cont.empty());
		xTEST_PTR(cont.data());

		// init
        {
			auto it = std::find_if_not(cont.cbegin(), cont.cend(), [](int_t i) {return i == 0;});
			xTEST(it == cont.end());

			const std::vector<int_t> v {0,1,2,3,4,5,6,7,8,9};
			xTEST_EQ(v.size(), ::buffSize);

			std::copy(v.cbegin(), v.cend(), cont.begin());
			xTEST_EQ(cont.size(), v.size());
		}

		xTEST_EQ(*cont.cbegin(), 0);
		xTEST_EQ(*(cont.cend() - 1), 9);

		xTEST_EQ(cont.front(), 0);
		xTEST_EQ(cont.back(), 9);

		xTEST_EQ(*cont.data(), 0);

		std::reverse(cont.begin(), cont.end());
		xTEST_EQ(cont.front(), 9);
		xTEST_EQ(cont.back(), 0);
		xTEST_EQ(*cont.data(), 9);
    }

    return true;
}
//-------------------------------------------------------------------------------------------------
