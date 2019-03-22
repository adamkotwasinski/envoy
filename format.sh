#!/bin/bash

tools/spelling/check_spelling_pedantic.py check contrib/kafka/

export BUILDOZER_BIN=${HOME}/go/bin/buildozer
export BUILDOZER_PATH=${BUILDOZER_BIN}
export BUILDIFIER_BIN=${HOME}/go/bin/buildifier
export BUILDIFIER_PATH=${BUILDIFIER_BIN}
export CLANG_FORMAT=/opt/homebrew/bin/clang-format

#CF_ARGS="--buildifier_path=${BUILDIFIER_PATH} --buildozer_path=${BUILDOZER_PATH} --clang_format_path=${CLANG_FORMAT}"
#tools/code_format/check_format.py ${CF_ARGS} fix contrib/kafka
bazel run //tools/code_format:check_format -- fix contrib/kafka/

# got to fix python dependencies on my box
#bazel run //tools/code_format:python_check -- --fix `pwd`
