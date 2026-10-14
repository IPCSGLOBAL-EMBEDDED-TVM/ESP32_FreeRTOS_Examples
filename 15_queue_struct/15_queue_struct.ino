#include <Arduino.h>

struct SensorMessage {
  uint32_t sequence;
  float temperature;
  float humidity;
};

QueueHandle_t sensorQueue;

void sensorTask(void *parameter) {
  SensorMessage msg = {};
  for (;;) {
    msg.sequence++;
    msg.temperature = 24.0f + (msg.sequence % 10) * 0.25f; // simulated reading
    msg.humidity = 50.0f + (msg.sequence % 20) * 0.5f;
    xQueueSend(sensorQueue, &msg, portMAX_DELAY);
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void loggerTask(void *parameter) {
  SensorMessage msg;
  for (;;) {
    if (xQueueReceive(sensorQueue, &msg, portMAX_DELAY) == pdPASS) {
      Serial.printf("#%lu Temp=%.2f C Humidity=%.2f%%\n",
                    (unsigned long)msg.sequence, msg.temperature, msg.humidity);
    }
  }
}

void setup() {
  Serial.begin(115200);
  sensorQueue = xQueueCreate(8, sizeof(SensorMessage));
  xTaskCreate(sensorTask, "Sensor", 2048, nullptr, 1, nullptr);
  xTaskCreate(loggerTask, "Logger", 3072, nullptr, 1, nullptr);
}

void loop() { vTaskDelay(pdMS_TO_TICKS(1000)); }
