load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_extension",
    "envoy_cc_library",
    "envoy_extension_package",
)

licenses(["notice"])  # Apache 2

envoy_extension_package()

envoy_cc_library(
    name = "credential_injector_lib",
    srcs = ["credential_injector_filter.cc"],
    hdrs = ["credential_injector_filter.h"],
    deps = [
        "//envoy/server:filter_config_interface",
        "//source/common/http:header_map_lib",
        "//source/extensions/filters/http/common:pass_through_filter_lib",
        "//source/extensions/http/injected_credentials/common:credential_interface",
    ],
)

envoy_cc_extension(
    name = "config",
    srcs = ["config.cc"],
    hdrs = ["config.h"],
    visibility = ["//visibility:public"],
    deps = [
        ":credential_injector_lib",
        "//envoy/registry",
        "//source/common/config:utility_lib",
        "//source/common/protobuf:utility_lib",
        "//source/extensions/filters/http/common:factory_base_lib",
        "//source/extensions/http/injected_credentials/common:credential_config_interface",
        "@envoy_api//envoy/extensions/filters/http/credential_injector/v3:pkg_cc_proto",
    ],
)
