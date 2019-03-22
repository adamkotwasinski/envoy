#!/bin/bash

./mtests.sh c && \
./bazel-bin/contrib/exe/envoy-static -l info -c kafka-all.yaml --concurrency 4 2>&1 | \
	grep -v 'API features marked as work-in-progress are not considered stable'
