# See bazel/README.md for details on how this system works.
EXTENSIONS = {
    #
    # Access loggers
    #


    #
    # Clusters
    #

    "envoy.clusters.static":                            "//source/extensions/clusters/static:static_cluster_lib",
    "envoy.clusters.strict_dns":                        "//source/extensions/clusters/strict_dns:strict_dns_cluster_lib",

    #
    # Compression
    #


    #
    # Config validators
    #

    #
    # gRPC Credentials Plugins
    #


    #
    # WASM
    #


    #
    # Health checkers
    #


    #
    # Input Matchers
    #


    #
    # Network Matchers
    #


    #
    # Generic Inputs
    #


    #
    # Matching actions
    #


    #
    # HTTP filters
    #


    #
    # Listener filters
    #

    # NOTE: The original_dst filter is implicitly loaded if original_dst functionality is
    #       configured on the listener. Do not remove it in that case or configs will fail to load.
    "envoy.filters.listener.original_dst":              "//source/extensions/filters/listener/original_dst:config",
    "envoy.filters.listener.original_src":              "//source/extensions/filters/listener/original_src:config",
    # NOTE: The proxy_protocol filter is implicitly loaded if proxy_protocol functionality is
    #       configured on the listener. Do not remove it in that case or configs will fail to load.
    "envoy.filters.listener.proxy_protocol":            "//source/extensions/filters/listener/proxy_protocol:config",

    #
    # Network filters
    #

    "envoy.filters.network.tcp_proxy":                            "//source/extensions/filters/network/tcp_proxy:config",

    #
    # UDP filters
    #


    #
    # UDP Session filters
    #


    #
    # Resource monitors
    #


    #
    # Stat sinks
    #


    #
    # Thrift filters
    #


    #
    # Tracers
    #


    #
    # OpenTelemetry Resource Detectors
    #

    "envoy.tracers.opentelemetry.resource_detectors.environment":         "//source/extensions/tracers/opentelemetry/resource_detectors/environment:config",

    #
    # OpenTelemetry tracer samplers
    #

    "envoy.tracers.opentelemetry.samplers.always_on":         "//source/extensions/tracers/opentelemetry/samplers/always_on:config",

    #
    # Transport sockets
    #

    "envoy.transport_sockets.upstream_proxy_protocol":  "//source/extensions/transport_sockets/proxy_protocol:upstream_config",
    "envoy.transport_sockets.raw_buffer":               "//source/extensions/transport_sockets/raw_buffer:config",
    "envoy.transport_sockets.internal_upstream":        "//source/extensions/transport_sockets/internal_upstream:config",

    #
    # Retry host predicates
    #


    #
    # Retry priorities
    #


    #
    # CacheFilter plugins
    #

    #
    # Internal redirect predicates
    #


    #
    # Http Upstreams (excepting envoy.upstreams.http.generic which is hard-coded into the build so not registered here)
    #


    #
    # Watchdog actions
    #


    #
    # WebAssembly runtimes
    #


    #
    # Rate limit descriptors
    #


    #
    # IO socket
    #


    #
    # TLS peer certification validators
    #


    #
    # HTTP header formatters
    #


    #
    # Original IP detection
    #


    #
    # Stateful session
    #


    #
    # Custom response policies
    #


    #
    # QUIC extensions
    #


    #
    # UDP packet writers
    #

    #
    # Formatter
    #


    #
    # Key value store
    #


    #
    # RBAC matchers
    #


    #
    # DNS Resolver
    #

    # apple DNS resolver extension is only needed in MacOS build plus one want to use apple library for DNS resolving.
    "envoy.network.dns_resolver.apple":                "//source/extensions/network/dns_resolver/apple:config",

    #
    # Custom matchers
    #


    #
    # Header Validators
    #


    #
    # Path Pattern Match and Path Pattern Rewrite
    #
    #
    # Early Data option
    #


    #
    # Load balancing policies for upstream
    #
    "envoy.load_balancing_policies.round_robin":       "//source/extensions/load_balancing_policies/round_robin:config",

    # HTTP Early Header Mutation
    #

    #
    # Config Subscription
    #

    #
    # Geolocation Provider
    #
}

# These can be changed to ["//visibility:public"], for  downstream builds which
# need to directly reference Envoy extensions.
EXTENSION_CONFIG_VISIBILITY = ["//:extension_config", "//:contrib_library", "//:examples_library", "//:mobile_library"]
EXTENSION_PACKAGE_VISIBILITY = ["//:extension_library", "//:contrib_library", "//:examples_library", "//:mobile_library"]
CONTRIB_EXTENSION_PACKAGE_VISIBILITY = ["//:contrib_library"]
MOBILE_PACKAGE_VISIBILITY = ["//:mobile_library"]

# Set this variable to true to disable alwayslink for envoy_cc_library.
# TODO(alyssawilk) audit uses of this in source/ and migrate all libraries to extensions.
LEGACY_ALWAYSLINK = 1
