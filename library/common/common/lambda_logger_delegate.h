#pragma once

#include <iostream>
#include <string>

#include "source/common/common/logger.h"

#include "absl/strings/string_view.h"
#include "library/common/api/external.h"
#include "envoy/config/typed_config.h"
#include "library/common/types/c_types.h"

namespace Envoy {
namespace Logger {

class LogSink {
public:
  virtual ~LogSink() = default;

  virtual void log(absl::string_view log) PURE;
  virtual void flush() PURE;
};
using LogSinkPtr = std::unique_ptr<LogSink>;

class LogSinkFactory : public Config::TypedFactory {
public:
  virtual LogSinkPtr createLogSink(const Protobuf::Message& config) PURE;

  std::string category() const override { return "envoy.mobile.log_sink"; }
};

class BaseSinkDelegate : public SinkDelegate {
public:
  explicit BaseSinkDelegate(DelegatingLogSinkSharedPtr log_sink,
                            std::vector<LogSinkPtr>&& log_sinks)
      : SinkDelegate(log_sink), event_tracker_(*static_cast<envoy_event_tracker*>(
                                    Api::External::retrieveApi(envoy_event_tracker_api_name))),
        log_sinks_(std::move(log_sinks)) {}

  // SinkDelegate
  void log(absl::string_view msg) override {
    for (const auto& sink : log_sinks_) {
      sink->log(msg);
    }
  }
  void logWithStableName(absl::string_view stable_name, absl::string_view level,
                         absl::string_view component, absl::string_view msg) override;
  void flush() override {
    for (const auto& sink : log_sinks_) {
      sink->flush();
    }
  }

private:
  envoy_event_tracker& event_tracker_;
  const std::vector<LogSinkPtr> log_sinks_;
};

using BaseSinkDelegatePtr = std::unique_ptr<BaseSinkDelegate>;
class LambdaDelegate : public LogSink {
public:
  LambdaDelegate(envoy_logger logger);

  // LogSink
  void log(absl::string_view msg) override;
  void flush() override {}

private:
  envoy_logger logger_;
};

// A default log delegate that logs to stderr, mimicking the default used by Envoy
// when no logger has been installed. Using this default delegate allows us to
// intercept the named log lines (used for analytic events) even if no platform
// logger has been installed.
class DefaultDelegate : public LogSink {
public:
  DefaultDelegate(absl::Mutex& mutex);

  // SinkDelegate
  void log(absl::string_view msg) override {
    absl::MutexLock l(&mutex_);
    std::cerr << msg;
  }
  void flush() override {
    absl::MutexLock l(&mutex_);
    std::cerr << std::flush;
  };

private:
  absl::Mutex& mutex_;
};

} // namespace Logger
} // namespace Envoy
