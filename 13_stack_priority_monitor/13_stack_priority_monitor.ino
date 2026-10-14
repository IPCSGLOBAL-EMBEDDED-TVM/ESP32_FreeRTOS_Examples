#include <Arduino.h>

TaskHandle_t monitorHandle;

void monitoredTask(void *parameter) {
  for (;;) {
    Serial.println("Monitored task working");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void monitorTask(void *parameter) {
  for (;;) {
    if (monitorHandle != nullptr) {
      UBaseType_t highWater = uxTaskGetStackHighWaterMark(monitorHandle);
      Serial.printf("Remaining stack high-water mark: %u words\n", (unsigned)highWater);
    }
    vTaskDelay(pdMS_TO_TICKS(3000));
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreate(monitoredTask, "Worker", 3072, nullptr, 1, &monitorHandle);
  xTaskCreate(monitorTask, "StackMonitor", 3072, nullptr, 1, nullptr);
}

void loop() { vTaskDelay(pdMS_TO_TICKS(1000)); }
