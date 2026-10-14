#include <Arduino.h>

SemaphoreHandle_t eventSemaphore;

void signalTask(void *parameter) {
  for (;;) {
    vTaskDelay(pdMS_TO_TICKS(2000));
    xSemaphoreGive(eventSemaphore);
  }
}

void waitingTask(void *parameter) {
  for (;;) {
    if (xSemaphoreTake(eventSemaphore, portMAX_DELAY) == pdTRUE) {
      Serial.println("Event received: perform action");
    }
  }
}

void setup() {
  Serial.begin(115200);
  eventSemaphore = xSemaphoreCreateBinary();
  xTaskCreate(signalTask, "Signaller", 2048, nullptr, 1, nullptr);
  xTaskCreate(waitingTask, "Waiter", 2048, nullptr, 1, nullptr);
}

void loop() { vTaskDelay(pdMS_TO_TICKS(1000)); }
