# See bazel/README.md for details on how this system works.
CONTRIB_EXTENSIONS = {
    #
    # HTTP filters
    #

    #
    # Network filters
    #

    "envoy.filters.network.kafka_broker":                       "//contrib/kafka/filters/network/source:kafka_broker_config_lib",
    "envoy.filters.network.kafka_mesh":                         "//contrib/kafka/filters/network/source/mesh:config_lib",

    #
    # Sip proxy
    #

    #
    # Private key providers
    #

    #
    # Socket interface extensions
    #

    #
    # Input matchers
    #

    #
    # Connection Balance extensions
    #

    #
    # Regex engines
    #

    #
    # Extensions for generic proxy
    #
    "envoy.filters.generic.router":                             "//contrib/generic_proxy/filters/network/source/router:config",
    "envoy.generic_proxy.codecs.dubbo":                         "//contrib/generic_proxy/filters/network/source/codecs/dubbo:config",

    #
    # xDS delegates
    #

}
