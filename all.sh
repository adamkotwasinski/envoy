#!/bin/bash

bazel build --jobs 7 //source/exe:envoy-static
if [ $? -ne 0 ]
then
	echo "compile failed"
	exit 1
fi

kill-kafka
kill-zookeeper
ps -AF | grep 'exe/envoy-static' | grep -v 'grep' | tr -s ' ' | cut -f3 -d' ' | xargs kill -9

cd /Users/adam.kotwasinski/kenv/zk
./run.sh >/dev/null 2>/dev/null &

cd /Users/adam.kotwasinski/kenv/24
./run.sh 1 mesh >/dev/null 2>/dev/null &
./run.sh 2 mesh >/dev/null 2>/dev/null &

sleep 3

bin/kafka-topics.sh --zookeeper localhost:42181/m1 --topic apples --replication-factor 1 --partitions 1 --create
bin/kafka-topics.sh --zookeeper localhost:42181/m2 --topic bananas --replication-factor 1 --partitions 1 --create

cd /Users/adam.kotwasinski/space-envoy/envoy2

./bazel-bin/source/exe/envoy-static -l info -c kafka.yaml
