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
��� �������� TColor, ���� �������� �������, ����� � ������ ������������? 
int red = random(255);		  // ������� ������������
int blue = random(255);		  // ����� ������������
int green = random(255);	  // ������� ������������
Label1->Font->Color = (TColor)RGB(red,green,blue);

��� ���� TColor, �������� �������� �������, ����� � ������ ������������? 
TColor color = ...;
unsigned red   = GetRValue(color); // ������� ������������
unsigned green = GetGValue(color); // ������� ������������
unsigned blue  = GetBValue(color); // ����� ������������

��� ������ ������� �����? 
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