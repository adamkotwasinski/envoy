licenses(["notice"])  # Apache 2

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_extension",
    "envoy_extension_package",
)

# TCP proxy L4 network filter.
# Public docs: docs/root/configuration/network_filters/tcp_proxy_filter.rst

envoy_extension_package()

envoy_cc_extension(
    name = "config",
    srcs = ["config.cc"],
    hdrs = ["config.h"],
    category = "envoy.filters.network",
    security_posture = "robust_to_untrusted_downstream",
    # This is core Envoy config.
    visibility = ["//visibility:public"],
    deps = [
        "//include/envoy/registry",
        "//source/common/tcp_proxy",
        "//source/extensions/filters/network:well_known_names",
        "//source/extensions/filters/network/common:factory_base_lib",
        "@envoy_api//envoy/extensions/filters/network/tcp_proxy/v3:pkg_cc_proto",
    ],
)
