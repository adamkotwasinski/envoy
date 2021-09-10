# See bazel/README.md for details on how this system works.
EXTENSIONS = {
    #
    # Access loggers
    #

    #
    # Clusters
    #

    #
    # Compression
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
    # Generic Inputs
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
    # Transport sockets
    #

    "envoy.transport_sockets.upstream_proxy_protocol":  "//source/extensions/transport_sockets/proxy_protocol:upstream_config",
    "envoy.transport_sockets.raw_buffer":               "//source/extensions/transport_sockets/raw_buffer:config",

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
    # Quic extensions
    #

    #
    # Formatter
    #

    #
    # Key value store
    #

}

# These can be changed to ["//visibility:public"], for  downstream builds which
# need to directly reference Envoy extensions.
EXTENSION_CONFIG_VISIBILITY = ["//:extension_config"]
EXTENSION_PACKAGE_VISIBILITY = ["//:extension_library"]
