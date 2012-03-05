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
        static bool           bIsValidVar   (const std::tstring_t &csVarName);
            ///< is valid environment variable name
        static bool           bIsValidValue (const std::tstring_t &csVarValue);
            ///< is valid environment variable value
        static std::tstring_t sGetVar       (const std::tstring_t &csVarName);
            ///< get value by name
        static bool           bSetVar       (const std::tstring_t &csVarName, const std::tstring_t &csValue);
            ///< set or change value by name
        static bool           bDeleteVar    (const std::tstring_t &csVarName);
            ///< delete var
        static bool           bGetValues    (std::vector<std::tstring_t> *pvsValues);
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
#endif //xLib_Filesystem_CxEnvironmentH

//_MAX_ENV
