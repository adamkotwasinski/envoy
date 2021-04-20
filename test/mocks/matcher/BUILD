licenses(["notice"])  # Apache 2

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_mock",
    "envoy_package",
)

envoy_package()

envoy_cc_mock(
    name = "matcher_mocks",
    hdrs = ["mocks.h"],
    deps = [
        "//source/common/matcher:matcher_lib",
    ],
)
