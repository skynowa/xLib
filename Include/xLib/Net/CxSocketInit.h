/**
 * \file  CxSocketInit.h
 * \brief initiates use of the Winsock DLL by a process
 */


#ifndef xLib_Net_CxSocketInitH
#define xLib_Net_CxSocketInitH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
#endif //xLib_Net_CxSocketInitH
