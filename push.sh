#!/bin/bash

BRANCH=$(git rev-parse --abbrev-ref HEAD)
echo "${BRANCH}"
if [ "kafka-mesh-public" = "${BRANCH}" ]
then
	echo "pushing main"
	git push github HEAD:refs/heads/main -f
	git push github HEAD:refs/heads/${BRANCH}-dev -f
	git push github HEAD~3:refs/heads/${BRANCH} -f
else
	echo "pushing dev"
	git push github HEAD:refs/heads/${BRANCH}-dev -f
	git push github HEAD~3:refs/heads/${BRANCH} -f
fi
