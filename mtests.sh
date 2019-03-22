#!/bin/bash

GOALS=""

echo "protocol"
#bazel test //test/extensions/filters/network/kafka/...

echo "mesh"
GOALS="${GOALS} //test/extensions/filters/network/kafka/mesh/..."

if [ "$#" -gt 0 ]
then
	echo "integration"
	GOALS="${GOALS} //test/extensions/filters/network/kafka/mesh/integration_test:kafka_mesh_integration_test"
fi

echo "${GOALS}"

time bazel test ${GOALS}
