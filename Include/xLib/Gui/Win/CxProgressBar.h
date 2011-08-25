/**
 * \file  CxProgressBar.h
 * \brief progress bar
 */


#ifndef XLib_Gui_CxProgressBarH
#define XLib_Gui_CxProgressBarH
//---------------------------------------------------------------------------
#include <xLib/GUI/CxWindow.h>
//---------------------------------------------------------------------------
class CxProgressBar: public CxWindow {
    public:
        //-------------------------------------
        //константы

        //стиль
        enum EViewStyle {
            vsDefault       = 0x00,        //FIX: 0x00
        #if (xWINVER >= xWIN32_S03)
            vsMarquee       = PBS_MARQUEE,
        #endif //xWIN32_S03
            vsSmooth        = PBS_SMOOTH,
        #if (xWINVER >= xWIN32_VISTA)
            vsSmoothReverse = PBS_SMOOTHREVERSE,
        #endif //xWIN32_VISTA
            vsVertical      = PBS_VERTICAL
        };

        //состояние
    #if (xWINVER >= xWIN32_VISTA)
        enum EState {
            stNormal = PBST_NORMAL,    //In progress
            stError  = PBST_ERROR,    //Error
            stPaused = PBST_PAUSED    //Paused
        };
    #endif //xWIN32_VISTA


                 CxProgressBar();
                ~CxProgressBar();

        BOOL     bCreateRes   (INT iID, CxWindow *pwndParent);
        BOOL     bSetViewStyle(EViewStyle vsViewStyle);


        //-------------------------------------
        //сообщения
    #if (xWINVER >= xWIN32_2K)
        UINT     uiGetPos     ();
    #endif //xWIN32_2K
    #if (xWINVER >= xWIN32_2K)
        BOOL     bSetPos      (UINT uiPos);
    #endif //xWIN32_2K
    #if (xWINVER >= xWIN32_2K)
        BOOL     bSetDeltaPos (INT iDelta);
    #endif //xWIN32_2K

    #if (xWINVER >= xWIN32_VISTA)
        EState   stGetState   ();
    #endif //xWIN32_VISTA
    #if (xWINVER >= xWIN32_VISTA)
        BOOL     bSetState    (EState stState);
    #endif //xWIN32_VISTA

    #if (xWINVER >= xWIN32_VISTA)
        COLORREF crGetBarColor();
    #endif //xWIN32_VISTA
    #if (xWINVER >= xWIN32_2K)
        BOOL     bSetBarColor (COLORREF crColor /* = CLR_DEFAULT*/);
    #endif //xWIN32_2K
    #if (xWINVER >= xWIN32_VISTA)
        COLORREF crGetBkColor ();
    #endif //xWIN32_VISTA
    #if (xWINVER >= xWIN32_2K)
        BOOL     bSetBkColor  (COLORREF crColor /*= CLR_DEFAULT*/);
    #endif //xWIN32_2K


    #if (xWINVER >= xWIN32_2K)
        BOOL     bGetRange    (INT *piMin, INT *piMax);
    #endif //xWIN32_2K
        #if (xWINVER >= xWIN32_2K)
        BOOL     bSetRange    (USHORT usMin, USHORT usMax);
    #endif //xWIN32_2K
    #if (xWINVER >= xWIN32_2K)
        BOOL     bSetRange32  (INT iMin, INT iMax);
    #endif //xWIN32_2K

    #if (xWINVER >= xWIN32_VISTA)
        UINT     uiGetStep    ();
    #endif //xWIN32_VISTA
    #if (xWINVER >= xWIN32_2K)
        BOOL     bSetStep     (UINT uiStep);
    #endif //xWIN32_2K
    #if (xWINVER >= xWIN32_2K)
        BOOL     bStepIt      ();
    #endif //xWIN32_2K

    #if (xWINVER >= xWIN32_S03)
        BOOL     bSetMarquee  (BOOL bIsOn, ULONG ulMilliSeconds);
    #endif //xWIN32_S03


        //-------------------------------------
        //события

    private:
        EViewStyle _m_vsViewStyle;
};
//---------------------------------------------------------------------------
#endif    //XLib_Gui_CxProgressBarH




////PBM_DELTAPOS    Advances the current position of a progress bar by a specified increment and redraws the bar to reflect the new position.
////PBM_GETBARCOLOR    Gets the color of the progress bar.
////PBM_GETBKCOLOR    Gets the background color of the progress bar.
////PBM_GETPOS        Retrieves the current position of the progress bar.
////PBM_GETRANGE    Retrieves information about the current high and low limits of a given progress bar control.
////PBM_GETSTATE    Gets the state of the progress bar.
////PBM_GETSTEP        n/i
////PBM_SETBARCOLOR    Sets the color of the progress indicator bar in the progress bar control.
////PBM_SETBKCOLOR    Sets the background color in the progress bar.
////PBM_SETMARQUEE    Sets the progress bar to marquee mode
////PBM_SETPOS        Sets the current position for a progress bar and redraws the bar to reflect the new position.
////PBM_SETRANGE    Sets the minimum and maximum values for a progress bar and redraws the bar to reflect the new range.
////PBM_SETRANGE32    Sets the range of a progress bar control to a 32-bit value.
////PBM_SETSTATE    Sets the state of the progress bar.
////PBM_SETSTEP        Specifies the step increment for a progress bar
////PBM_STEPIT        Advances the current position for a progress bar by the step increment and redraws the bar to reflect the new position
