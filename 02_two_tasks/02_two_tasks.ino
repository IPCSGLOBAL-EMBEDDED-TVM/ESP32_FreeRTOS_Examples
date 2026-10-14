#include <Arduino.h>

void taskA(void *parameter) {
  for (;;) {
    Serial.println("Task A: core-independent periodic work");
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void taskB(void *parameter) {
  for (;;) {
    Serial.println("Task B: running concurrently");
    vTaskDelay(pdMS_TO_TICKS(1500));
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreate(taskA, "TaskA", 2048, nullptr, 1, nullptr);
  xTaskCreate(taskB, "TaskB", 2048, nullptr, 1, nullptr);
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
}
