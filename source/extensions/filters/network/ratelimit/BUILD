licenses(["notice"])  # Apache 2

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_extension",
    "envoy_cc_library",
    "envoy_extension_package",
)

# Ratelimit L4 network filter
# Public docs: docs/root/configuration/network_filters/rate_limit_filter.rst

envoy_extension_package()

envoy_cc_library(
    name = "ratelimit_lib",
    srcs = ["ratelimit.cc"],
    hdrs = ["ratelimit.h"],
    # Legacy test use. TODO(#9953) clean up.
    visibility = [
        "//source/extensions:__subpackages__",
        "//test/common/network:__pkg__",
        "//test/extensions:__subpackages__",
    ],
    deps = [
        "//include/envoy/network:connection_interface",
        "//include/envoy/network:filter_interface",
        "//include/envoy/ratelimit:ratelimit_interface",
        "//include/envoy/runtime:runtime_interface",
        "//include/envoy/stats:stats_macros",
        "//source/common/tracing:http_tracer_lib",
        "//source/extensions/filters/common/ratelimit:ratelimit_client_interface",
        "//source/extensions/filters/network:well_known_names",
        "@envoy_api//envoy/extensions/filters/network/ratelimit/v3:pkg_cc_proto",
    ],
)

envoy_cc_extension(
    name = "config",
    srcs = ["config.cc"],
    hdrs = ["config.h"],
    category = "envoy.filters.network",
    security_posture = "robust_to_untrusted_downstream",
    deps = [
        "//include/envoy/registry",
        "//source/common/config:utility_lib",
        "//source/common/protobuf:utility_lib",
        "//source/extensions/filters/common/ratelimit:ratelimit_client_interface",
        "//source/extensions/filters/common/ratelimit:ratelimit_lib",
        "//source/extensions/filters/network:well_known_names",
        "//source/extensions/filters/network/common:factory_base_lib",
        "//source/extensions/filters/network/ratelimit:ratelimit_lib",
        "@envoy_api//envoy/extensions/filters/network/ratelimit/v3:pkg_cc_proto",
    ],
)
