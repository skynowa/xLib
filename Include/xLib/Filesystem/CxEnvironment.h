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
    public CxNonCopyable
    /// system environment variables
{
    public:
        static BOOL         bIsExists     (const std::string_t &csVarName);
            ///< check for existence
        static std::string_t sGetVar       (const std::string_t &csVarName);
            ///< get value by name
        static BOOL         bSetVar       (const std::string_t &csVarName, const std::string_t &csValue);
            ///< set or change value by name
        static BOOL         bDeleteVar    (const std::string_t &csVarName);
            ///< delete var
        static BOOL         bGetValues    (std::vector<std::string_t> *pvsValues);
            ///< get all values
        static std::string_t sExpandStrings(const std::string_t &csvVar);
            ///< expands strings by separator "%"

    private:
                            CxEnvironment ();
            ///< constructor
        virtual            ~CxEnvironment ();
            ///< destructor
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Filesystem_CxEnvironmentH

//_MAX_ENV
