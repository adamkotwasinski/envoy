# See bazel/README.md for details on how this system works.
EXTENSIONS = {
    #
    # Access loggers
    #

    #
    # Clusters
    #
    "envoy.clusters.kafka":                             "//source/extensions/clusters/kafka:kafka_cluster",

    #
    # Compression
    #

    #
    # gRPC Credentials Plugins
    #

    #
    # Health checkers
    #

    #
    # HTTP filters
    #

    #
    # Listener filters
    #

    # NOTE: The original_dst filter is implicitly loaded if original_dst functionality is
    #       configured on the listener. Do not remove it in that case or configs will fail to load.
    # NOTE: The proxy_protocol filter is implicitly loaded if proxy_protocol functionality is
    #       configured on the listener. Do not remove it in that case or configs will fail to load.

    #
    # Network filters
    #

    # WiP
    "envoy.filters.network.kafka_broker":               "//source/extensions/filters/network/kafka:kafka_broker_config_lib",
    "envoy.filters.network.kafka_mesh":                 "//source/extensions/filters/network/kafka:kafka_mesh_config_lib",
    "envoy.filters.network.tcp_proxy":                  "//source/extensions/filters/network/tcp_proxy:config",

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

}
