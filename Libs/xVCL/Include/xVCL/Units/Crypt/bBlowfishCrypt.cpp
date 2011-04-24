/**********************************************************************
*	bBlowfishCrypt -
*
***********************************************************************/



//---------------------------------------------------------------------------
//TODO: bBlowfishCrypt 
bool bBlowfishCrypt(FILE *pFileIn, FILE *pFileOut, int iMode, const std::string &csBlowfishCryptKey) {
	//-------------------------------------
	//CHECK
	if (NULL == pFileIn || NULL == pFileOut) {
		return false;
	}
	if (!(BF_ENCRYPT == iMode) && !(BF_DECRYPT == iMode) ) {
		return false;
	}

	//-------------------------------------
	//переменные
	int                iNum        = 0;
	const unsigned int cuiBuffSize = 1024;
	unsigned char      ucBuffIn [cuiBuffSize];	memset(ucBuffIn,  0, sizeof(unsigned char) * cuiBuffSize);
	unsigned char      ucBuffOut[cuiBuffSize];	memset(ucBuffOut, 0, sizeof(unsigned char) * cuiBuffSize);
	  
	//-------------------------------------
	//Ключ шифрования длиной 128 бит и вектор инициализации 
	unsigned char ucIv[8];	memset(ucIv, 0, sizeof(unsigned char) * 8);

	size_t uiKeySize = sizeof(unsigned char) * csBlowfishCryptKey.size();
	unsigned char *pucKey = (unsigned char *)malloc(uiKeySize);
	if (pucKey == NULL) {
		return false;
	}
	////////vStrToUCHAR(сsBlowfishCryptKey, pucKey, сsBlowfishCryptKey.size());		 
	  
	//-------------------------------------
	//Помещаем ключ в структуру bfkey
	BF_KEY bfkey;
	BF_set_key(&bfkey, uiKeySize, pucKey);	
	free(pucKey);
	pucKey = NULL;
	 
	//-------------------------------------
	//Шифруем блоки входного файла
	for (;;) { 
		size_t uiInLen = fread(ucBuffIn, 1, cuiBuffSize, pFileIn); 
		if (uiInLen <= 0) {
			break; 
		}
		  
		BF_cfb64_encrypt(ucBuffIn, ucBuffOut, uiInLen, &bfkey, ucIv, &iNum , iMode); 
		fwrite(ucBuffOut, 1, uiInLen, pFileOut); 
	} 

	return true; 
}
//---------------------------------------------------------------------------
