/****************************************************************************
* Class name:  CxResources
* Description: 
* File name:   CxResources.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     07.09.2009 9:44:20
*
*****************************************************************************/


#ifndef XLib_Gui_CxResourcesH
#define XLib_Gui_CxResourcesH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Gui/Win/xCommon.h>
#include <xLib/Common/CxNonCopyable.h>
//---------------------------------------------------------------------------
class CxResources : public CxNonCopyable {
    public:
        static BOOL    bInit       ();
        static tString sGetText    (INT iID);
        static INT     iGetLeft       (INT iID);
        static INT     iGetTop     (INT iID);
        static INT     iGetWidth   (INT iID);
        static INT     iGetHeight  (INT iID);
        static ULONG   ulGetStyle  (INT iID);
        static ULONG   ulGetStyleEx(INT iID);

    private:
        //-------------------------------------
        //����� �������� ���������    
        class CXSettings {
            public:
                        CXSettings   () :
                                        _m_sText    (),             
                                        _m_iLeft    (0), 
                                        _m_iTop     (0), 
                                        _m_iWidth   (0), 
                                        _m_iHeight  (0),               
                                        _m_ulStyle  (0),               
                                        _m_ulStyleEx(0)           {}
                        CXSettings   (const tString &csText, INT iLeft, INT iTop, INT iWidth, INT iHeight, ULONG ulStyle, ULONG ulStyleEx) :
                                        _m_sText    (csText),             
                                        _m_iLeft    (iLeft), 
                                        _m_iTop     (iTop), 
                                        _m_iWidth   (iWidth), 
                                        _m_iHeight  (iHeight),               
                                        _m_ulStyle  (ulStyle),               
                                        _m_ulStyleEx(ulStyleEx) {}
                       ~CXSettings   ()       {} 

                tString sGetText     () const {return _m_sText;    }
                INT     iGetLeft     () const {return _m_iLeft;    }
                INT     iGetTop      () const {return _m_iTop;     }
                INT     iGetWidth    () const {return _m_iWidth;   }
                INT     iGetHeight   () const {return _m_iHeight;  }
                ULONG   ulGetStyle   () const {return _m_ulStyle;  }
                ULONG   ulGetStyleEx () const {return _m_ulStyleEx;}

            private:
                tString _m_sText;
                INT     _m_iLeft; 
                INT     _m_iTop; 
                INT     _m_iWidth; 
                INT     _m_iHeight;
                ULONG   _m_ulStyle;
                ULONG   _m_ulStyleEx;
        };
        typedef std::map<INT, CXSettings> TSettingsMap;    

        //-------------------------------------
        //
        static TSettingsMap _m_mapResContent;        //����� (ID (Key) + ������ (Value))

                             CxResources   ();
                            ~CxResources   ();
        static BOOL         _bInitControl  (INT iID, const tString &csText, INT iLeft, INT iTop, INT iWidth, INT iHeight, ULONG ulStyle, ULONG ulStyleEx);
        static BOOL         _bRemoveControl(INT iID);
};
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxResourcesH