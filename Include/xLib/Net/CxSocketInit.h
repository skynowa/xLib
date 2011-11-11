/**
 * \file  CxSocketInit.h
 * \brief initiates use of the Winsock DLL by a process
 */


#ifndef xLib_Net_CxSocketInitH
#define xLib_Net_CxSocketInitH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxSocketInit :
    public CxNonCopyable
    /// initiates use of the Winsock DLL by a process
{
    public:
                  CxSocketInit(const USHORT cusHighVersion, const USHORT cusLowVersion);
            ///< constructor (init winsock DLL)
        virtual  ~CxSocketInit();
            ///< destructor  (clean winsock DLL)

    private:

};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#endif //xLib_Net_CxSocketInitH
