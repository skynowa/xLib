//---------------------------------------------------------------------------
BOOL bCompression(const String &csFilePath) {
	std::auto_ptr<TFileStream>         apInFile     (new TFileStream(csFilePath, fmOpenRead | fmShareExclusive));
	std::auto_ptr<TFileStream>         apOutFile    (new TFileStream(csFilePath + _T(".arh"), fmCreate | fmShareExclusive));
	std::auto_ptr<TZCompressionStream> apComprStream(new TZCompressionStream(Zlib::clMax, apOutFile.get()));

	apComprStream->CopyFrom(apInFile.get(), apInFile->Size);
	apComprStream->CompressionRate;

	return TRUE;
}
//---------------------------------------------------------------------------
BOOL bDecompression(const String &csFilePath) {
	int    iReaded = 0;
	TCHAR *pszBuff = new TCHAR[1024];

	std::auto_ptr<TFileStream> apInFile(new TFileStream(csFilePath,fmOpenRead|fmShareExclusive));

	String sFilePath = StringReplace(_T("res_") + csFilePath, _T(".arh"), _T(""), TReplaceFlags() << rfReplaceAll);

	std::auto_ptr<TFileStream>           apOutFile (new TFileStream(csFilePath, fmCreate | fmShareExclusive));
	std::auto_ptr<TZDecompressionStream> decompress(new TZDecompressionStream(apInFile.get()));
	do {
	   iReaded = decompress->Read(pszBuff, 1024);
	   apOutFile->Write(pszBuff,iReaded);
	}
	while (iReaded);

	delete [] pszBuff;

	return TRUE;
}
//---------------------------------------------------------------------------