#include <Arduino.h>

const int LED_PIN = 2;

void blinkTask(void *parameter) {
  pinMode(LED_PIN, OUTPUT);
  for (;;) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreate(blinkTask, "BlinkTask", 2048, nullptr, 1, nullptr);
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
}
