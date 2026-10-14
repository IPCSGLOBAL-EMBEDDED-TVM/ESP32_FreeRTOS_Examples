#include <Arduino.h>

TaskHandle_t receiverHandle = nullptr;

void senderTask(void *parameter) {
  for (;;) {
    vTaskDelay(pdMS_TO_TICKS(1500));
    xTaskNotifyGive(receiverHandle);
  }
}

void receiverTask(void *parameter) {
  for (;;) {
    uint32_t count = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    Serial.printf("Notification received; count=%lu\n", (unsigned long)count);
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreate(receiverTask, "Receiver", 2048, nullptr, 1, &receiverHandle);
  xTaskCreate(senderTask, "Sender", 2048, nullptr, 1, nullptr);
}

void loop() { vTaskDelay(pdMS_TO_TICKS(1000)); }
