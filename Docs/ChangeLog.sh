#!/usr/bin/env bash
#
# \file  ChangeLog.sh
# \brief Generate change log from MRs
#


LOGFILE="ChangeLog.md"
GIT_REPOSITORY="https://github.com/skynowa/xLib"

# Header
echo "# Change Log {#id_changelog}" > "$LOGFILE"
echo "" >> "$LOGFILE"

# Extract merge commits (those with PR references like #123) with description and format as Markdown
git log master \
  --grep="#[0-9]\+" \
  --pretty=format:"## %s%n%n- **Commit:** [%h](${GIT_REPOSITORY}/commit/%h)%n- **Author:** %an%n- **Date:** %cd%n%n%b%n" \
  --date=short >> "$LOGFILE"

echo "$LOGFILE - Saved"
