#!/bin/bash -e

bazel build //contrib/kafka/filters/network/source:kafka_request_generated_source //contrib/kafka/filters/network/source:kafka_response_generated_source

cp -v bazel-out/darwin_arm64-fastbuild/bin/contrib/kafka/filters/network/source/external/requests.h .
cp -v bazel-out/darwin_arm64-fastbuild/bin/contrib/kafka/filters/network/source/external/responses.h .

git status
