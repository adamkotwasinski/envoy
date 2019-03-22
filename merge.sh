#!/bin/bash
git checkout github/kafka-mesh-public && \
	git merge --no-edit envoy/main && \
	git cherry-pick master~3 master~2 master~1 master && \
	git branch -D master && \
	git checkout -b master
