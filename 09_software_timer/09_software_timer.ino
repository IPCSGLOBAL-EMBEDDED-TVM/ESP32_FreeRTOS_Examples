#include <Arduino.h>

TimerHandle_t periodicTimer;

void timerCallback(TimerHandle_t timer) {
  Serial.println("Software timer callback");
}

void setup() {
  Serial.begin(115200);
  periodicTimer = xTimerCreate("Periodic", pdMS_TO_TICKS(2000), pdTRUE, nullptr, timerCallback);
  if (periodicTimer != nullptr) xTimerStart(periodicTimer, 0);
}

void loop() { vTaskDelay(pdMS_TO_TICKS(1000)); }
