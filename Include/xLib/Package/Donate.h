/**
 * \file   Donate.h
 * \brief  Donate money
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
namespace xl::package
{

struct DonateData
    /// SourceInfo data
{
    std::tstring_t payPal;
    std::tstring_t webMoney;
    std::tstring_t yandexMoney;
    std::tstring_t private24;
};
xUSING_CONST(DonateData);

class Donate
    /// Donate money
{
public:
///@name ctors, dtor
///@{
			  Donate() = default;
	explicit  Donate(cDonateData &data);
	virtual  ~Donate() = default;

    // TODO: xNO_COPY_ASSIGN(Donate)
///@}

    xPROPERTY(DonateData, data, Data);
};

} // namespace
//-------------------------------------------------------------------------------------------------
