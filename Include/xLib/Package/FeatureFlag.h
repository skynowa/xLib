/**
 * \file  FeatureFlag.h
 * \brief Feature flag / toggle
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/DateTime.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, package)

class FeatureFlag
    /// Feature flag / toggle
{
public:
             FeatureFlag() = default;
    virtual ~FeatureFlag() = default;

	xPROPERTY(std::tstring_t, name, Name);
	xPROPERTY(std::tstring_t, description, Description);
	xPROPERTY(bool_t,         enable, Enable);

public:
    void setIntervalTs(const DateTime &start, const DateTime &stop);
        ///<
    void setStop(const DateTime &stop);
        ///<
    void setPermissions();
        ///<
    void alert() const;
        ///<

private:
	DateTime _start; ///<
	DateTime _stop;  ///<

    xNO_COPY_ASSIGN(FeatureFlag)
};

xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------
