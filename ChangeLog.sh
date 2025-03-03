#!/bin/bash

LOGFILE="ChangeLog.md"

# Header
echo "# Merge Request Change log" > "$LOGFILE"
echo "" >> "$LOGFILE"

# Extract merge commits and format as Markdown
git log --merges --pretty=format:"## %s%n- **Commit:** [%h](https://your.git.repo/commit/%h)%n- **Author:** %an%n- **Date:** %cd%n" --date=short >> "$LOGFILE"

echo "Merge request change log saved to $LOGFILE"
