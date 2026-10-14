#include <Arduino.h>

EventGroupHandle_t systemEvents;
const EventBits_t SENSOR_READY = BIT0;
const EventBits_t WIFI_READY = BIT1;

void setupSensor(void *parameter) {
  vTaskDelay(pdMS_TO_TICKS(1000));
  Serial.println("Sensor initialized");
  xEventGroupSetBits(systemEvents, SENSOR_READY);
  vTaskDelete(nullptr);
}

void setupWifi(void *parameter) {
  vTaskDelay(pdMS_TO_TICKS(2000));
  Serial.println("Wi-Fi setup complete (demo)");
  xEventGroupSetBits(systemEvents, WIFI_READY);
  vTaskDelete(nullptr);
}

void monitorTask(void *parameter) {
  for (;;) {
    xEventGroupWaitBits(systemEvents, SENSOR_READY | WIFI_READY, pdFALSE, pdTRUE, portMAX_DELAY);
    Serial.println("Both prerequisites are ready");
    vTaskDelay(pdMS_TO_TICKS(3000));
  }
}

void setup() {
  Serial.begin(115200);
  systemEvents = xEventGroupCreate();
  xTaskCreate(setupSensor, "SensorInit", 2048, nullptr, 1, nullptr);
  xTaskCreate(setupWifi, "WiFiInit", 2048, nullptr, 1, nullptr);
  xTaskCreate(monitorTask, "Monitor", 2048, nullptr, 1, nullptr);
}

void loop() { vTaskDelay(pdMS_TO_TICKS(1000)); }
