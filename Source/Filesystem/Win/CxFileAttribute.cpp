/****************************************************************************
* Class name:  CxFileAttribute
* Description: file attribute
* File name:   CxFileAttribute.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     06.04.2010 13:37:54
*
*****************************************************************************/


#include <xLib/Filesystem/Win/CxFileAttribute.h>


/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: atGet
/*static*/
CxFileAttribute::EAttribute
CxFileAttribute::atGet(const tString &csFilePath) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), faInvalid);

    EAttribute faRes;

#if defined(xOS_WIN)
    faRes = static_cast<EAttribute>( ::GetFileAttributes(csFilePath.c_str()) );
    /*DEBUG*/// n/a
#elif defined(xOS_LINUX)
    //TODO: xOS_LINUX

    struct stat sb = {0};

    INT iRes = stat(csFilePath.c_str(), &sb)
    /*DEBUG*/xASSERT_RET(- 1 != iRes, faInvalid);

    switch (sb.st_mode & S_IFMT) {
        case S_IFBLK:  faRes = ("block device\n");            break;
        case S_IFCHR:  faRes = ("character device\n");        break;
        case S_IFDIR:  faRes = ("directory\n");               break;
        case S_IFIFO:  faRes = ("FIFO/pipe\n");               break;
        case S_IFLNK:  faRes = ("symlink\n");                 break;
        case S_IFREG:  faRes = ("regular file\n");            break;
        case S_IFSOCK: faRes = ("socket\n");                  break;
        default:       faRes = ("unknown?\n");                break;
    }
#endif

    return faRes;
}
//---------------------------------------------------------------------------
//DONE: bSet
/*static*/
BOOL
CxFileAttribute::bSet(const tString &csFilePath, EAttribute atValue) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// atValue

BOOL bRes = FALSE;

#if defined(xOS_WIN)
    bRes = ::SetFileAttributes(csFilePath.c_str(), static_cast<ULONG>(atValue));
    /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
#elif defined(xOS_LINUX)
    //TODO: xOS_LINUX
    xNOT_IMPLEMENTED_RET(FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//DONE: bAdd
/*static*/
BOOL
CxFileAttribute::bAdd(const tString &csFilePath, EAttribute atValue) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// atValue

#if defined(xOS_WIN)
    return bModify(csFilePath, static_cast<EAttribute>(0), atValue);
#elif defined(xOS_LINUX)
    //TODO: xOS_LINUX
    xNOT_IMPLEMENTED_RET(FALSE);
#endif
}
//---------------------------------------------------------------------------
//DONE: bRemove ()
/*static*/
BOOL
CxFileAttribute::bRemove(const tString &csFilePath, EAttribute atValue)  {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// atValue

#if defined(xOS_WIN)
    return bModify(csFilePath, atValue, static_cast<EAttribute>(0));
#elif defined(xOS_LINUX)
    //TODO: xOS_LINUX
    xNOT_IMPLEMENTED_RET(FALSE);
#endif
}
//---------------------------------------------------------------------------
//DONE: bModify
/*static*/
BOOL
CxFileAttribute::bModify(const tString &csFilePath, EAttribute atRemoveValue, EAttribute atAddValue) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// atRemoveValue
    /*DEBUG*/// atAddValue

#if defined(xOS_WIN)
    //First we get the current window Attr.
    EAttribute atValue = atGet(csFilePath);

    //Change bits.
    ////atValue &= ~ulRemoveValue;
    ////atValue |= ulAddValue;
    atValue = static_cast<EAttribute>( static_cast<ULONG>(atValue) & ~atRemoveValue );
    atValue = static_cast<EAttribute>( static_cast<ULONG>(atValue) |  atAddValue    );

    //Change the Attr.
    bSet(csFilePath, atValue);
    /*DEBUG*/
#elif defined(xOS_LINUX)
    //TODO: xOS_LINUX
    xNOT_IMPLEMENTED_RET(FALSE);
#endif

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: - bIsExists ()
/*static*/
BOOL
CxFileAttribute::bIsExists(const tString &csFilePath, EAttribute atValue) {
    /*DEBUG*/xASSERT_RET(false == csFilePath.empty(), FALSE);
    /*DEBUG*/// atValue

#if defined(xOS_WIN)
    //////ULONG _ulAttr = 0xffffffff;
    //////
    //////_m_bRes = bGetAttr(&_ulAttr);
    ///////*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

    //////if (_ulAttr & ulAttr) {
    //////    return TRUE;
    //////}

    ////////////////////if ((ulGetAttr() & BS_TYPEMASK) == atValue) {
    ////////////////////    return TRUE;
    ////////////////////}

    /*ULONG _ulAttr = ulGetAttr();
    if (_ulAttr & ulAttr) {
        return TRUE;
    }*/

    EAttribute _atValue = faInvalid;

    _atValue = atGet(csFilePath);
    xCHECK_RET(_atValue & atValue, TRUE);
#elif defined(xOS_LINUX)
    //TODO: xOS_LINUX
    xNOT_IMPLEMENTED_RET(FALSE);
#endif

    return FALSE;
}
//---------------------------------------------------------------------------



/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
//DONE: CxFileAttribute (comment)
CxFileAttribute::CxFileAttribute() {

}
//---------------------------------------------------------------------------
//DONE: ~CxFileAttribute (comment)
CxFileAttribute::~CxFileAttribute() {

}
//---------------------------------------------------------------------------
