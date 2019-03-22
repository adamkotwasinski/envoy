#!/bin/bash

echo "cleanup"
kill-kafka
kill-zookeeper
kill-envoy

echo "zookeeper"
cd /Users/adam.kotwasinski/kenv/zk
./run.sh >/dev/null 2>/dev/null &

echo "kafka"
cd /Users/adam.kotwasinski/kenv/27
./run.sh 1 mesh >/dev/null 2>/dev/null &
./run.sh 2 mesh >/dev/null 2>/dev/null &
./run.sh 3 mesh >/dev/null 2>/dev/null &

echo "sleeping"
sleep 5

echo "topics"
bin/kafka-topics.sh --zookeeper localhost:42181/m1 --topic apples --replication-factor 1 --partitions 1 --create
bin/kafka-topics.sh --zookeeper localhost:42181/m2 --topic bananas --replication-factor 1 --partitions 1 --create
bin/kafka-topics.sh --zookeeper localhost:42181/m3 --topic cherries --replication-factor 1 --partitions 5 --create

echo "envoy"
cd ~/space-envoy/envoy2
if [ "$#" -eq 0 ]; then
	./go.sh
fi
