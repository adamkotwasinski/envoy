licenses(["notice"])  # Apache 2

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_test",
    "envoy_package",
)

envoy_package()

envoy_cc_test(
    name = "config_test",
    srcs = ["config_test.cc"],
    deps = [
        "//source/common/http/match_wrapper:config",
        "//test/mocks/server:factory_context_mocks",
        "//test/test_common:registry_lib",
    ],
)
