/**********************************************************************
*	
*
***********************************************************************/


//---------------------------------------------------------------------------
void __fastcall vEnableControls(bool bFlag) {
    for (int i = 1; i < ComponentCount; i ++) {
        tString asClassName           = Components[i]->ClassName();
        tString asParentComponentName = "";

        if (Components[i]->HasParent() && asClassName == "TCheckBox") {
            asParentComponentName = Components[i]->GetParentComponent()->Name;

            if (asParentComponentName == "tsDeleteOptions") {
                ((TCheckBox *)Components[i])->Enabled = bFlag;
            }
        }
    }

    //--TCheckBox->Enabled = bFlag;
}
//---------------------------------------------------------------------------