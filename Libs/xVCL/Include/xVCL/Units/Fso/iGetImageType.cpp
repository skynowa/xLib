/**********************************************************************
*	iGetImageType.cpp
*
***********************************************************************/


//---------------------------------------------------------------------------
int __fastcall iGetImageType(TMemoryStream *pMS)  {
	xASSERT(pMS);

	enum EImageType {itUnknown = - 1, itBmp = 0, itJpg = 1,  itGif = 2, itPng = 3};

	int           iRes      = itUnknown;
	__int64       StreamPos = 0;

	const unsigned long int cucImgSignSize = 10;
	unsigned char           ucImgSign[cucImgSignSize];	ZeroMemory(&ucImgSign[0], cucImgSignSize);

	StreamPos = pMS->Position;
	__try {
		//-------------------------------------
		//BM
		if (itUnknown == iRes) {
			const unsigned long int cucBmSize        = 2;
			unsigned char           ucBm[cucBmSize] = {0x42, 0x4D};

			ZeroMemory(&ucImgSign[0], 10);
			pMS->Position = StreamPos;
			pMS->Read(ucImgSign, cucBmSize);

			if (0 == strncmp(ucImgSign, ucBm, cucBmSize)) {
				iRes = itBmp;
			} else {
				iRes = itUnknown;
			}
		}

		//-------------------------------------
		//JFIF, JFI, JPG, JPEG
		//06h  Идентификационная строка "JFIF", заканчивающаяся нулём
		if (itUnknown == iRes) {
			const unsigned long int cucJfifSize         = 5;
			unsigned char           ucJfif[cucJfifSize] = {0x4A, 0x46, 0x49, 0x46, 0x00};

			ZeroMemory(&ucImgSign[0], cucImgSignSize);
			pMS->Position = StreamPos;
			pMS->Seek(6, soFromCurrent);
			pMS->Read(ucImgSign, cucJfifSize);

			if (0 == strncmp(ucImgSign, ucJfif, cucJfifSize)) {
				iRes = itJpg;
			} else {
				iRes = itUnknown;
			}
		}

		//-------------------------------------
		//GIF87a, GIF89a, GIF
		if (itUnknown == iRes) {
			const unsigned long int cucGifSize        = 3;
			unsigned char           ucGif[cucGifSize] = {0x47, 0x49, 0x46};

			ZeroMemory(&ucImgSign[0], cucImgSignSize);
			pMS->Position = StreamPos;
			pMS->Read(ucImgSign, cucGifSize);

			if (0 == strncmp(ucImgSign, ucGif, cucGifSize)) {
				iRes = itGif;
			} else {
				iRes = itUnknown;
			}
		}

		//-------------------------------------
		//PNG
		if (itUnknown == iRes) {
			const unsigned long int cucPngSize        = 8;
			unsigned char           ucPng[cucPngSize] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};

			ZeroMemory(&ucImgSign[0], cucImgSignSize);
			pMS->Position = StreamPos;
			pMS->Read(ucImgSign, cucPngSize);

			if (0 == strncmp(ucImgSign, ucPng, cucPngSize)) {
				iRes = itPng;
			} else {
				iRes = itUnknown;
			}
		}
	}
	__finally {
		pMS->Position = StreamPos;
	}

	return iRes;
}
//---------------------------------------------------------------------------