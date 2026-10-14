#include <Arduino.h>

SemaphoreHandle_t serialMutex;

void printTask(void *parameter) {
  const char *name = static_cast<const char *>(parameter);
  for (;;) {
    if (xSemaphoreTake(serialMutex, portMAX_DELAY) == pdTRUE) {
      Serial.printf("%s: protected shared Serial output\n", name);
      xSemaphoreGive(serialMutex);
    }
    vTaskDelay(pdMS_TO_TICKS(700));
  }
}

void setup() {
  Serial.begin(115200);
  serialMutex = xSemaphoreCreateMutex();
  xTaskCreate(printTask, "PrintA", 2048, (void *)"Task A", 1, nullptr);
  xTaskCreate(printTask, "PrintB", 2048, (void *)"Task B", 1, nullptr);
}

void loop() { vTaskDelay(pdMS_TO_TICKS(1000)); }
