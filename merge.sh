#!/bin/bash
git checkout github/kafka-mesh-public && \
	git merge --no-edit envoy/main && \
	git cherry-pick main~3 main~2 main~1 main && \
	git branch -D main && \
	git checkout -b main
