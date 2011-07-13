#include <XLib2/CXApp.h>
#include "CMyCDlg.h"
//---------------------------------------------------------------------------
class CMyApp : public CXApp {
	CMyCDlg *m_pMainDlg;

	/*virtual */INT InitInstance();
	/*virtual */INT Run();
};
//---------------------------------------------------------------------------