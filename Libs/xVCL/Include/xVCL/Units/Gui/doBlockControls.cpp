/***********************************************************************
*	Блокируем/разблокируем контролы
*
************************************************************************/

void __fastcall doBlockControls(bool Flag){
    txtInFolder->Enabled=Flag;
    //cmdInFolder->Enabled=Flag;
    optWithOutFarmat->Enabled=Flag;
    optFarmatAsWEBPage->Enabled=Flag;
    txtInsertIndex->Enabled=Flag;
    cboFileMask->Enabled=Flag;
    cboExtationSaveAs->Enabled=Flag;
    chkNumericFiles->Enabled=Flag;
}
