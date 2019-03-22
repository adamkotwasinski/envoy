#!/bin/bash

git push github HEAD:master --force && \
git push workday HEAD:master --force && \
git push github HEAD~5:refs/heads/kafka
