#!/bin/bash

BRANCH=$(git rev-parse --abbrev-ref HEAD)
echo "${BRANCH}"

if [ "main" = "${BRANCH}" ]
then
	echo "pushing main"
	git push github HEAD:refs/heads/main -f
	exit 0
fi

if [ "dev" = "${BRANCH}" ]
then
	echo "pushing dev"
	git push github HEAD:refs/heads/dev -f
	exit 0
fi

echo "pushing other branch"
git push github HEAD:refs/heads/${BRANCH}-dev -f
git push github HEAD~5:refs/heads/${BRANCH} -f
