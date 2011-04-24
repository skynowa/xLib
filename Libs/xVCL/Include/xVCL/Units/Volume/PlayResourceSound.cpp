/***********************************************************************
*   
*
************************************************************************/


void __fastcall TfrmMainServer::PlayResourceSound(const tString &asWavSoundID) {
    PlaySound(asWavSoundID.c_str(), 0, SND_RESOURCE | SND_ASYNC);
}
