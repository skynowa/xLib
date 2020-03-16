/**
 * \file  FeatureFlag.h
 * \brief Feature flag / toggle
 */


#pragma once

#include <xLib/Core/Core.h>
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
    void     setStartTs(const DateTime &start);
    void     setStopTs(const DateTime &stop);
    void     setStop(const DateTime &dateTime);

    bool_t   isEnable() const;
    void     setEnable(cbool_t flag);

    void     setPermissions();
    void     alert();

private:
    xNO_COPY_ASSIGN(FeatureFlag)
};

xNAMESPACE_END2(xl, package)
//-------------------------------------------------------------------------------------------------
