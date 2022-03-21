workspace(name = "envoy_mobile")

# The pgv imports require gazelle to be available early on.
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
http_archive(
    name = "bazel_gazelle",
    sha256 = "de69a09dc70417580aabf20a28619bb3ef60d038470c7cf8442fafcf627c21cb",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-gazelle/releases/download/v0.24.0/bazel-gazelle-v0.24.0.tar.gz",
        "https://github.com/bazelbuild/bazel-gazelle/releases/download/v0.24.0/bazel-gazelle-v0.24.0.tar.gz",
    ],
)

load("@envoy_mobile//bazel:envoy_mobile_repositories.bzl", "envoy_mobile_repositories")
envoy_mobile_repositories()

local_repository(
    name = "envoy",
    path = "envoy",
)

local_repository(
    name = "envoy_build_config",
    path = "envoy_build_config",
)

load("@envoy//bazel:api_binding.bzl", "envoy_api_binding")
envoy_api_binding()

load("@envoy//bazel:api_repositories.bzl", "envoy_api_dependencies")
envoy_api_dependencies()

load("@envoy//bazel:repositories.bzl", "envoy_dependencies")
envoy_dependencies()

load("@envoy//bazel:repositories_extra.bzl", "envoy_dependencies_extra")
envoy_dependencies_extra()

load("@envoy//bazel:dependency_imports.bzl", "envoy_dependency_imports")
envoy_dependency_imports()

load("@envoy_mobile//bazel:envoy_mobile_dependencies.bzl", "envoy_mobile_dependencies")
envoy_mobile_dependencies()

load("@envoy_mobile//bazel:envoy_mobile_toolchains.bzl", "envoy_mobile_toolchains")
envoy_mobile_toolchains()

load("@pybind11_bazel//:python_configure.bzl", "python_configure")
python_configure(name = "local_config_python", python_version = "3")

load("//bazel:python.bzl", "declare_python_abi")
declare_python_abi(name = "python_abi", python_version = "3")

load("//bazel:android_configure.bzl", "android_configure")
android_configure(
    name = "local_config_android",
    sdk_api_level = 29,
    ndk_api_level = 21,
    build_tools_version = "30.0.2"
)

load("@local_config_android//:android_configure.bzl", "android_workspace")
android_workspace()

ATS_COMMIT = "master"
http_archive(
    name = "android_test_support",
    strip_prefix = "android-test-%s" % ATS_COMMIT,
    urls = ["https://github.com/android/android-test/archive/%s.tar.gz" % ATS_COMMIT],
)
# load("@android_test_support//:repo.bzl", "android_test_repositories")
# android_test_repositories()

http_archive(
    name = "google_apputils",
    build_file = "@android_test_support//opensource:google-apputils.BUILD",
    sha256 = "47959d0651c32102c10ad919b8a0ffe0ae85f44b8457ddcf2bdc0358fb03dc29",
    strip_prefix = "google-apputils-0.4.2",
    url = "https://pypi.python.org/packages/69/66/a511c428fef8591c5adfa432a257a333e0d14184b6c5d03f1450827f7fe7/google-apputils-0.4.2.tar.gz",
)

http_archive(
    name = "portpicker_archive",
    build_file = "@android_test_support//opensource:portpicker.BUILD",
    sha256 = "2f88edf7c6406034d7577846f224aff6e53c5f4250e3294b1904d8db250f27ec",
    strip_prefix = "portpicker-1.1.1/src",
    url = "https://pypi.python.org/packages/96/48/0e1f20fdc0b85cc8722284da3c5b80222ae4036ad73210a97d5362beaa6d/portpicker-1.1.1.tar.gz",
)

http_archive(
    name = "gflags_archive",
    build_file = "@android_test_support//opensource:gflags.BUILD",
    sha256 = "3377d9dbeedb99c0325beb1f535f8fa9fa131d1d8b50db7481006f0a4c6919b4",
    strip_prefix = "python-gflags-3.1.0",
    url = "https://github.com/google/python-gflags/releases/download/3.1.0/python-gflags-3.1.0.tar.gz",
)
http_archive(
    name = "six_archive",
    build_file = "@android_test_support//opensource:six.BUILD",
    sha256 = "105f8d68616f8248e24bf0e9372ef04d3cc10104f1980f54d57b2ce73a5ad56a",
    strip_prefix = "six-1.10.0",
    url = "https://pypi.python.org/packages/source/s/six/six-1.10.0.tar.gz",
)
# Open source version of the google python flags library.
http_archive(
    name = "absl_py",
    sha256 = "980ce58c34dfa75a9d20d45c355658191c166557f1de41ab52f208bd00604c2b",
    strip_prefix = "abseil-py-b347ba6022370f895d3133241ed96965b95ecb40",
    urls = ["https://github.com/abseil/abseil-py/archive/b347ba6022370f895d3133241ed96965b95ecb40.tar.gz"],
)
