#include <Arduino.h>

TaskHandle_t workerHandle = nullptr;

void workerTask(void *parameter) {
  for (;;) {
    Serial.println("Worker active");
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void controllerTask(void *parameter) {
  for (;;) {
    vTaskDelay(pdMS_TO_TICKS(3000));
    Serial.println("Suspending worker");
    vTaskSuspend(workerHandle);
    vTaskDelay(pdMS_TO_TICKS(2000));
    Serial.println("Resuming worker");
    vTaskResume(workerHandle);
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreate(workerTask, "Worker", 2048, nullptr, 1, &workerHandle);
  xTaskCreate(controllerTask, "Controller", 2048, nullptr, 1, nullptr);
}

void loop() { vTaskDelay(pdMS_TO_TICKS(1000)); }
