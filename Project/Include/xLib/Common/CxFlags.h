/**
 * \file  CxFlags.h
 * \brief bit mask flags
 */


#ifndef xLib_Common_CxFlagsH
#define xLib_Common_CxFlagsH
//------------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxFlags :
    private CxNonCopyable
    /// bit mask flags
{
public:
    typedef ulong_t mask_t; ///< mask type

              CxFlags    ();
        ///< constructor
    explicit  CxFlags    (const CxFlags &cfFlags);
        ///< constructor
    explicit  CxFlags    (cint_t &ciFlag);
        ///< constructor
    explicit  CxFlags    (const mask_t &cmFlag);
        ///< constructor
    virtual  ~CxFlags    ();
        ///< destructor

    bool_t    isSet      (cint_t &ciFlag) const;
        ///<
    bool_t    isSet      (const mask_t &cmFlag) const;
        ///<
    bool_t    isAnySet   (const mask_t &cmFlag) const;
        ///<
    bool_t    isAnySet   (cint_t &ciFlag) const;
        ///<
    void_t    setFlag    (const mask_t &cmFlag);
        ///<
    void_t    setFlag    (cint_t &ciFlag);
        ///<
    void_t    unsetFlag  (const mask_t &cmFlag);
        ///<
    void_t    unsetFlag  (cint_t &ciFlag);
        ///<
    void_t    setFlags   (const mask_t &cmFlag);
        ///<
    mask_t    getFlags   () const;
        ///<
    CxFlags & operator = (const CxFlags &cfFlags);

private:
    mask_t    _m_mFlags;
};

xNAMESPACE_END(NxLib)
//-------------------------------------------------------------------------
#endif // xLib_Common_CxFlagsH
