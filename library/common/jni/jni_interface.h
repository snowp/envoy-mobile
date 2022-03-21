#pragma once

#include "library/common/api/c_types.h"

extern "C" JNIEXPORT void jvm_on_track(envoy_map events, const void* context);
