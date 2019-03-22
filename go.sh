#!/bin/bash -e

./mtests.sh c

if [ $# -gt 0 ]; then
	echo "no log"
	./bazel-bin/contrib/exe/envoy-static -l info -c kafka-all.yaml --concurrency 4 2>&1
else
	stdbuf --output=L ./bazel-bin/contrib/exe/envoy-static -l info -c kafka-all.yaml --concurrency 4 2>&1 | tee logz
fi
