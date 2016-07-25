/**
 * \file   Donate.h
 * \brief  Donate money
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xlib, package)

struct DonateData
    /// SourceInfo data
{
    std::tstring_t payPal;
    std::tstring_t webMoney;
    std::tstring_t yandexMoney;
    std::tstring_t private24;
};
xTYPEDEF_CONST(DonateData);

class Donate
    ///< Donate money
{
public:
    explicit     Donate(cDonateData &data);
        ///< constructor
    virtual     ~Donate();
        ///< destructor

	xPROPERTY(DonateData, data);

private:
    xNO_COPY_ASSIGN(Donate)
};

xNAMESPACE_END2(xlib, package)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "Donate.cpp"
#endif
