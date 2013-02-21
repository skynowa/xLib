/**
 * \file  CxEnvironment.h
 * \brief system environment variables
 */


#ifndef xLib_Filesystem_CxEnvironmentH
#define xLib_Filesystem_CxEnvironmentH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxEnvironment :
    private CxNonCopyable
    /// system environment variables
{
public:
    static bool           isExists     (const std::tstring_t &csVarName) xWARN_UNUSED_RESULT;
        ///< check for existence
    static bool           isVarValid   (const std::tstring_t &csVarName) xWARN_UNUSED_RESULT;
        ///< is valid environment variable name
    static bool           isValueValid (const std::tstring_t &csVarValue) xWARN_UNUSED_RESULT;
        ///< is valid environment variable value
    static std::tstring_t var          (const std::tstring_t &csVarName) xWARN_UNUSED_RESULT;
        ///< get value by name
    static void           setVar       (const std::tstring_t &csVarName, const std::tstring_t &csValue);
        ///< set or change value by name
    static void           deleteVar    (const std::tstring_t &csVarName);
        ///< delete var
    static void           values       (std::vec_tstring_t *pvsValues);
        ///< get all values
    static std::tstring_t expandStrings(const std::tstring_t &csvVar) xWARN_UNUSED_RESULT;
        ///< expands strings by separator "%"

private:
                          CxEnvironment();
        ///< constructor
    virtual              ~CxEnvironment();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#endif // xLib_Filesystem_CxEnvironmentH
