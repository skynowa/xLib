/****************************************************************************
*	TColorConverter.cpp
*
*****************************************************************************/


#include <vcl.h>
#include "uMain.h"
//---------------------------------------------------------------------------
//RGB to TColor Values
TColor crRGBToTColor(BYTE byRed, BYTE byGreen, BYTE byBlue) {
	return static_cast<TColor>( RGB(byRed, byGreen, byBlue) );
}
//---------------------------------------------------------------------------
//TColor to RGB values
VOID vTColorToRGB(TColor crColor, BYTE *pucRed, BYTE *pucGreen, BYTE *pucBlue) { 
	/*DEBUG*/// crColor  - n/a
	/*DEBUG*/// pucRed   - n/a
	/*DEBUG*/// pucGreen - n/a
	/*DEBUG*/// pbyBlue  - n/a

	xCHECK_DO(NULL != pucRed,   (*pucRed)   = GetRValue(crColor));
	xCHECK_DO(NULL != pucGreen, (*pucGreen) = GetGValue(crColor));
	xCHECK_DO(NULL != pucBlue , (*pucBlue)  = GetBValue(crColor));
}
//---------------------------------------------------------------------------



/*
 ак получить TColor, име€ значени€ красной, синей и зелЄной составл€ющих? 
int red = random(255);		  // красна€ составл€юща€
int blue = random(255);		  // син€€ составл€юща€
int green = random(255);	  // зелена€ составл€юща€
Label1->Font->Color = (TColor)RGB(red,green,blue);

 ак име€ TColor, получить значени€ красной, синей и зелЄной составл€ющих? 
TColor color = ...;
unsigned red   = GetRValue(color); // красна€ составл€юща€
unsigned green = GetGValue(color); // зелена€ составл€юща€
unsigned blue  = GetBValue(color); // син€€ составл€юща€

 ак узнать €ркость цвета? 
TColor color = ...;
unsigned luminosity = (GetRValue(color)*77 + GetGValue(color)*151 + GetBValue(color)*28) >> 8;
*/


/*
// RGB to TColor Values
procedure TForm1.Button1Click(Sender: TObject);
begin
  Edit1.Color := RGB(58, 110, 165);
end;

// TColor to RGB values
procedure TForm1.Button2Click(Sender: TObject); 
var 
  Color: Longint; 
  r, g, b: Byte; 
begin 
  Color := ColorToRGB(Edit1.Color); 
  r     := Color; 
  g     := Color shr 8; 
  b     := Color shr 16; 
  label1.Caption := ' Red  : ' + IntToStr(r) + 
    ' Green: ' + IntToStr(g) + 
    ' Blue : ' + IntToStr(b); 
end;
*/