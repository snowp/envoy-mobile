load("@rules_java//java:defs.bzl", "java_library")
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")
load("//bazel:kotlin_lib.bzl", "envoy_mobile_so_to_jni_lib")

licenses(["notice"])  # Apache 2

java_library(
    name = "test_jni_java_lib",
    srcs = [
        "TestJniLibrary.java",
    ],
    visibility = ["//visibility:public"],
    deps = [
    ],
)

cc_library(
    name = "test_jni_lib",
    srcs = [
        "test_jni_interface.cc",
    ],
    copts = ["-std=c++17"],
    visibility = ["//visibility:public"],
    linkopts = [
        "-lm",
        # "-llog",
        "-ldl",
    ] + select({
        "@envoy//bazel:dbg_build": ["-Wl,--build-id=sha1"],
        "//conditions:default": [],
    }),
    deps = [
        "//library/common/jni:libjava_jni_lib",
        "//library/common/jni:jni_utility_lib",
        # "//library/common/jni:ndk_jni_support",
    ],
    # We need this to ensure that we link this into the .so even though there are no code references.
    alwayslink = True,
)

# OS X binary (.jnilib) for JVM testing
envoy_mobile_so_to_jni_lib(
    name = "libtest_jni.jnilib",
    visibility = ["//visibility:public"],
    native_dep = "libtest_jni.so",
)

# Main dynamic library for the Envoy Mobile aar
cc_binary(
    name = "libtest_jni.so",
    copts = ["-std=c++17"],
    visibility = ["//visibility:public"],
    linkopts = [
        "-lm",
        # "-llog",
    ] + select({
        "@envoy//bazel:dbg_build": ["-Wl,--build-id=sha1"],
        "//conditions:default": [],
    }),
    linkshared = True,
    deps = [
        ":test_jni_lib",
    ],
)
