#!/bin/bash
./push-master.sh
git push github HEAD~2:kafka-mesh-public --force;
