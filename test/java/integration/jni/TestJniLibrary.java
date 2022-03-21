package test.java.integration.jni;

import java.util.Map;

import java.nio.ByteBuffer;

public class TestJniLibrary {

  public static void load() {
	  System.loadLibrary("test_jni");
  }

  // TODO reuse
  public interface EventTracker {
    void track(Map<String, String> events);
  }

  public static native void sendLotsOfEvents(EventTracker event_tracker);
}
