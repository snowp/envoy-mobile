#include "library/common/common/lambda_logger_delegate.h"

#include <iostream>

#include "library/common/bridge/utility.h"
#include "library/common/data/utility.h"

namespace Envoy {
namespace Logger {

void BaseSinkDelegate::logWithStableName(absl::string_view stable_name, absl::string_view,
                                              absl::string_view, absl::string_view msg) {
  if (event_tracker_.track == nullptr) {
    return;
  }

  event_tracker_.track(Bridge::Utility::makeEnvoyMap({{"name", "event_log"},
                                                      {"log_name", std::string(stable_name)},
                                                      {"message", std::string(msg)}}),
                       event_tracker_.context);
}

LambdaDelegate::LambdaDelegate(envoy_logger logger)
    : logger_(logger) {
}

void LambdaDelegate::log(absl::string_view msg) {
  logger_.log(Data::Utility::copyToBridgeData(msg), logger_.context);
}

DefaultDelegate::DefaultDelegate(absl::Mutex& mutex)
    : mutex_(mutex) {
}

} // namespace Logger
} // namespace Envoy
