licenses(["notice"])  # Apache 2

load(
    "//bazel:envoy_build_system.bzl",
    "envoy_package",
)
load("@rules_python//python:defs.bzl", "py_test")
load("@kafka_pip3//:requirements.bzl", "requirement")

envoy_package()

py_test(
    name = "kafka_mesh_integration_test",
    srcs = [
        "kafka_mesh_integration_test.py",
        "@kafka_python_client//:all",
    ],
    data = [
        "//source/exe:envoy-static",
        "//bazel:remote_jdk11",
        "@kafka_server_binary//:all",
    ] + glob(["*.j2"]),
    python_version = "PY3",
    srcs_version = "PY3",
    tags = ["manual"],
    deps = [
        requirement("Jinja2"),
        requirement("MarkupSafe"),
    ],
)
