/**
 * \file  CxFlags.h
 * \brief bit mask flags
 */


#pragma once

#include <xLib/Core/xCore.h>
//------------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

template <class T>
class CxFlags :
    private CxNonCopyable
    /// bit mask flags
{
public:
              CxFlags();
        ///< constructor
    explicit  CxFlags(const CxFlags &cfValues);
        ///< constructor
    explicit  CxFlags(const T &valuesT);
        ///< constructor
    virtual  ~CxFlags();
        ///< destructor

    CxFlags & operator = (const CxFlags &cfValues);
        ///< operator =

    size_t  & get() const;
        ///< get all flags
    void_t    set(const T &valuesT);
        ///< set all flags
    void_t    clear();
        ///< reset all flags

    bool_t    isSetFlag(const T &valueT) const;
        ///< flag is set
    bool_t    isSetAnyFlag(const T &valueT) const;
        ///< is any flag set
    void_t    setFlag(const T &valueT);
        ///< set flag
    void_t    unsetFlag(const T &valueT);
        ///< unset flag
    void_t    toggleFlag(const T &valueT);
        ///< toggle flag

private:
    size_t    _m_mFlags;
};
//------------------------------------------------------------------------------
xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------

#include <xLib/Core/CxFlags.inl>
