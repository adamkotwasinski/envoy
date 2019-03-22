#!/bin/bash

BRANCH=$(git rev-parse --abbrev-ref HEAD)
echo "${BRANCH}"
if [ "kafka-mesh-public" = "${BRANCH}" ]
then
	echo "main"
	COMMITS=$(git log github/kafka-mesh-public..HEAD --format=%h)
	git reset --hard github/kafka-mesh-public
	git merge envoy/main
	for i in ${COMMITS}; do
		git cherry-pick ${i}
	done
fi
