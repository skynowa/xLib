/**
 * \file  DirTemp.cpp
 * \brief DirTemp
 */


#include "DirTemp.h"

#if   xENV_WIN
    #include "Platform/Win/DirTemp_win.inl"
#elif xENV_UNIX
    // #include "Platform/Unix/DirTemp_unix.inl"
#endif


xNAMESPACE_BEGIN2(xl, fs)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
DirTemp::FileTemp(
	std::ctstring_t &a_dirPath,
    cbool_t          a_isAutoDelete
) :
    _dirPath     (a_dirPath),
    _isAutoDelete(a_isAutoDelete)
{
    xTEST(!a_dirPath.empty());
}
//-------------------------------------------------------------------------------------------------
/* virtual */
DirTemp::~FileTemp()
{
    if (_isAutoDelete && !_dirPath.empty()) {
        Dir(_dirPath).remove();
    }
}
//-------------------------------------------------------------------------------------------------
void_t
DirTemp::create()
{
   /**
    * The last six characters of template must be XXXXXX and
    * these are replaced with a string that makes the filename unique.
    * Since it will be modified, template must not be a string constant,
    * but should be declared as a character array
    */
    std::ctstring_t fileNameTemplate = xT("XXXXXX");

    _dirPath = Path(_dirPath).slashAppend() + Path(_dirPath).fileName() + fileNameTemplate;

    Dir(_dirPath).pathCreate();
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, fs)
