/****************************************************************************
* Class name:  CxTest_CxUrlCoder
* Description: test CxUrlCoder
* File name:   CxTest_CxUrlCoder.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


//---------------------------------------------------------------------------
//DONE: CxTest_CxUrlCoder (constructor)
CxTest_CxUrlCoder::CxTest_CxUrlCoder() {
    bSetName(xFUNCTION);
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxUrlCoder (destructor)
CxTest_CxUrlCoder::~CxTest_CxUrlCoder() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxUrlCoder::bUnit() {
	std::string sStr("Privet chuvyrlo! ! !+");

	CXUrlCoder C;
	sStr = C.sEncode(sStr);
	std::cout << "encode:\t" << sStr << std::endl;

	sStr = C.sDecode(sStr);
	std::cout << "decode:\t" << sStr << std::endl;

	system("pause");

    return TRUE;
}
//---------------------------------------------------------------------------
