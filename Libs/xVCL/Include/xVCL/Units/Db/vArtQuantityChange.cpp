/**********************************************************************
*	vArtQuantityPlus - ���������/�������� �/�� ������� ���
*
***********************************************************************/


#include "uDoc.h"           //frmDoc
#include "uEToken.h"        //frmMain
//---------------------------------------------------------------------------
void vArtQuantityChange(TADOConnection *pADOConnection, const tString &asArticle, signed int iValue) {
    //-------------------------------------
    //������ �������� ���� FN_QUANTITY � ��������� TN_INFO �� ������ ���  (frmDoc->asExecSQLStr(pADOConnection, asSQLStr1)).ToInt();
    tString asSQLStr1 =
           "SELECT \
                FN_QUANTITY AS tmp_var \
            FROM \
                TN_INFO \
            WHERE \
                FN_ETOKEN_ID = " + asArticle;     

    int iArtQuantity = 0;
    TADOQuery *qryTmp1 =  new TADOQuery(NULL);
    qryTmp1->Connection = pADOConnection;
    qryTmp1->Close();
    qryTmp1->SQL->Text = asSQLStr1;
    try {
        qryTmp1->Open();
        iArtQuantity = qryTmp1->FieldByName("tmp_var")->Value;
    } catch (Exception &exception) {
        Application->ShowException(&exception); //��������� �������, � ��.
    }
    delete qryTmp1; qryTmp1 = NULL;

    //-------------------------------------

    //-------------------------------------
    //��������/������ iValue ������        ////frmDoc->vExecSQLStr(pADOConnection, asSQLStr2, false);
    tString asSQLStr2 =
           "UPDATE \
                TN_INFO \
            SET \
                FN_QUANTITY = "  + tString(iArtQuantity + iValue) + " \
            WHERE \
                FN_ETOKEN_ID = " + asArticle;

    TADOQuery *qryTmp2 =  new TADOQuery(NULL);
	qryTmp2->Connection = pADOConnection;
	qryTmp2->Close();
	qryTmp2->SQL->Text = asSQLStr2;
    try {
        qryTmp2->ExecSQL();
    } catch (Exception &exception) {
        Application->ShowException(&exception); //��������� �������, � ��.
    }
	delete qryTmp2; qryTmp2 = NULL;
}
//---------------------------------------------------------------------------

