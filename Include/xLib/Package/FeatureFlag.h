/**
 * \file  FeatureFlag.h
 * \brief Feature flag / toggle
 */


#pragma once

#include <xLib/Core/Core.h>
#include <xLib/Core/DateTime.h>
//-------------------------------------------------------------------------------------------------
namespace xl::package
{

class FeatureFlag
    /// Feature flag / toggle
{
public:
///@name ctors, dtor
///@{
			 FeatureFlag() = default;
	virtual ~FeatureFlag() = default;

	xNO_COPY_ASSIGN(FeatureFlag)
///@}

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
};

} // namespace
//-------------------------------------------------------------------------------------------------
