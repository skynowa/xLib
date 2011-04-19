/****************************************************************************
* Class name:  CxFileAttribute
* Description: file attribute
* File name:   CxFileAttribute.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     06.04.2010 13:37:54
*
*****************************************************************************/


#ifndef xLib_Fso_CxFileAttributeH
#define xLib_Fso_CxFileAttributeH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxFileAttribute : public CxNonCopyable {
	public:
		//attributes
		enum EAttribute {
			faInvalid           = INVALID_FILE_ATTRIBUTES,
			faReadOnly          = FILE_ATTRIBUTE_READONLY,  
			faHidden            = FILE_ATTRIBUTE_HIDDEN, 
			faSystem            = FILE_ATTRIBUTE_SYSTEM,  
			faDirectory         = FILE_ATTRIBUTE_DIRECTORY,
			faArchive           = FILE_ATTRIBUTE_ARCHIVE,
			faDevice            = FILE_ATTRIBUTE_DEVICE,  
			faNormal            = FILE_ATTRIBUTE_NORMAL,  
			faTemporary         = FILE_ATTRIBUTE_TEMPORARY,  
			faSparseFile        = FILE_ATTRIBUTE_SPARSE_FILE,  
			faReparsePoint      = FILE_ATTRIBUTE_REPARSE_POINT,  
			faCompressed        = FILE_ATTRIBUTE_COMPRESSED,  
			faOffline           = FILE_ATTRIBUTE_OFFLINE,  
			faNotContentIndexed = FILE_ATTRIBUTE_NOT_CONTENT_INDEXED,
			faEncrypted         = FILE_ATTRIBUTE_ENCRYPTED 
		};

		static EAttribute atGet    		 (const tString &csFilePath);
		static BOOL       bSet     		 (const tString &csFilePath, EAttribute atValue);
		static BOOL       bAdd     		 (const tString &csFilePath, EAttribute atValue);
		static BOOL       bRemove  		 (const tString &csFilePath, EAttribute atValue);
		static BOOL       bModify  		 (const tString &csFilePath, EAttribute atRemoveValue, EAttribute atAddValue);
		static BOOL       bIsExists		 (const tString &csFilePath, EAttribute atValue);
	 
	private:
		                  CxFileAttribute();
		virtual          ~CxFileAttribute();		
};
//---------------------------------------------------------------------------
#endif //xLib_Fso_CxFileAttributeH
