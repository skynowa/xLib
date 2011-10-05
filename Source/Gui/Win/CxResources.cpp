/**
 * \file  CxResources.cpp
 * \brief resources
 */


#include <xLib/Gui/Win/CxResources.h>

#if defined(xOS_ENV_WIN)
#define RES_FILE_PATH <xLib/Gui/Resource.xrc.cpp>
//---------------------------------------------------------------------------
//DONE: �������������� ������ �����
CxResources::TSettingsMap CxResources::_m_mapResContent;
//---------------------------------------------------------------------------


/****************************************************************************
*    Public methods
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: bInit ()
/*static*/
BOOL CxResources::bInit() {
    BOOL bRes = FALSE;

    #ifndef RES_FILE_PATH
        #error "xLib: [Please, define RES_FILE_PATH]"

        return FALSE;
    #endif

    //�������� ���� � ����� ������� ���������
    #include RES_FILE_PATH

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: sGetText (�� ID �������� ���� ��������)
/*static*/
tString CxResources::sGetText(INT iID) {
    xCHECK_RET(true == _m_mapResContent.empty(), 0);

    return _m_mapResContent[iID].sGetText();
}
//---------------------------------------------------------------------------
//DONE: iGetLeft (�� ID �������� ���� ��������)
/*static*/INT CxResources::iGetLeft(INT iID) {
    xCHECK_RET(true == _m_mapResContent.empty(), 0);

    return _m_mapResContent[iID].iGetLeft();
}
//---------------------------------------------------------------------------
//DONE: iGetTop (�� ID �������� ���� ��������)
/*static*/
INT CxResources::iGetTop(INT iID) {
    xCHECK_RET(true == _m_mapResContent.empty(), 0);

    return _m_mapResContent[iID].iGetTop();
}
//---------------------------------------------------------------------------
//DONE: iGetWidth (�� ID �������� ���� ��������)
/*static*/
INT CxResources::iGetWidth(INT iID) {
    xCHECK_RET(true == _m_mapResContent.empty(), 0);

    return _m_mapResContent[iID].iGetWidth();
}
//---------------------------------------------------------------------------
//DONE: iGetHeight (�� ID �������� ���� ��������)
/*static*/
INT CxResources::iGetHeight(INT iID) {
    xCHECK_RET(true == _m_mapResContent.empty(), 0);

    return _m_mapResContent[iID].iGetHeight();
}
//---------------------------------------------------------------------------
//DONE: ulGetStyle (�� ID �������� ���� ��������)
/*static*/
ULONG CxResources::ulGetStyle(INT iID) {
    xCHECK_RET(true == _m_mapResContent.empty(), 0);

    return _m_mapResContent[iID].ulGetStyle();
}
//---------------------------------------------------------------------------
//DONE: ulGetStyleEx (�� ID �������� ���� ��������)
/*static*/
ULONG CxResources::ulGetStyleEx(INT iID) {
    xCHECK_RET(true == _m_mapResContent.empty(), 0);

    return _m_mapResContent[iID].ulGetStyleEx();
}
//---------------------------------------------------------------------------


/****************************************************************************
*    Private methods
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxResources
CxResources::CxResources() {
    /*DEBUG*/xASSERT(FALSE);
}
//---------------------------------------------------------------------------
//DONE: ~CxResources
CxResources::~CxResources() {
    /*DEBUG*/xASSERT(FALSE);
}
//---------------------------------------------------------------------------
//DONE: _bInitControl
/*static*/
BOOL CxResources::_bInitControl(INT iID, const tString &csText, INT iLeft, INT iTop, INT iWidth, INT iHeight, ULONG ulStyle, ULONG ulStyleEx) {
    xASSERT_RET(0 <  iID,     FALSE);
    xASSERT_RET(0 <= iLeft,   FALSE);
    xASSERT_RET(0 <= iTop,    FALSE);
    xASSERT_RET(0 <= iWidth,  FALSE);
    xASSERT_RET(0 <= iHeight, FALSE);

    _m_mapResContent[iID] = CXSettings(csText, iLeft, iTop, iWidth, iHeight, ulStyle, ulStyleEx);

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: _bRemoveControl
/*static*/
BOOL CxResources::_bRemoveControl(INT iID) {
    xASSERT_RET(0 < iID, FALSE);

    TSettingsMap::const_iterator it;

    it = _m_mapResContent.find(iID);
    xASSERT_RET(_m_mapResContent.end() != it, FALSE);

    _m_mapResContent.erase(it);

    return TRUE;
}
//---------------------------------------------------------------------------
#endif
