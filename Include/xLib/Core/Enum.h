/**
 * \file   Enum.h
 * \brief  Enumeration
 */


#pragma once

#include <xLib/Core/Core.h>
//-------------------------------------------------------------------------------------------------
xNAMESPACE_BEGIN2(xl, core)

class Enum
    ///< Enumeration
{
public:
             Enum();
        ///< constructor
    virtual ~Enum();
        ///< destructor

    std::tstring_t toString();
    void_t         print();
    bool_t         isValid();

    // operators
    // iterators

private:
    xNO_COPY_ASSIGN(Enum)
};

xNAMESPACE_END2(xl, core)
//-------------------------------------------------------------------------------------------------
#if cmOPTION_PROJECT_HEADER_ONLY
    #include "Enum.cpp"
#endif
