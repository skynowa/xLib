/**
 * \file   CxFinder.h
 * \brief
 */


#ifndef xLib_Filesystem_CxFinderH
#define xLib_Filesystem_CxFinderH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>

#include <xLib/Filesystem/CxFileAttribute.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxFinder :
    public CxNonCopyable
    ///< file system finder
{
    public:
        explicit                     CxFinder    (const std::tstring_t &a_csRootDirPath);
            ///< constructor
        virtual                     ~CxFinder    ();
            ///< destructor

        std::tstring_t               sRootDirPath();
        std::tstring_t               sFileName   ();
        CxFileAttribute::ExAttribute faAttributes();

        bool                         bFirst      ();
        bool                         bNext       ();
        void                         vClose      ();

    private:
        struct _SEntry {
            #if   xOS_ENV_WIN
                HANDLE           hHandle;
                WIN32_FIND_DATA  fdData;
            #elif xOS_ENV_UNIX
                DIR             *pHandle;
                dirent          *pdrData;
            #endif    
        };

        typedef _SEntry _entry_t;
            ///< entry

        _entry_t                     _m_enEnrty;
        std::tstring_t               _m_sRootDirPath;

};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Filesystem_CxFinderH
