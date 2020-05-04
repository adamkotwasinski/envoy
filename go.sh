#!/bin/bash

bazel build --jobs 7 //source/exe:envoy-static && ./bazel-bin/source/exe/envoy-static -l info -c kafka.yaml --concurrency 4
