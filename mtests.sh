#!/bin/bash

GOALS=""
COMMAND="test"

while [ $# -ne 0 ]
do
	ARG="$1"
    case "${ARG}" in
		bi)
			echo "broker-integration"
			GOALS="${GOALS} //test/extensions/filters/network/kafka/broker/integration_test:kafka_broker_integration_test"
			;;
        mi)
			echo "mesh-integration"
            GOALS="${GOALS} //test/extensions/filters/network/kafka/mesh/integration_test:kafka_mesh_integration_test"
            ;;
		mt)
			echo "mesh-test"
			GOALS="${GOALS} //test/extensions/filters/network/kafka/mesh/..."
			;;
		mb)
			echo "mesh-build"
			COMMAND="build"
			GOALS="//source/extensions/filters/network/kafka/mesh/..."
			;;
		a)
			echo "all"
			GOALS="${GOALS} //test/extensions/filters/network/kafka/... //test/extensions/filters/network/kafka/broker/integration_test:kafka_broker_integration_test //test/extensions/filters/network/kafka/mesh/integration_test:kafka_mesh_integration_test"
			;;
    esac
    shift
done

echo "${GOALS}"

time bazel ${COMMAND} ${GOALS}
