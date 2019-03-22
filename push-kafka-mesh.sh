#!/bin/bash
./push-master.sh
git push github HEAD~3:kafka-mesh-public --force;
