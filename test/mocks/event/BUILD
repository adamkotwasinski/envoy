licenses(["notice"])  # Apache 2

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_mock",
    "envoy_cc_test_library",
    "envoy_package",
)

envoy_package()

envoy_cc_mock(
    name = "event_mocks",
    srcs = ["mocks.cc"],
    hdrs = ["mocks.h"],
    deps = [
        "//include/envoy/event:deferred_deletable",
        "//include/envoy/event:dispatcher_interface",
        "//include/envoy/event:file_event_interface",
        "//include/envoy/event:scaled_range_timer_manager_interface",
        "//include/envoy/event:signal_interface",
        "//include/envoy/event:timer_interface",
        "//include/envoy/network:connection_handler_interface",
        "//include/envoy/network:connection_interface",
        "//include/envoy/network:dns_interface",
        "//include/envoy/network:listener_interface",
        "//include/envoy/ssl:context_interface",
        "//test/mocks/buffer:buffer_mocks",
        "//test/test_common:test_time_lib",
    ],
)

envoy_cc_test_library(
    name = "wrapped_dispatcher",
    hdrs = ["wrapped_dispatcher.h"],
    deps = [
        "//include/envoy/event:dispatcher_interface",
    ],
)
