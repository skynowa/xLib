/**
 * \file  CxEnvironment.h
 * \brief system environment variables
 */


#pragma once

#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxEnvironment :
    private CxNonCopyable
    /// system environment variables
{
public:
    static bool_t         isExists     (std::ctstring_t &csVarName) xWARN_UNUSED_RV;
        ///< check for existence
    static bool_t         isVarValid   (std::ctstring_t &csVarName) xWARN_UNUSED_RV;
        ///< is valid environment variable name
    static bool_t         isValueValid (std::ctstring_t &csVarValue) xWARN_UNUSED_RV;
        ///< is valid environment variable value
    static std::tstring_t var          (std::ctstring_t &csVarName) xWARN_UNUSED_RV;
        ///< get value by name
    static void_t         setVar       (std::ctstring_t &csVarName, std::ctstring_t &csValue);
        ///< set or change value by name
    static void_t         deleteVar    (std::ctstring_t &csVarName);
        ///< delete var
    static void_t         values       (std::vec_tstring_t *pvsValues);
        ///< get all values
    static std::tstring_t expandStrings(std::ctstring_t &csvVar) xWARN_UNUSED_RV;
        ///< expands strings by separator "%"

private:
                          CxEnvironment();
        ///< constructor
    virtual              ~CxEnvironment();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
