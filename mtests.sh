#!/bin/bash

GOALS=""
COMMAND="test"

while [ $# -ne 0 ]
do
	ARG="$1"
	case "${ARG}" in
		c)
			echo "compile-source-only"
			COMMAND="build"
			GOALS="${GOALS} //contrib/exe:envoy-static"
			;;
		s)
			echo "serialization"
			GOALS="${GOALS} //contrib/kafka/filters/network/test:serialization_test"
			;;
		p)
			echo "protocol"
			GOALS="${GOALS} //contrib/kafka/filters/network/test:responses_test //contrib/kafka/filters/network/test:requests_test"
			;;
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
			GOALS="//contrib/kafka/filters/network/source/mesh/..."
			;;
		a)
			echo "all"
			GOALS="${GOALS} //contrib/kafka/filters/network/test/..."
			;;
    esac
    shift
done

echo "${GOALS}"

if [ "$(uname)" == "Darwin" ]; then
	DEF_JC=6
else
	DEF_JC=4
fi

time bazel ${COMMAND} ${GOALS} --jobs ${JC:-${DEF_JC}}
