#!/bin/bash

LAST_MERGE=$(git log :/^Merge | head -1 | cut -f2 -d' ')

git rebase -ip ${LAST_MERGE}
