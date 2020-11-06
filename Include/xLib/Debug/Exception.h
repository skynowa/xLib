/**
 * \file  Exception.h
 * \brief exception
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::debug
{

class Exception
    /// exception
{
public:
///@name ctors, dtor
///@{
			 Exception() = default;
	virtual ~Exception() = default;

	// TODO: xNO_COPY_ASSIGN(Exception);
///@}

///@name operators
///@{
	template<typename T>
	Exception & operator << (const T &msgT);
///@}

    std::ctstring_t & what() const;
        ///< get message

private:
    std::tstring_t _msgT;
        ///< message
};

} // namespace
//-------------------------------------------------------------------------------------------------
#include "Exception.inl"
