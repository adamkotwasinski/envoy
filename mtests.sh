#!/bin/bash

echo "protocol"
#bazel test //test/extensions/filters/network/kafka/...
echo "mesh"
bazel test //test/extensions/filters/network/kafka/mesh/...

if [ "$#" -gt 0 ]
then
	echo "integration"
	bazel test //test/extensions/filters/network/kafka/mesh/integration_test:kafka_mesh_integration_test
fi
