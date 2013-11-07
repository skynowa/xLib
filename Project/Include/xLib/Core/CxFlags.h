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
    public CxNonCopyable
    /// bit mask flags
{
public:
              CxFlags();
        ///< constructor
    explicit  CxFlags(const CxFlags &values);
        ///< constructor
    explicit  CxFlags(const T &values);
        ///< constructor
    virtual  ~CxFlags();
        ///< destructor

    CxFlags & operator = (const CxFlags &values);
        ///< operator =

    size_t  & get() const;
        ///< get all flags
    void_t    set(const T &values);
        ///< set all flags
    void_t    clear();
        ///< reset all flags

    bool_t    isSetFlag(const T &value) const;
        ///< flag is set
    bool_t    isSetAnyFlag(const T &value) const;
        ///< is any flag set
    void_t    setFlag(const T &value);
        ///< set flag
    void_t    unsetFlag(const T &value);
        ///< unset flag
    void_t    toggleFlag(const T &value);
        ///< toggle flag

private:
    size_t    _flags;
};

xNAMESPACE_END(NxLib)
//------------------------------------------------------------------------------
#include <xLib/Core/CxFlags.inl>
