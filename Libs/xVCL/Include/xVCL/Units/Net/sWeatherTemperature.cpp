/****************************************************************************
* Unit name:   sWeatherTemperature
* Description: получение температуры воздуха за бортом (Киев, по Цельсию)
* File name:   sWeatherTemperature.cpp
* Compilers:   C++ Builder 2010
* String type: Ansi, Unicode
* Libraries:   VCL
* Author:      Sergey Shapka
* E-mail:      dr.web.agent@gmail.com
* Created:     12.11.2009 11:50:00
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


#ifndef XVCL_Net_sWeatherTemperatureH
#define XVCL_Net_sWeatherTemperatureH
//---------------------------------------------------------------------------
#include <memory>
#include "IdBaseComponent.hpp"
#include "IdComponent.hpp"
#include "IdHTTP.hpp"
#include "IdTCPClient.hpp"
#include "IdTCPConnection.hpp"

#pragma link "IdBaseComponent"
#pragma link "IdComponent"
#pragma link "IdHTTP"
#pragma link "IdTCPClient"
#pragma link "IdTCPConnection"
//---------------------------------------------------------------------------
String sWeatherTemperature() {
	String sRes;
	String sUrl     = xT("http://weather.yahoo.com/ukraine/kiev-city-municipality/kiev-924938/?unit=c");
	String sFindStr = xT("<dt>Feels Like:</dt><dd>");	//<dt>Feels Like:</dt><dd>8 &deg;C</dd>

	std::auto_ptr<TIdHTTP> apIdHTTP(new TIdHTTP(0));
	/*DEBUG*/xASSERT(NULL != apIdHTTP.get());

	try {
		sRes = apIdHTTP->Get(sUrl);

		//удаляем до строки "8 &deg;C</dd>"
		int sFindStrPos = sRes.Pos(sFindStr);
		sRes = sRes.Delete(1, sFindStrPos + sFindStr.Length() - 1);

		//позиция пробела
		int sFindSpace = sRes.Pos(xT(" "));

		//вырезаем значение температуры
		sRes = sRes.SubString(0, sFindSpace);

		//если плюсовая температура - добавляем "+"
		if (xT('-') != sRes[1]) {
			sRes = String(xT('+')) + sRes;
		}

		sRes = sRes.Trim() + xT(" °C");
	}
	catch (...) {
		sRes = xT("- °C");
	}

	return sRes;
}
//---------------------------------------------------------------------------
#endif //XVCL_Net_sWeatherTemperatureH