/****************************************************************************
* Class name:  CxTest_CxDrive
* Description: test CxDrive
* File name:   CxTest_CxDrive.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     14.04.2010 11:03:19
*
*****************************************************************************/


#ifndef CxTest_CxDriveH
#define CxTest_CxDriveH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
#include <xLib/Debug/CxTest.h>
#include <xLib/Filesystem/Win/CxDrive.h>
//---------------------------------------------------------------------------
class CxTest_CxDrive : public CxTest {
	public:
		CxTest_CxDrive();
		virtual     ~CxTest_CxDrive();

	    virtual BOOL bUnit();

	private:
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//DONE: CxTest_CxDrive (constructor)
CxTest_CxDrive::CxTest_CxDrive() {
    bSetName(xT(xFUNCTION));
}
//---------------------------------------------------------------------------
//DONE: ~CxTest_CxDrive (destructor)
CxTest_CxDrive::~CxTest_CxDrive() {

}
//---------------------------------------------------------------------------
//TODO: bUnit ()
/*virtual*/
BOOL
CxTest_CxDrive::bUnit() {
    const tString  g_csDrivePathWithSlash         = xT("Z:\\");
    const tString  g_csDrivePathWithoutSlash      = xT("Z:");
    const tString  g_csFilePath                   = xT("C:\\Test.txt");
    const tString  g_csNewFilePath                = xT("C:\\New.Test.txt");
    const tString  g_csBakFilePath                = xT("C:\\Test_Static.txt.bak");
    const tString  g_csFilePathSt                 = xT("C:\\Test_Static.txt");
    ULONGLONG      g_ulFreeBytesAvailableToCaller;
    ULONGLONG      g_ulTotalNumberOfBytes;
    ULONGLONG      g_ulTotalNumberOfFreeBytes;

	//-------------------------------------
	//bIsReady
	m_bRes = CxDrive::bIsReady(g_csDrivePathWithSlash);
	xASSERT(TRUE == m_bRes);

	//-------------------------------------
	//bIsEmpty
	m_bRes = CxDrive::bIsEmpty(g_csDrivePathWithSlash);
	xASSERT(FALSE == m_bRes);

	//-------------------------------------
	//bGetFreeSpace
	m_bRes = CxDrive::bGetFreeSpace(g_csDrivePathWithSlash, &g_ulFreeBytesAvailableToCaller, &g_ulTotalNumberOfBytes, &g_ulTotalNumberOfFreeBytes);
	xASSERT(TRUE == m_bRes);

	//-------------------------------------
	//dtGetType
    CxDrive::EType g_dtRes = CxDrive::dtGetType(g_csDrivePathWithoutSlash);

	//-------------------------------------
	//dtGetType
	tString szVolumeName;
	ULONG   ulVolumeSerialNumber     = 0;
	ULONG   ulMaximumComponentLength = 0;
	ULONG   ulFileSystemFlags        = 0;
	tString sFileSystemName;

	m_bRes = CxDrive::bGetInfo(
						g_csDrivePathWithoutSlash,
						&szVolumeName,
						&ulVolumeSerialNumber,
						&ulMaximumComponentLength,
						&ulFileSystemFlags,
						&sFileSystemName);
	xASSERT(TRUE == m_bRes);

	//-------------------------------------
	//bGetLogicalDrives
	{
		std::vector<tString> vecsDrives;

		m_bRes = CxDrive::bGetLogicalDrives(&vecsDrives);
		xASSERT(TRUE == m_bRes);
	}

	//-------------------------------------
	//bGetLogicalDrives2
	{
		std::vector<tString> vecsDrives;

		m_bRes = CxDrive::bGetLogicalDrives(&vecsDrives, CxDrive::dtFixed);
		xASSERT(TRUE == m_bRes);
	}

	//-------------------------------------
	//bDefineDosDevice
	{

	}

	//-------------------------------------
	//bDeleteVolumeMountPoint
	{

	}

	//-------------------------------------
	//hFindFirstVolume
	{

	}

	//-------------------------------------
	//hFindFirstVolumeMountPoint
	{

	}

	//-------------------------------------
	//sFindNextVolume
	{

	}

	//-------------------------------------
	//bFindNextVolumeMountPoint
	{

	}

	//-------------------------------------
	//bFindVolumeClose
	{

	}

	//-------------------------------------
	//bFindVolumeMountPointClose
	{

	}

	//-------------------------------------
	//sGetLogicalStrings
	{

	}

	//-------------------------------------
	//sGetVolumeNameForVolumeMountPoint
	{

	}

	//-------------------------------------
	//sGetVolumePathName
	{

	}

	//-------------------------------------
	//sGetVolumePathNamesForVolumeName
	{

	}

	//-------------------------------------
	//sQueryDosDevice

	//-------------------------------------
	//bSetVolumeLabel
	{

	}

	//-------------------------------------
	//bSetVolumeMountPoint
	{

	}

    return TRUE;
}
//---------------------------------------------------------------------------
#endif //CxTest_CxDriveH

