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
    ///< Feature flag / toggle
{
public:
             FeatureFlag();
        ///< constructor
    virtual ~FeatureFlag();
        ///< destructor

    void     setName(std::ctstring_t &name);
    void     setDescription(std::ctstring_t &desc);
    bool_t   isEnable() const;
    void     setEnable(cbool_t enable);
    void     setIntervalTs(const DateTime &start, const DateTime &stop);
    void     setStop(const DateTime &stop);
    void     setPermissions();
    void     alert();

private:
    std::tstring_t _name;
    std::tstring_t _desc;
    bool_t         _is_enable {};
	DateTime       _start;
	DateTime       _stop;

    xNO_COPY_ASSIGN(FeatureFlag)
};

xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------
