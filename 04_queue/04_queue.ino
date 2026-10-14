#include <Arduino.h>

QueueHandle_t numberQueue;

void producerTask(void *parameter) {
  int value = 0;
  for (;;) {
    value++;
    if (xQueueSend(numberQueue, &value, portMAX_DELAY) == pdPASS) {
      Serial.printf("Sent: %d\n", value);
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void consumerTask(void *parameter) {
  int value;
  for (;;) {
    if (xQueueReceive(numberQueue, &value, portMAX_DELAY) == pdPASS) {
      Serial.printf("Received: %d\n", value);
    }
  }
}

void setup() {
  Serial.begin(115200);
  numberQueue = xQueueCreate(5, sizeof(int));
  if (numberQueue == nullptr) {
    Serial.println("Queue creation failed");
    while (true) vTaskDelay(pdMS_TO_TICKS(1000));
  }
  xTaskCreate(producerTask, "Producer", 2048, nullptr, 1, nullptr);
  xTaskCreate(consumerTask, "Consumer", 2048, nullptr, 1, nullptr);
}

void loop() { vTaskDelay(pdMS_TO_TICKS(1000)); }
