licenses(["notice"])  # Apache 2

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_extension",
    "envoy_extension_package",
)

envoy_extension_package()

envoy_cc_extension(
    name = "config",
    srcs = [
        "config.cc",
    ],
    hdrs = [
        "config.h",
    ],
    category = "envoy.upstreams",
    security_posture = "robust_to_untrusted_downstream",
    visibility = ["//visibility:public"],
    deps = [
        "//source/extensions/upstreams/http/http:upstream_request_lib",
        "//source/extensions/upstreams/http/tcp:upstream_request_lib",
        "@envoy_api//envoy/extensions/upstreams/http/generic/v3:pkg_cc_proto",
    ],
)
