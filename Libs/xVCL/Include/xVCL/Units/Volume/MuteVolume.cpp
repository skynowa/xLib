/**********************************************************************
*
*
***********************************************************************/


void __fastcall TfrmMainServer::MuteVolume(bool bMuteFlag) {
	if (mixerGetNumDevs() < 1) {
		return;
	}

	HMIXER hMix;
	if (mixerOpen(&hMix, 0, 0, 0, 0) != MMSYSERR_NOERROR) {
		return;
	}

	MIXERCONTROLDETAILS_BOOLEAN mcdMute;

	MIXERLINE ml = {0};
	ml.cbStruct        = sizeof(MIXERLINE);
	ml.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
	mixerGetLineInfo(hMix, &ml, MIXER_GETLINEINFOF_COMPONENTTYPE);

	MIXERLINECONTROLS mlc = {0};

	MIXERCONTROL mc = {0};
	mlc.cbStruct      = sizeof(MIXERLINECONTROLS);
	mlc.dwLineID      = ml.dwLineID;
	mlc.dwControlType = MIXERCONTROL_CONTROLTYPE_MUTE;
	mlc.cControls     = 1;
	mlc.pamxctrl      = &mc;
	mlc.cbmxctrl      = sizeof(MIXERCONTROL);
	mixerGetLineControls(hMix, &mlc, MIXER_GETLINECONTROLSF_ONEBYTYPE);

	MIXERCONTROLDETAILS mcd = {0};
	mcd.cbStruct    = sizeof(MIXERCONTROLDETAILS);
	mcd.hwndOwner   = 0;
	mcd.dwControlID = mc.dwControlID;
	mcd.paDetails   = &mcdMute;
	mcd.cbDetails   = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	mcd.cChannels   = 1;
	mixerGetControlDetails(hMix, &mcd, MIXER_GETCONTROLDETAILSF_VALUE);
	mcdMute.fValue  = bMuteFlag;	//отключения/включения
	mixerSetControlDetails(hMix, &mcd, MIXER_SETCONTROLDETAILSF_VALUE);
}