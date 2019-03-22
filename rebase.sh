#!/bin/bash

BRANCH=$(git rev-parse --abbrev-ref HEAD)
echo "${BRANCH}"
if [ "kafka-mesh-public" = "${BRANCH}" ]
then
	echo "main"
	git rebase -i HEAD~4
else
	git rebase -i github/${BRANCH}
fi
