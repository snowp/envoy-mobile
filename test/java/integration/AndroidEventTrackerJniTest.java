package test.kotlin.integration;

import android.content.Context;
import androidx.test.core.app.ApplicationProvider;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.RobolectricTestRunner;
import test.java.integration.jni.TestJniLibrary;
import java.util.concurrent.atomic.AtomicInteger;

import static org.assertj.core.api.Assertions.assertThat;

// NOLINT(namespace-envoy)

@RunWith(RobolectricTestRunner.class)
public class AndroidEventTrackerJniTest {
//   static { TestJniLibrary.load(); }

  private final Context appContext = ApplicationProvider.getApplicationContext();

  @Test
  public void ensure_events_dont_leak() throws InterruptedException {
	   AtomicInteger count = new AtomicInteger();
	   TestJniLibrary.EventTracker t = (event) -> { count.incrementAndGet(); };
	   
	   System.out.println(System.getProperty("user.dir"));
	   System.out.println(System.getProperty("envoy_jni_library_name"));
	   System.out.println(System.getProperty("java.library.path"));
	   TestJniLibrary.load();
	   TestJniLibrary.sendLotsOfEvents(t);

    assertThat(count.get()).isEqualTo(1000);
  }
}
