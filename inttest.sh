#!/bin/bash

#time bazel test //test/extensions/filters/network/kafka/broker/integration_test:kafka_broker_integration_test
time bazel test //test/extensions/filters/network/kafka/mesh/integration_test:kafka_mesh_integration_test
