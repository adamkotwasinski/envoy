#!/bin/bash
./__push-main.sh
git push github HEAD~3:kafka-mesh-public --force;
