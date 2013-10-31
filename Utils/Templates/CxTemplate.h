/**
 * \file   [CxTemplate].h
 * \brief
 */


#pragma once

#include <xLib/Core/xCore.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class [CxTemplate] :
    public CxNonCopyable
    ///< ??????????
{
    public:
                 [CxTemplate]() {}
            ///< constructor
        virtual ~[CxTemplate]() {}
            ///< destructor

    private:

};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#if xXLIB_HEADER_ONLY
    #include <xLib/[CxTemplate].h>
#endif
