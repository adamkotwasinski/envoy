#!/bin/bash

bazel build --jobs 7 //source/exe:envoy-static && ./bazel-bin/source/exe/envoy-static -l info -c ~/space-envoy/kafka-protocol-tests/kafka.yaml
