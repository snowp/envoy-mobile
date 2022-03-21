load("@envoy//bazel:envoy_build_system.bzl", "envoy_cc_library", "envoy_package")
load("@com_github_google_flatbuffers//:build_defs.bzl", "flatbuffer_library_public", "flatbuffer_cc_library")
load("@rules_java//java:defs.bzl", "java_library")

licenses(["notice"])  # Apache 2

envoy_package()

envoy_cc_library(
    name = "c_types_lib",
    srcs = [
        "c_types.cc",
    ],
    hdrs = [
        "c_types.h",
    ],
    repository = "@envoy",
    visibility = ["//visibility:public"],
    deps = [
        "@envoy//source/common/common:assert_lib",
    ],
)

flatbuffer_cc_library(
    name = "types_cc_fbs",
    srcs = ["types.fbs"],
)

flatbuffer_library_public(
    name = "types_java_fbs_srcs",
    outs = ["types/Pair.java", "types/Map.java"],
    srcs = ["types.fbs"],
    language_flag = "-j",
)

java_library(
    name = "types_java_fbs",
    srcs = [":types_java_fbs_srcs"],
)
