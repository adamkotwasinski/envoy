#!/bin/bash

tools/spelling/check_spelling_pedantic.py check source/extensions/filters/network/kafka
tools/spelling/check_spelling_pedantic.py check test/extensions/filters/network/kafka

export BUILDOZER_BIN=/Users/adam.kotwasinski/go/bin/buildozer
export BUILDIFIER_BIN=/usr/local/bin/buildifier
export CLANG_FORMAT=/usr/local/bin/clang-format
#tools/code_format/check_format.py fix
tools/code_format/check_format.py fix source/extensions/filters/network/kafka
tools/code_format/check_format.py fix test/extensions/filters/network/kafka

bazel run //tools/code_format:python_check -- --fix `pwd`
