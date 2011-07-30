/****************************************************************************
* Class name:  CxType
* Description: type info
* File name:   CxType.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     29.07.2011
*
*****************************************************************************/


#ifndef xLib_Common_CxTypeH
#define xLib_Common_CxTypeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxType : 
    public CxNonCopyable 
{
	public:
        template<class T>
        static tString  sGetName   (const T &cObjectT);

        template<class T>
        static tString  sGetRawName(const T &cObjectT);

        template<class T1, class T2>
        static BOOL 	bIsEquals  (const T1 &cObjectT1, const T2 &cObjectT2);
        
    private:
    				    CxType     ();
		virtual        ~CxType     ();
};
//---------------------------------------------------------------------------
#include <Common/CxType.inl>
//---------------------------------------------------------------------------
#endif //xLib_Common_CxTypeH
