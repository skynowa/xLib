/**
 * \file  CxEnvironment.h
 * \brief system environment variables
 */


#ifndef xLib_Filesystem_CxEnvironmentH
#define xLib_Filesystem_CxEnvironmentH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxEnvironment :
    private CxNonCopyable
    /// system environment variables
{
public:
    static bool           bIsExists     (const std::tstring_t &csVarName);
        ///< check for existence
    static bool           bIsVarValid   (const std::tstring_t &csVarName);
        ///< is valid environment variable name
    static bool           bIsValueValid (const std::tstring_t &csVarValue);
        ///< is valid environment variable value
    static std::tstring_t sVar          (const std::tstring_t &csVarName);
        ///< get value by name
    static void           vSetVar       (const std::tstring_t &csVarName, const std::tstring_t &csValue);
        ///< set or change value by name
    static void           vDeleteVar    (const std::tstring_t &csVarName);
        ///< delete var
    static void           vValues       (std::vec_tstring_t *pvsValues);
        ///< get all values
    static std::tstring_t sExpandStrings(const std::tstring_t &csvVar);
        ///< expands strings by separator "%"

private:
                          CxEnvironment ();
        ///< constructor
    virtual              ~CxEnvironment ();
        ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Filesystem_CxEnvironmentH
