licenses(["notice"])  # Apache 2

# Kafka network filter.
# Broker filter public docs: docs/root/configuration/network_filters/kafka_broker_filter.rst

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_extension",
    "envoy_cc_library",
    "envoy_package",
)
load("//bazel:envoy_internal.bzl", "envoy_external_dep_path")

envoy_package()

envoy_cc_extension(
    name = "config_lib",
    srcs = ["config.cc"],
    hdrs = ["config.h"],
    security_posture = "requires_trusted_downstream_and_upstream",
    status = "wip",
    deps = [
        ":filter_lib",
        ":clustering_lib",
        ":upstream_kafka_facade_lib",
        "//source/extensions/filters/network:well_known_names",
        "//source/extensions/filters/network/common:factory_base_lib",
        "@envoy_api//envoy/extensions/filters/network/kafka_mesh/v3:pkg_cc_proto",
    ],
)

envoy_cc_library(
    name = "filter_lib",
    srcs = ["filter.cc"],
    hdrs = [
        "filter.h",
    ],
    deps = [
        ":splitter_lib",
        ":clustering_lib",
        ":upstream_kafka_facade_lib",
        ":command_lib",
        "//source/extensions/filters/network/kafka:kafka_request_codec_lib",
        "//source/extensions/filters/network/kafka:kafka_response_codec_lib",
        "//include/envoy/buffer:buffer_interface",
        "//include/envoy/network:connection_interface",
        "//include/envoy/network:filter_interface",
        "//source/common/common:assert_lib",
        "//source/common/common:minimal_logger_lib",
    ],
)

envoy_cc_library(
    name = "splitter_lib",
    srcs = [
        "splitter.cc"
    ],
    hdrs = [
        "splitter.h",
    ],
    deps = [
    	":command_lib",
        "//source/extensions/filters/network/kafka:kafka_request_parser_lib",
        "//source/common/common:minimal_logger_lib",
    ],
)

envoy_cc_library(
    name = "command_lib",
    srcs = [
        "command.cc"
    ],
    hdrs = [
        "command.h",
    ],
    deps = [
        ":upstream_kafka_facade_lib",
        ":clustering_lib",
        "//source/extensions/filters/network/kafka:kafka_request_parser_lib",
        "//source/extensions/filters/network/kafka:kafka_response_parser_lib",
        "//source/common/common:minimal_logger_lib",
    ],
)

envoy_cc_library(
    name = "upstream_kafka_facade_lib",
    srcs = [
        "upstream_kafka_facade.cc"
    ],
    hdrs = [
        "upstream_kafka_facade.h",
    ],
    deps = [
        ":upstream_kafka_client_lib",
        "//source/common/common:minimal_logger_lib",
        "//include/envoy/thread:thread_interface",
        "//include/envoy/thread_local:thread_local_interface",
    ],
)

envoy_cc_library(
    name = "upstream_kafka_client_lib",
    srcs = [
        "upstream_kafka_client.cc"
    ],
    hdrs = [
        "upstream_kafka_client.h",
    ],
    deps = [
        "//source/common/common:minimal_logger_lib",
        "//include/envoy/event:dispatcher_interface",
        envoy_external_dep_path("librdkafka"),
    ],
)

envoy_cc_library(
    name = "clustering_lib",
    srcs = [
        "clustering.cc"
    ],
    hdrs = [
        "clustering.h",
    ],
    deps = [
        "@envoy_api//envoy/extensions/filters/network/kafka_mesh/v3:pkg_cc_proto",
        "//source/common/common:assert_lib",
        "//source/common/common:minimal_logger_lib",
    ],
)
