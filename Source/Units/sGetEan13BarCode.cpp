/**
 * \file  sGetEan13BarCode.cpp
 * \brief code EAN-13
 */


#include <xLib/Units/sGetEan13BarCode.h>


//---------------------------------------------------------------------------
std::string_t
sGetEan13BarCode(
    const std::string_t &csData	///< a 12 digits length string
)
	///< \return a string which give the bar code when it is dispayed with EAN13.TTF font an empty string if the supplied parameter is no good
{
	/*DEBUG*/xASSERT_RET(false == csData.empty(), std::string_t());
	/*DEBUG*/xASSERT_RET(12    == csData.size(),  std::string_t());

	/*DEBUG*///And they are really digits
	/*DEBUG*/for (size_t i = 0; i < csData.size(); ++ i) {
	/*DEBUG*/	if ( (INT)csData.at(i) < 48 || (INT)csData.at(i) > 57 ) {
	/*DEBUG*/		/*DEBUG*/xASSERT_RET(FALSE, std::string_t());
	/*DEBUG*/	}
	/*DEBUG*/}

	std::string_t sRes;
	INT 	iFirst    = 0;
	BOOL    bTableA   = FALSE;
	std::string_t sData     = csData;

	//-------------------------------------
	//x - ����� ������
	//x = 4 + 3 + 1 + 2 + 8 + 9 = 27
	INT iX = 0;

	for (INT i = csData.size() - 2; i >= 0; i -= 2) {
		iX += CxString::lexical_cast<INT>(sData.substr(i, 1));
	}
	/*DEBUG*///xASSERT(27 == iX);

	//-------------------------------------
	//y - ����� ��������
	//y = 7 + 4 + 1 + 0 + 0 + 7 = 19
	INT iY = 0;

	for (INT i = csData.size() - 1; i >= 0; i -= 2) {
		iY += CxString::lexical_cast<INT>(sData.substr(i, 1));
	}
	/*DEBUG*///xASSERT(19 == iY);

	//-------------------------------------
	//��������� Z �� �������: z = x + 3 * y
	//z = 3 * 19 + 27 = 84
	INT iZ = 0;

	iZ = iX + iY * 3;
	/*DEBUG*///xASSERT(84 == iZ);

	//-------------------------------------
	//����������� ����� (13-� ������): 90 - 84 = 6
	std::string_t sCheckSum;

	sCheckSum = CxString::lexical_cast((10 - iZ % 10) % 10 );

	//-------------------------------------
	//��� EAN13 (9 780201 134476)
	sData.append(sCheckSum);
	/*DEBUG*/xASSERT(false               == sData.empty());
	/*DEBUG*///xASSERT(xT("9780201134476") == sData);

	//-------------------------------------
	//The first digit is taken just as it is, the second one come from table A
	sRes   = std::string_t(1, sData.at(0))  + std::string_t(1,  (TCHAR)(65 + CxString::lexical_cast<INT>(sData.substr(1, 1))));
	iFirst = CxString::lexical_cast<INT>( std::string_t(1, sData.at(0)) );

	for (INT i = 2; i < 7; ++ i) {
		bTableA = FALSE;

		switch (i) {
			case 2:
				{
					//0 To 3
					switch (iFirst) {
						case 0:
						case 1:
						case 2:
						case 3: { bTableA = TRUE; }    break;
					}
				}
				break;

			case 3:
				{
					//0, 4, 7, 8
					switch (iFirst) {
						case 0:
						case 4:
						case 7:
						case 8: { bTableA = TRUE; }    break;
					}
				}
				break;

			case 4:
				{
					//0, 1, 4, 5, 9
					switch (iFirst) {
						case 0:
						case 1:
						case 4:
						case 5:
						case 9: { bTableA = TRUE; }    break;
					}
				}
				break;

			case 5:
				{
					//0, 2, 5, 6, 7
					switch (iFirst) {
						case 0:
						case 2:
						case 5:
						case 6:
						case 7: { bTableA = TRUE; }    break;
					}
				}
				break;

			case 6:
				{
					//0, 3, 6, 8, 9
					switch (iFirst) {
						case 0:
						case 3:
						case 6:
						case 8:
						case 9: { bTableA = TRUE; }    break;
					}
				}
				break;
		}

		if (TRUE == bTableA) {
			TCHAR chChar = (TCHAR)(65 + CxString::lexical_cast<INT>(sData.substr(i, 1)));
			sRes.push_back( chChar );
		} else {
			TCHAR chChar = (TCHAR)(75 + CxString::lexical_cast<INT>(sData.substr(i, 1)));
			sRes.push_back( chChar );
		}
	} //for

	//Add middle separator
	sRes.append(xT("*"));

	//6 digits from table C
	for (size_t i = 7; i < sData.size(); ++ i) {
		sRes.push_back( (TCHAR)(97 + CxString::lexical_cast<INT>(sData.substr(i, 1))) );
	}

	//Add end mark
	sRes.append(xT("+"));

	return sRes;
}
//---------------------------------------------------------------------------
std::string_t
sGetEan13Code(
    const std::string_t &csData	///< a 12 digits length string
)
	///< \return a string which give the bar code when it is dispayed with EAN13.TTF font an empty string if the supplied parameter is no good
{
	//	����� ���������� ������ ������.
	//	����� X - ����� ������ (�� ��������� - ����. Lyekka) ����, Y - ����� �������� (�� ���������) ����.
	//	��������� Z �� �������: z = x + 3 * y
	//	����� M - �����, ������� ������� �� 10 � ��������������� ������ Z.
	//	����������� ����� ���� m - z

	//������: 978020113447
	//	x = 4 + 3 + 1 + 2 + 8 + 9 = 27
	//	y = 7 + 4 + 1 + 0 + 0 + 7 = 19
	//	z = 3 * 19 + 27 = 84
	//	m = 90
	//	����������� �����= 90 - 84 = 6
	//	EAN13 ---> 9 780201 134476

	std::string_t sRes;

	//-------------------------------------
	//x - ����� ������
	//x = 4 + 3 + 1 + 2 + 8 + 9 = 27
	size_t uiX = 0;
	for (size_t i = 0; i < csData.size(); i += 2) {
		//iMsgBox( csData.at(i) );
		uiX = uiX + CxString::lexical_cast<size_t>( std::string_t(1, csData.at(i)) );
	}
	/*DEBUG*///xASSERT(27 == uiX);

	//-------------------------------------
	//y - ����� ��������
	//y = 7 + 4 + 1 + 0 + 0 + 7 = 19
	size_t uiY = 0;
	for (size_t i = 1; i < csData.size(); i += 2) {
		//iMsgBox( csData.at(i) );
		uiY = uiY + CxString::lexical_cast<size_t>( std::string_t(1, csData.at(i)) );
	}
	/*DEBUG*///xASSERT(19 == uiY);



	//-------------------------------------
	//��������� Z �� �������: z = x + 3 * y
	//z = 3 * 19 + 27 = 84
	size_t uiZ = 0;

	uiZ = uiX + uiY * 3;
	/*DEBUG*///xASSERT(84 == uiZ);


	//-------------------------------------
	//����� M - �����, ������� ������� �� 10 � ��������������� ������ Z.
	//m = 90
	size_t uiM = 0;

	for (size_t i = uiZ + 1; ; ++ i) {
		if (0 == i % 10) {
			uiM = i;
        	break;
		}
	}
	/*DEBUG*///xASSERT(90 == uiM);

	//-------------------------------------
	//����������� �����= 90 - 84 = 6
	size_t uiCtrlSumm = 0;

	uiCtrlSumm = uiM - uiZ;
	/*DEBUG*///xASSERT(6 == uiCtrlSumm);

	//-------------------------------------
	//EAN13 ---> 9 780201 134476
	sRes = csData + CxString::lexical_cast(uiCtrlSumm);
	/*DEBUG*///xASSERT(false               == sRes.empty());
	/*DEBUG*///xASSERT(xT("9780201134476") == sRes);

	return sRes;
}
//---------------------------------------------------------------------------
