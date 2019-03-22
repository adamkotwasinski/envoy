#!/bin/bash

#tools/spelling/check_spelling_pedantic.py check source/extensions/filters/network/kafka
#tools/spelling/check_spelling_pedantic.py check test/extensions/filters/network/kafka
tools/spelling/check_spelling_pedantic.py check contrib/kafka/

export BUILDOZER_BIN=${HOME}/go/bin/buildozer
export BUILDIFIER_BIN=${HOME}/go/bin/buildifier
if [ -f '/usr/local/bin/clang-format' ]
then
	export CLANG_FORMAT=/usr/local/bin/clang-format
fi

#tools/code_format/check_format.py fix
#tools/code_format/check_format.py fix source/extensions/filters/network/kafka
#tools/code_format/check_format.py fix test/extensions/filters/network/kafka
tools/code_format/check_format.py fix contrib/kafka/

tools/code_format/check_format.py fix bazel/foreign_cc/BUILD

# got to fix python dependencies on my box
#bazel run //tools/code_format:python_check -- --fix `pwd`

