/**
 * \file   Guid.h
 * \brief  GUID (globally unique identifier)
 */


#pragma once

#include <xLib/Core/Core.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, crypt)

class Guid
    /// GUID (globally unique identifier)
{
public:
    enum class Type
    {
        Unknown     = 0,
        RandomBased = 1
    };
    xUSING_CONST(Type);

///@name ctors, dtor
///@{
			 Guid(cType type);
	virtual ~Guid() = default;

	xNO_COPY_ASSIGN(Guid)
///@}

	std::tstring_t get() const;
		///< generate GUID

private:
	cType _type;

xPLATFORM_IMPL:
    std::tstring_t _randomBased_impl() const;
        ///< random based GUID
};

xNAMESPACE_END2(xl, crypt)
//---------------------------------------------------------------------------
