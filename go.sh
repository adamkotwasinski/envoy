#!/bin/bash

cp api/envoy/extensions/filters/network/kafka_mesh/v3alpha/kafka_mesh.proto generated_api_shadow/envoy/extensions/filters/network/kafka_mesh/v3alpha/kafka_mesh.proto

bazel build --jobs 7 //source/exe:envoy-static && ./bazel-bin/source/exe/envoy-static -l info -c kafka.yaml --concurrency 4
