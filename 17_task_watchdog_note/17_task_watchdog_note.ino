#include <Arduino.h>
#include <esp_task_wdt.h>

// Demonstration only. Watchdog APIs and initialization defaults vary by
// Arduino-ESP32 core version. Do not reconfigure the global watchdog blindly.
void healthyTask(void *parameter) {
  // On cores where the current task must be registered explicitly, initialize
  // or add this task using the API appropriate for your installed core version.
  for (;;) {
    Serial.println("Watchdog demo task is alive");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreate(healthyTask, "HealthyTask", 3072, nullptr, 1, nullptr);
  Serial.println("This example demonstrates a watchdog-friendly task pattern.");
  Serial.println("Avoid infinite loops that never yield or block.");
}

void loop() { vTaskDelay(pdMS_TO_TICKS(1000)); }
