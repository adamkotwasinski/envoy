licenses(["notice"])  # Apache 2

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_package",
)

envoy_package()

filegroup(
    name = "configs",
    srcs = [
        "//examples/wasm-cc:configs",
    ] + glob(
        [
            "**/*.yaml",
            "**/*.lua",
            "_extra_certs/*.pem",
        ],
        exclude = [
            "cache/responses.yaml",
            "dynamic-config-fs/**/*",
            "jaeger-native-tracing/*",
            "**/*docker-compose*.yaml",
        ],
    ),
)
