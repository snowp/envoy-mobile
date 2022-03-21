#include <string>

#include "library/common/jni/jni_support.h"
#include "library/common/jni/jni_interface.h"
#include "library/common/bridge/utility.h"
#include <thread>

// NOLINT(namespace-envoy)

extern "C" JNIEXPORT void JNICALL Java_test_java_integration_jni_TestJniLibrary_sendLotsOfEvents(
    JNIEnv* env, jclass, jobject event_tracker) {

  std::thread t([&]() {
    for (uint64_t i = 0; i < 1000000; ++i) {
      const auto event = Envoy::Bridge::Utility::makeEnvoyMap(
          {{"name", "some-name"}, {"location", "some-location"}});
      jvm_on_track(event, reinterpret_cast<const void*>(event_tracker));
    }
  });

  t.join();
}
