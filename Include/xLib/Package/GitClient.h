/**
 * \file  GitClient.h
 * \brief GIT client
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
namespace xl::package
{

class GitClient
    /// GIT client
{
public:
///\name ctors, dtor
///\{
             GitClient();
    virtual ~GitClient() = default;

    xNO_COPY_ASSIGN(GitClient);
///\}

	bool           isGitDir() const;
		///< check Git directory

///\name Repositories
///\{
	std::tstring_t repoUrl() const;
		///< get repo URL
	std::tstring_t repoUrlName() const;
		///< get repo URL name
	std::tstring_t repoName() const;
		///< get repository name

	void_t         remoteRepoNames(std::vec_tstring_t *repoNames) const;
		///< get remote repository names

	std::tstring_t gitlabRepoGroupName() const;
		///< Gitalb: get group repository name
///\}

///\name Branches
///\{
	std::tstring_t branchName() const;
		///< get brach name
	std::size_t    localBranchesNum() const;
		///< number of local branches
///\}

///\name Statuses
///\{
	std::tstring_t filesStatuses() const;
		///< get source files statuses
	void_t         commitsAheadBehind(std::size_t *aheadNum, std::size_t *behindNum) const;
		///< get number commits ahead behind
	std::size_t    stashesNum() const;
		///< get stashes number
	void_t         modifiedFiles(std::cvec_tstring_t &filterFileExts,
						std::vec_tstring_t *filePathes) const;
		///< get modified files
	void_t         trackedFiles(std::cvec_tstring_t &filterFileExts,
						std::vec_tstring_t *filePathes) const;
		///< get tracked files
	void_t         modifiedFilesLineFilter() const;
		///< get modified lines line filter (JSON)
///\}

private:
	std::ctstring_t _gitPath;

	std::tstring_t _binPath() const;
		///< path to binary file
	void_t         _gitExecute(std::cvec_tstring_t &params, std::tstring_t *stdOut,
	    				std::tstring_t *stdError) const;
		///< execute Git proccess
};

} // namespace
//-------------------------------------------------------------------------------------------------
