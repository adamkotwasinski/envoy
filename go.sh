#!/bin/bash

./mtests.sh c && \
stdbuf --output=L ./bazel-bin/contrib/exe/envoy-static -l info -c kafka-all.yaml --concurrency 4 2>&1 | \
	tee logz
