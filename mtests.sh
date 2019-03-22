#!/bin/bash

GOALS=""

while [ $# -ne 0 ]
do
    ARG="$1"
    case "${ARG}" in
		old)
			echo "kafka-general"
			GOALS="${GOALS} //test/extensions/filters/network/kafka/..."
			;;
		m)
			echo "mesh-unit"
			GOALS="${GOALS} //test/extensions/filters/network/kafka/mesh/..."
			;;
		mi)
			echo "mesh-integration"
			GOALS="${GOALS} //test/extensions/filters/network/kafka/mesh/integration_test:kafka_mesh_integration_test"
			;;
		all)
			echo "all"
			GOALS="${GOALS} //test/extensions/filters/network/kafka/... //test/extensions/filters/network/kafka/mesh/integration_test:kafka_mesh_integration_test"
			;;
    esac
    shift
done

echo "${GOALS}"

time bazel \
	test \
	--local_cpu_resources=5 \
	${GOALS}
