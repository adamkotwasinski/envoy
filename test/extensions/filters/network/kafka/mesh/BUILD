licenses(["notice"])  # Apache 2

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_test_library",
    "envoy_package",
)
load(
    "//bazel:envoy_internal.bzl",
    "envoy_external_dep_path",
)
load(
    "//test/extensions:extensions_build_system.bzl",
    "envoy_extension_cc_test",
)

envoy_package()

envoy_extension_cc_test(
    name = "config_unit_test",
    srcs = ["config_unit_test.cc"],
    extension_name = "envoy.filters.network.kafka_mesh",
    tags = ["skip_on_windows"],
    deps = [
        "//source/extensions/filters/network/kafka/mesh:config_lib",
        "//test/mocks/server:factory_context_mocks",
    ],
)

envoy_extension_cc_test(
    name = "filter_unit_test",
    srcs = ["filter_unit_test.cc"],
    extension_name = "envoy.filters.network.kafka_mesh",
    tags = ["skip_on_windows"],
    deps = [
        "//source/extensions/filters/network/kafka/mesh:filter_lib",
        "//test/mocks/network:network_mocks",
    ],
)

envoy_extension_cc_test(
    name = "splitter_unit_test",
    srcs = ["splitter_unit_test.cc"],
    extension_name = "envoy.filters.network.kafka_mesh",
    tags = ["skip_on_windows"],
    deps = [
        "//source/extensions/filters/network/kafka/mesh:splitter_lib",
    ],
)

envoy_extension_cc_test(
    name = "upstream_kafka_facade_unit_test",
    srcs = ["upstream_kafka_facade_unit_test.cc"],
    extension_name = "envoy.filters.network.kafka_mesh",
    tags = ["skip_on_windows"],
    deps = [
        "//source/extensions/filters/network/kafka/mesh:upstream_kafka_facade_lib",
        "//test/mocks/thread_local:thread_local_mocks",
        "//test/test_common:thread_factory_for_test_lib",
    ],
)

envoy_extension_cc_test(
    name = "upstream_kafka_client_unit_test",
    srcs = ["upstream_kafka_client_unit_test.cc"],
    extension_name = "envoy.filters.network.kafka_mesh",
    tags = ["skip_on_windows"],
    deps = [
        ":kafka_mocks_lib",
        "//source/extensions/filters/network/kafka/mesh:upstream_kafka_client_lib",
        "//test/mocks/event:event_mocks",
        "//test/test_common:thread_factory_for_test_lib",
    ],
)

envoy_extension_cc_test(
    name = "clustering_unit_test",
    srcs = ["clustering_unit_test.cc"],
    extension_name = "envoy.filters.network.kafka_mesh",
    tags = ["skip_on_windows"],
    deps = [
        "//source/extensions/filters/network/kafka/mesh:clustering_lib",
    ],
)

envoy_extension_cc_test(
    name = "abstract_command_unit_test",
    srcs = ["abstract_command_unit_test.cc"],
    extension_name = "envoy.filters.network.kafka_mesh",
    tags = ["skip_on_windows"],
    deps = [
        "//source/extensions/filters/network/kafka/mesh:abstract_command_lib",
    ],
)

envoy_cc_test_library(
    name = "kafka_mocks_lib",
    srcs = [],
    hdrs = ["kafka_mocks.h"],
    tags = ["skip_on_windows"],
    deps = [
        envoy_external_dep_path("librdkafka"),
    ],
)
