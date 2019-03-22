#!/bin/bash
./push-master.sh
git push github HEAD~4:kafka-mesh-public --force;
