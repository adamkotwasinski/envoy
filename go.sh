#!/bin/bash

cp api/envoy/config/filter/network/kafka_mesh/v2alpha1/kafka_mesh.proto generated_api_shadow/envoy/config/filter/network/kafka_mesh/v2alpha1/kafka_mesh.proto
cp api/envoy/extensions/filters/network/kafka_mesh/v3/kafka_mesh.proto generated_api_shadow/envoy/extensions/filters/network/kafka_mesh/v3/kafka_mesh.proto

bazel build --jobs 7 //source/exe:envoy-static && ./bazel-bin/source/exe/envoy-static -l info -c kafka.yaml --concurrency 4
