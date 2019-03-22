#!/bin/bash

GOALS=""
COMMAND="test"

while [ $# -ne 0 ]
do
	ARG="$1"
    case "${ARG}" in
		bi)
			echo "broker-integration"
			GOALS="${GOALS} //contrib/kafka/filters/network/test/broker/integration_test:kafka_broker_integration_test"
			;;
        mi)
			echo "mesh-integration"
            GOALS="${GOALS} //contrib/kafka/filters/network/test/mesh/integration_test:kafka_mesh_integration_test"
            ;;
		mt)
			echo "mesh-test"
			GOALS="${GOALS} //contrib/kafka/filters/network/test/mesh/..."
			;;
		mb)
			echo "mesh-build"
			COMMAND="build"
			GOALS="//source/extensions/filters/network/kafka/mesh/..."
			;;
		a)
			echo "all"
			GOALS="${GOALS} //contrib/kafka/filters/network/test/... //contrib/kafka/filters/network/test/broker/integration_test:kafka_broker_integration_test //contrib/kafka/filters/network/test/mesh/integration_test:kafka_mesh_integration_test"
			;;
    esac
    shift
done

echo "${GOALS}"

time bazel ${COMMAND} ${GOALS}
