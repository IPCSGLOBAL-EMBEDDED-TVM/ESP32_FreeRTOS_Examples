#include <Arduino.h>

void pinnedTask(void *parameter) {
  for (;;) {
    Serial.printf("Pinned task running on core %d\n", xPortGetCoreID());
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreatePinnedToCore(pinnedTask, "CoreTask", 2048, nullptr, 1, nullptr, 1);
}

void loop() {
  vTaskDelay(pdMS_TO_TICKS(1000));
}
