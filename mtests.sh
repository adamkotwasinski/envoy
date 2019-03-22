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
		bb)
			echo "broker-build"
			COMMAND="build"
			GOALS="${GOALS} //contrib/kafka/filters/network/source/broker/..."
			;;
		bt)
			echo "broker-test"
			GOALS="${GOALS} //contrib/kafka/filters/network/test/broker/..."
			;;
		bi)
			echo "broker-integration"
			GOALS="${GOALS} //contrib/kafka/filters/network/test/broker/integration_test:kafka_broker_integration_test"
			;;
		mb)
			echo "mesh-build"
			COMMAND="build"
			GOALS="${GOALS} //contrib/kafka/filters/network/source/mesh/..."
			;;
		mt)
			echo "mesh-test"
			GOALS="${GOALS} //contrib/kafka/filters/network/test/mesh/..."
			;;
		mi)
			echo "mesh-integration"
			GOALS="${GOALS} //contrib/kafka/filters/network/test/mesh/integration_test:kafka_mesh_integration_test"
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
	DEF_JC=8
else
	DEF_JC=4
fi

time bazel ${COMMAND} ${GOALS} --jobs ${JC:-${DEF_JC}}
