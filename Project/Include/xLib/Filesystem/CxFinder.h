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
    explicit                     CxFinder     (const std::tstring_t &csRootDirPath,
                                               const std::tstring_t &csFilterByShell);
        ///< constructor
    virtual                     ~CxFinder     ();
        ///< destructor

    const std::tstring_t &       rootDirPath  () const xWARN_UNUSED_RESULT;
        ///< root directory path
    const std::tstring_t &       filterByShell() const xWARN_UNUSED_RESULT;
        ///< shell wild card filter
    std::tstring_t               entryName    () const xWARN_UNUSED_RESULT;
        ///< entry name
    CxFileAttribute::ExAttribute attributes   () const xWARN_UNUSED_RESULT;
        ///< file attributes

    bool                         isValid      () const xWARN_UNUSED_RESULT;
        ///< is valid handle
    bool                         moveFirst    () xWARN_UNUSED_RESULT;
        ///< move first entry
    bool                         moveNext     () xWARN_UNUSED_RESULT;
        ///< move next entry
    void                         close        ();
        ///< close search

private:
    struct _SEntry {
    #if   xOS_ENV_WIN
        HANDLE           hHandle;
        WIN32_FIND_DATA  fdData;

        _SEntry() :
            hHandle(xNATIVE_HANDLE_INVALID),
            fdData ()
        {}
    #elif xOS_ENV_UNIX
        DIR             *pHandle;
        dirent          *pdrData;

        _SEntry() :
            pHandle(NULL),
            pdrData(NULL)
        {}
    #endif
    };

    typedef _SEntry _entry_t;
        ///< entry

    _entry_t                     _m_enEnrty;            ///< entry handle
    const std::tstring_t         _m_csRootDirPath;      ///< root directory path
    const std::tstring_t         _m_csFilterByShell;    ///< shell wild card filter
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif // xLib_Filesystem_CxFinderH
