#!/bin/bash

BRANCH=$(git rev-parse --abbrev-ref HEAD)
echo "${BRANCH}"

if [ "main" = "${BRANCH}" ]
then
	git rebase -i envoy/main
	exit 0
fi

if [ "kafka-mesh-public" = "${BRANCH}" ]
then
	git rebase -i HEAD~5
	exit 0
fi

git rebase -i github/${BRANCH}
