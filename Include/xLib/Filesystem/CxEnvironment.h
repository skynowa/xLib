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
        static bool         bIsExists     (const std::tstring &csVarName);
            ///< check for existence
        static std::tstring sGetVar       (const std::tstring &csVarName);
            ///< get value by name
        static bool         bSetVar       (const std::tstring &csVarName, const std::tstring &csValue);
            ///< set or change value by name
        static bool         bDeleteVar    (const std::tstring &csVarName);
            ///< delete var
        static bool         bGetValues    (std::vector<std::tstring> *pvsValues);
            ///< get all values
        static std::tstring sExpandStrings(const std::tstring &csvVar);
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
