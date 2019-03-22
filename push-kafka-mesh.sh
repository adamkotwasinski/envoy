#!/bin/bash
./push-master.sh
git push github HEAD~1:kafka-mesh-public --force; 
