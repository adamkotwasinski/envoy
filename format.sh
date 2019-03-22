#!/bin/bash

export BUILDOZER_BIN=/Users/adam.kotwasinski/go/bin/buildozer
export BUILDIFIER_BIN=/usr/local/bin/buildifier
export CLANG_FORMAT=/usr/local/bin/clang-format
#tools/code_format/check_format.py fix
#tools/code_format/format_python_tools.sh fix

bazel run //tools/code_format:python_check -- --fix `pwd`
