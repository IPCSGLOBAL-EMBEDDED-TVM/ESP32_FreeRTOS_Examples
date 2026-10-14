#include <Arduino.h>

void periodicTask(void *parameter) {
  TickType_t lastWake = xTaskGetTickCount();
  const TickType_t period = pdMS_TO_TICKS(500);
  for (;;) {
    Serial.printf("Periodic action at %lu ms\n", (unsigned long)(millis()));
    vTaskDelayUntil(&lastWake, period);
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreate(periodicTask, "Periodic", 2048, nullptr, 1, nullptr);
}

void loop() { vTaskDelay(pdMS_TO_TICKS(1000)); }
