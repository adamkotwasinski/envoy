# See bazel/README.md for details on how this system works.
EXTENSIONS = {
    #
    # Access loggers
    #


    #
    # Clusters
    #

    "envoy.clusters.aggregate":                         "//source/extensions/clusters/aggregate:cluster",
    "envoy.clusters.dynamic_forward_proxy":             "//source/extensions/clusters/dynamic_forward_proxy:cluster",
    "envoy.clusters.eds":                               "//source/extensions/clusters/eds:eds_lib",
    "envoy.clusters.redis":                             "//source/extensions/clusters/redis:redis_cluster",
    "envoy.clusters.static":                            "//source/extensions/clusters/static:static_cluster_lib",
    "envoy.clusters.strict_dns":                        "//source/extensions/clusters/strict_dns:strict_dns_cluster_lib",
    "envoy.clusters.original_dst":                      "//source/extensions/clusters/original_dst:original_dst_cluster_lib",
    "envoy.clusters.logical_dns":                       "//source/extensions/clusters/logical_dns:logical_dns_cluster_lib",

    #
    # Compression
    #


    #
    # Config validators
    #

    "envoy.config.validators.minimum_clusters_validator":     "//source/extensions/config/validators/minimum_clusters:config",

    #
    # gRPC Credentials Plugins
    #

    "envoy.grpc_credentials.file_based_metadata":       "//source/extensions/grpc_credentials/file_based_metadata:config",
    "envoy.grpc_credentials.aws_iam":                   "//source/extensions/grpc_credentials/aws_iam:config",

    #
    # WASM
    #

    "envoy.bootstrap.wasm":                             "//source/extensions/bootstrap/wasm:config",

    #
    # Health checkers
    #

    "envoy.health_checkers.redis":                      "//source/extensions/health_checkers/redis:config",
    "envoy.health_checkers.thrift":                     "//source/extensions/health_checkers/thrift:config",

    #
    # Input Matchers
    #

    "envoy.matching.matchers.consistent_hashing":       "//source/extensions/matching/input_matchers/consistent_hashing:config",
    "envoy.matching.matchers.ip":                       "//source/extensions/matching/input_matchers/ip:config",

    #
    # Generic Inputs
    #

    "envoy.matching.common_inputs.environment_variable":       "//source/extensions/matching/common_inputs/environment_variable:config",

    #
    # Matching actions
    #

    "envoy.matching.actions.format_string":             "//source/extensions/matching/actions/format_string:config",

    #
    # HTTP filters
    #


    #
    # Listener filters
    #

    "envoy.filters.listener.http_inspector":            "//source/extensions/filters/listener/http_inspector:config",
    # NOTE: The original_dst filter is implicitly loaded if original_dst functionality is
    #       configured on the listener. Do not remove it in that case or configs will fail to load.
    "envoy.filters.listener.original_dst":              "//source/extensions/filters/listener/original_dst:config",
    "envoy.filters.listener.original_src":              "//source/extensions/filters/listener/original_src:config",
    # NOTE: The proxy_protocol filter is implicitly loaded if proxy_protocol functionality is
    #       configured on the listener. Do not remove it in that case or configs will fail to load.
    "envoy.filters.listener.proxy_protocol":            "//source/extensions/filters/listener/proxy_protocol:config",
    "envoy.filters.listener.tls_inspector":             "//source/extensions/filters/listener/tls_inspector:config",

    #
    # Network filters
    #

    "envoy.filters.network.connection_limit":                     "//source/extensions/filters/network/connection_limit:config",
    "envoy.filters.network.direct_response":                      "//source/extensions/filters/network/direct_response:config",
    "envoy.filters.network.echo":                                 "//source/extensions/filters/network/echo:config",
    "envoy.filters.network.ratelimit":                            "//source/extensions/filters/network/ratelimit:config",
    "envoy.filters.network.rbac":                                 "//source/extensions/filters/network/rbac:config",
    "envoy.filters.network.tcp_proxy":                            "//source/extensions/filters/network/tcp_proxy:config",
    "envoy.filters.network.sni_cluster":                          "//source/extensions/filters/network/sni_cluster:config",
    "envoy.filters.network.sni_dynamic_forward_proxy":            "//source/extensions/filters/network/sni_dynamic_forward_proxy:config",

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

    "envoy.transport_sockets.alts":                     "//source/extensions/transport_sockets/alts:config",
    "envoy.transport_sockets.http_11_proxy":            "//source/extensions/transport_sockets/http_11_proxy:upstream_config",
    "envoy.transport_sockets.upstream_proxy_protocol":  "//source/extensions/transport_sockets/proxy_protocol:upstream_config",
    "envoy.transport_sockets.raw_buffer":               "//source/extensions/transport_sockets/raw_buffer:config",
    "envoy.transport_sockets.tap":                      "//source/extensions/transport_sockets/tap:config",
    "envoy.transport_sockets.starttls":                 "//source/extensions/transport_sockets/starttls:config",
    "envoy.transport_sockets.tcp_stats":                "//source/extensions/transport_sockets/tcp_stats:config",
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
    "envoy.extensions.http.cache.simple":               "//source/extensions/http/cache/simple_http_cache:config",

    #
    # Internal redirect predicates
    #

    "envoy.internal_redirect_predicates.allow_listed_routes": "//source/extensions/internal_redirect/allow_listed_routes:config",
    "envoy.internal_redirect_predicates.previous_routes":     "//source/extensions/internal_redirect/previous_routes:config",
    "envoy.internal_redirect_predicates.safe_cross_scheme":   "//source/extensions/internal_redirect/safe_cross_scheme:config",

    #
    # Http Upstreams (excepting envoy.upstreams.http.generic which is hard-coded into the build so not registered here)
    #

    "envoy.upstreams.http.http":                        "//source/extensions/upstreams/http/http:config",
    "envoy.upstreams.http.tcp":                         "//source/extensions/upstreams/http/tcp:config",

    #
    # Watchdog actions
    #

    "envoy.watchdog.profile_action":                    "//source/extensions/watchdog/profile_action:config",

    #
    # WebAssembly runtimes
    #


    #
    # Rate limit descriptors
    #

    "envoy.rate_limit_descriptors.expr":                "//source/extensions/rate_limit_descriptors/expr:config",

    #
    # IO socket
    #

    "envoy.io_socket.user_space":                       "//source/extensions/io_socket/user_space:config",
    "envoy.bootstrap.internal_listener":                "//source/extensions/bootstrap/internal_listener:config",

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
    "envoy.udp_packet_writer.default":                  "//source/extensions/udp_packet_writer/default:config",
    "envoy.udp_packet_writer.gso":                      "//source/extensions/udp_packet_writer/gso:config",

    #
    # Formatter
    #


    #
    # Key value store
    #

    "envoy.key_value.file_based":     "//source/extensions/key_value/file_based:config_lib",

    #
    # RBAC matchers
    #

    "envoy.rbac.matchers.upstream_ip_port":     "//source/extensions/filters/common/rbac/matchers:upstream_ip_port_lib",

    #
    # DNS Resolver
    #

    # c-ares DNS resolver extension is recommended to be enabled to maintain the legacy DNS resolving behavior.
    "envoy.network.dns_resolver.cares":                "//source/extensions/network/dns_resolver/cares:config",
    # apple DNS resolver extension is only needed in MacOS build plus one want to use apple library for DNS resolving.
    "envoy.network.dns_resolver.apple":                "//source/extensions/network/dns_resolver/apple:config",
    # getaddrinfo DNS resolver extension can be used when the system resolver is desired (e.g., Android)
    "envoy.network.dns_resolver.getaddrinfo":          "//source/extensions/network/dns_resolver/getaddrinfo:config",

    #
    # Custom matchers
    #

    "envoy.matching.custom_matchers.trie_matcher":     "//source/extensions/common/matcher:trie_matcher_lib",

    #
    # Header Validators
    #

    "envoy.http.header_validators.envoy_default":        "//source/extensions/http/header_validators/envoy_default:config",

    #
    # Path Pattern Match and Path Pattern Rewrite
    #
    "envoy.path.match.uri_template.uri_template_matcher": "//source/extensions/path/match/uri_template:config",
    "envoy.path.rewrite.uri_template.uri_template_rewriter": "//source/extensions/path/rewrite/uri_template:config",
    #
    # Early Data option
    #

    "envoy.route.early_data_policy.default":           "//source/extensions/early_data:default_early_data_policy_lib",
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
