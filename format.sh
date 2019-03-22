#!/bin/bash

export BUILDIFIER_BIN=/usr/local/bin/buildifier
export CLANG_FORMAT=/usr/local/bin/clang-format
tools/check_format.py fix
tools/proto_format.sh fix
