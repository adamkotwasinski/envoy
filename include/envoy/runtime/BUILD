licenses(["notice"])  # Apache 2

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_library",
    "envoy_package",
)

envoy_package()

envoy_cc_library(
    name = "runtime_interface",
    hdrs = ["runtime.h"],
    external_deps = [
        "abseil_node_hash_map",
        "abseil_optional",
    ],
    deps = [
        "//include/envoy/stats:stats_interface",
        "//include/envoy/thread_local:thread_local_object",
        "//source/common/common:assert_lib",
        "//source/common/singleton:threadsafe_singleton",
        "@envoy_api//envoy/type/v3:pkg_cc_proto",
    ],
)
