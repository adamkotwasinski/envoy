#!/bin/bash

ci/run_envoy_docker.sh 'ci/check_and_fix_format.sh'
#export BUILDIFIER_BIN=/usr/local/bin/buildifier
#export CLANG_FORMAT=/usr/local/bin/clang-format
#tools/check_format.py fix
#tools/proto_format.sh fix
