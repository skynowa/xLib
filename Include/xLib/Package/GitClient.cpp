/**
 * \file  GitClient.cpp
 * \brief GIT client
 */


#include "GitClient.h"


namespace xl::package
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
GitClient::GitClient()
{
}
//-------------------------------------------------------------------------------------------------
GitClient::~GitClient()
{
}
//-------------------------------------------------------------------------------------------------
bool
GitClient::isGitDir() const
{
	std::cvec_tstring_t params {"rev-parse", "--git-dir"};
	std::tstring_t      stdOut;
	std::tstring_t      stdError;

	Process::execute(_gitPath(), params, {}, xTIMEOUT_INFINITE, &stdOut, &stdError);
	xCHECK_RET(!stdError.empty(), false);
	xCHECK_RET((stdOut.find(xT(".git")) == std::tstring_t::npos), false);

	return true;
}
//-------------------------------------------------------------------------------------------------
/**
 * HTTP(s)/Git proto
 *
 * - git@bitbucket.org:skynowa/faq.git
 * - ssh://git@gitlab.maklai.dev:8999/suppliers/services-sync.git
 * - ssh://git@stash.fabrica.net.ua:7999/trav/booked.git
 *
 * - https://github.com/FIvanO/PocketBookTest
 *
 * - https://skynowa@git.code.sf.net/p/x-lib/code
 */
std::tstring_t
GitClient::repoUrlName() const
{
	/// xCHECK_RET(!isGitDir(), xT(""));

	std::tstring_t sRv;

	std::cvec_tstring_t params {"config", "--get", "remote.origin.url"};
	std::tstring_t      stdOut;
	std::tstring_t      stdError;

	Process::execute(_gitPath(), params, {}, xTIMEOUT_INFINITE, &stdOut, &stdError);

	std::ctstring_t &url = String::trimSpace(stdOut);

	constexpr std::array protos
	{
		xT("git@"), 		// without protos
		xT("@git.code."),	// sourceforge.net
		xT("://")			// with protos
	};

	for (const auto &it_proto : protos) {
		xCHECK_DO(url.find(it_proto) == std::tstring_t::npos, continue);

		return String::cut(url, it_proto, xT(".")) ;
	}

	return {};
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
GitClient::repoName() const
{
	/// xCHECK_RET(!isGitDir(), xT(""));

	std::tstring_t sRv;

	std::cvec_tstring_t params {"rev-parse", "--show-toplevel"};
	std::tstring_t      stdOut;
	std::tstring_t      stdError;

	Process::execute(_gitPath(), params, {}, xTIMEOUT_INFINITE, &stdOut, &stdError);

	sRv = String::trimSpace( Path(stdOut).fileBaseName() );

	return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
GitClient::branchName() const
{
	/// xCHECK_RET(!isGitDir(), xT(""));

	std::tstring_t sRv;

	std::cvec_tstring_t params {"rev-parse", "--abbrev-ref", "HEAD"};
	std::tstring_t      stdOut;
	std::tstring_t      stdError;

	Process::execute(_gitPath(), params, {}, xTIMEOUT_INFINITE, &stdOut, &stdError);

	if      ( stdOut.empty() ) {
		sRv = xT("");
	}
	else if (stdOut == xT("HEAD")) {
		sRv = xT("detached●");
	}
	else {
		sRv = stdOut;
	}

	sRv = String::trimSpace(sRv);

	return sRv;
}
//-------------------------------------------------------------------------------------------------
std::size_t
GitClient::localBranchesNum() const
{
	/// xCHECK_RET(!isGitDir(), 0);

	std::cvec_tstring_t  params {"branch"};
	std::tstring_t       stdOut;
	std::tstring_t       stdError;

	Process::execute(_gitPath(), params, {}, xTIMEOUT_INFINITE, &stdOut, &stdError);

	std::vec_tstring_t values;
	String::split(String::trimSpace(stdOut), Const::nl(), &values);
	xCHECK_RET(values.empty(), 0);

	// without "master"
	return values.size() - 1;
}
//-------------------------------------------------------------------------------------------------
/**
 git_states=""

 get_git_states()
 {
	local status=`git status 2>&1 | tee`

	local nocommit=`echo  "${status}" 2> /dev/null | grep "nothing to commit" &> /dev/null; echo "$?"`
	local dirty=`echo     "${status}" 2> /dev/null | grep "modified:"         &> /dev/null; echo "$?"`
	local untracked=`echo "${status}" 2> /dev/null | grep "Untracked files"   &> /dev/null; echo "$?"`
	local newfile=`echo   "${status}" 2> /dev/null | grep "new file:"         &> /dev/null; echo "$?"`
	local renamed=`echo   "${status}" 2> /dev/null | grep "renamed:"          &> /dev/null; echo "$?"`
	local deleted=`echo   "${status}" 2> /dev/null | grep "deleted:"          &> /dev/null; echo "$?"`

	 git_states=""

	if [ "${nocommit}" == "0" ]; then
		git_states="✔"
	fi

	if [ "${renamed}" == "0" ]; then
		git_states="△${git_states}"
	fi

	if [ "${newfile}" == "0" ]; then
		git_states="+${git_states}"
	fi

	if [ "${untracked}" == "0" ]; then
		git_states="…${git_states}"
	fi

	if [ "${deleted}" == "0" ]; then
		git_states="✖${git_states}"
	fi

	if [ "${dirty}" == "0" ]; then
		git_states="●${git_states}"
	fi
 }
*/
std::tstring_t
GitClient::filesStatuses() const
{
	/// xCHECK_RET(!isGitDir(), xT(""));

	std::cvec_tstring_t params {"status"};
	std::tstring_t      stdOut;
	std::tstring_t      stdError;

	Process::execute(_gitPath(), params, {}, xTIMEOUT_INFINITE, &stdOut, &stdError);

	cbool_t isNoCommit  = StringCI::contains(stdOut, xT("nothing to commit"));
	cbool_t isModified  = StringCI::contains(stdOut, xT("modified:"));
	cbool_t isUntracked = StringCI::contains(stdOut, xT("Untracked files"));
	cbool_t isNew       = StringCI::contains(stdOut, xT("new file:"));
	cbool_t isRenamed   = StringCI::contains(stdOut, xT("renamed:"));
	cbool_t isDeleted   = StringCI::contains(stdOut, xT("deleted:"));

	std::tstring_t sRv;

	if (isNoCommit) {
		sRv += xT("✔");
	}

	if (isRenamed) {
		sRv += xT("△");
	}

	if (isNew) {
		sRv += xT("✚");
	}

	if (isUntracked) {
		sRv += xT("…");
	}

	if (isDeleted) {
		sRv += xT("✖");
	}

	if (isModified) {
		sRv += xT("●");
	}

	return sRv;
}
//-------------------------------------------------------------------------------------------------
/**
 find_git_ahead_behind()
 {
	if ! $(is_git); then
		git_ahead_behind=""
		return
	fi

	local status=$(git rev-list --left-right --count origin/master...$branch)
	local aheadRegex="([0-9]+)"
	local behindRegex="\s(\w+)$"

	[[ $status =~ $aheadRegex ]]  && ahead="${BASH_REMATCH[1]}"  || ahead="0"
	[[ $status =~ $behindRegex ]] && behind="${BASH_REMATCH[1]}" || behind="0"

??? [[ $(git status 2> /dev/null | tail -n1) != "nothing to commit, working tree clean" ]] && git_ahead_behind=""
	[[ $ahead != "0" ]]  && git_ahead_behind="↑${ahead}"
	[[ $behind != "0" ]] && git_ahead_behind="↓${behind}"
 }
*/
void_t
GitClient::commitsAheadBehind(
	std::size_t *out_aheadNum,	///< [out]
	std::size_t *out_behindNum	///< [out]
) const
{
	Utils::ptrAssignT(out_aheadNum,  std::size_t{});
	Utils::ptrAssignT(out_behindNum, std::size_t{});

	/// xCHECK_DO(!isGitDir(), return);

	std::cvec_tstring_t params {"rev-list", "--left-right", "--count", "origin/master..." + branchName()};
	std::tstring_t      stdOut;
	std::tstring_t      stdError;

	Process::execute(_gitPath(), params, {}, xTIMEOUT_INFINITE, &stdOut, &stdError);

	std::vec_tstring_t values;
	String::split(stdOut, Const::ht(), &values);
	if (values.size() != 2) {
		return;
	}

	Utils::ptrAssignT(out_aheadNum,  String::cast<std::size_t>(String::trimSpace(values[0])));
	Utils::ptrAssignT(out_behindNum, String::cast<std::size_t>(String::trimSpace(values[1])));
}
//-------------------------------------------------------------------------------------------------
std::size_t
GitClient::stashesNum() const
{
	/// xCHECK_RET(!isGitDir(), 0);

	std::cvec_tstring_t params {"stash", "list"};
	std::tstring_t      stdOut;
	std::tstring_t      stdError;

	Process::execute(_gitPath(), params, {}, xTIMEOUT_INFINITE, &stdOut, &stdError);

	std::vec_tstring_t values;
	String::split(String::trimSpace(stdOut), Const::nl(), &values);

	return values.size();
}
//-------------------------------------------------------------------------------------------------
void_t
GitClient::modifiedFiles(
	std::cvec_tstring_t &a_filterFileExts,	///<
	std::vec_tstring_t  *out_filePathes		///< [out]
) const
{
	xCHECK_DO(out_filePathes == nullptr, return);

	out_filePathes->clear();

	bool_t bRv {};

#if 0
def getGitModifiedFiles(self):
	"" Get current GIT modified files ""

	result = ""

	cmd_commit_diff = "git diff --name-only --cached --diff-filter=ACM".split()
	/// cmd_master_diff = "git diff --name-only master".split()

	cmd = cmd_commit_diff

	out = subprocess.Popen(cmd, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
	stdout,stderr = out.communicate()

	items = stdout.strip().decode("utf8").split("\n")

	for it_item in items:
		base,ext = os.path.splitext(it_item)
		if (ext in options.CPP_MASK):
			result += it_item.strip() + " "

	return result
#else
	/// xCHECK_RET(!isGitDir(), 0);

	std::cvec_tstring_t params {"diff", "--name-only", "--cached", "--diff-filter=ACM"};
	std::tstring_t      stdOut;
	std::tstring_t      stdError;

	Process::execute(_gitPath(), params, {}, xTIMEOUT_INFINITE, &stdOut, &stdError);

	std::vec_tstring_t values;
	String::split(String::trimSpace(stdOut), Const::nl(), &values);

	for (const auto &it_value : values) {
		std::ctstring_t &filePath = String::trimSpace(it_value);

		{
			std::ctstring_t &fileExt = Path(filePath).ext();

			bRv = Algos::isContains(a_filterFileExts, fileExt);
			xCHECK_DO(!bRv, continue);
		}

		out_filePathes->push_back(filePath);
	} // for (values)
#endif
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
GitClient::_gitPath() const
{
	static std::tstring_t sRv;
	if ( !sRv.empty() ) {
		return sRv;
	}

	std::ctstring_t gitName =
	#if   xENV_WIN
		xT("git.exe");
	#elif xENV_UNIX
		xT("git");
	#endif

	std::cvec_tstring_t dirPaths
	{
	#if   xENV_WIN
		// echo %Path%
		xT("c:\\Program Files (x86)\\Git\\bin")
	#elif xENV_UNIX
		// echo $PATH
		xT("/usr/bin"),
		xT("/usr/local/bin")
	#endif
	};

	cbool_t isRecursively {false};

	sRv = Finder::file(dirPaths, gitName, isRecursively);
	xTEST(!sRv.empty());

	return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
