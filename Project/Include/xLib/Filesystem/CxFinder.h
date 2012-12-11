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
        explicit                     CxFinder    (const std::tstring_t &a_csRootDirPath, const std::tstring_t &csFileFilter);
            ///< constructor
        virtual                     ~CxFinder    ();
            ///< destructor

        const std::tstring_t &       sRootDirPath() const;
            ///< root directory path
        const std::tstring_t &       sFilter     () const;
            ///< shell wildcard pattern
        std::tstring_t               sEntryName  () const;
            ///< entry name
        CxFileAttribute::ExAttribute faAttributes() const;
            ///< file attributes

        bool                         bIsValid    () const;
            ///< is valid handle
        bool                         bMoveFirst  ();
            ///< move first entry
        bool                         bMoveNext   ();
            ///< move next entry
        void                         vClose      ();
            ///< close search

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
        const std::tstring_t         _m_csRootDirPath;
        const std::tstring_t         _m_csFilter;

};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Filesystem_CxFinderH
