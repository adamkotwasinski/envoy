#!/bin/bash

#BRANCH=$(git rev-parse --abbrev-ref HEAD)
#echo "${BRANCH}"

git rebase -i envoy/main
