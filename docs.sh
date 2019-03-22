#!/bin/bash -e

rm -rf ~/tmp/docs && bazel build //docs:html && mkdir ~/tmp/docs && tar -xzf bazel-bin/docs/html.tar.gz -C ~/tmp/docs && open ~/tmp/docs/index.html

