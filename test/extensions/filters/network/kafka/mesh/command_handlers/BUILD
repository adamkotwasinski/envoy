licenses(["notice"])  # Apache 2

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_package",
)
load(
    "//test/extensions:extensions_build_system.bzl",
    "envoy_extension_cc_test",
)

envoy_package()

envoy_extension_cc_test(
    name = "api_versions_unit_test",
    srcs = ["api_versions_unit_test.cc"],
    extension_name = "envoy.filters.network.kafka_mesh",
    tags = ["skip_on_windows"],
    deps = [
        "//source/extensions/filters/network/kafka/mesh/command_handlers:api_versions_lib",
        "//test/mocks/network:network_mocks",
        "//test/mocks/stats:stats_mocks",
    ],
)

envoy_extension_cc_test(
    name = "metadata_unit_test",
    srcs = ["metadata_unit_test.cc"],
    extension_name = "envoy.filters.network.kafka_mesh",
    tags = ["skip_on_windows"],
    deps = [
        "//source/extensions/filters/network/kafka/mesh/command_handlers:metadata_lib",
        "//test/mocks/network:network_mocks",
        "//test/mocks/stats:stats_mocks",
    ],
)

envoy_extension_cc_test(
    name = "produce_unit_test",
    srcs = ["produce_unit_test.cc"],
    extension_name = "envoy.filters.network.kafka_mesh",
    tags = ["skip_on_windows"],
    deps = [
        "//source/extensions/filters/network/kafka/mesh/command_handlers:produce_lib",
        "//test/mocks/network:network_mocks",
        "//test/mocks/stats:stats_mocks",
    ],
)
