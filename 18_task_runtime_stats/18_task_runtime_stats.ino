#include <Arduino.h>

// ESP-IDF configuration and Arduino core build options affect runtime stats.
// This portable example reports basic task-system information.
void infoTask(void *parameter) {
  for (;;) {
    Serial.printf("Free heap: %u bytes; minimum free heap: %u bytes\n",
                  (unsigned)ESP.getFreeHeap(),
                  (unsigned)ESP.getMinFreeHeap());
    Serial.printf("Current task: %s\n", pcTaskGetName(nullptr));
    vTaskDelay(pdMS_TO_TICKS(3000));
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreate(infoTask, "SystemInfo", 3072, nullptr, 1, nullptr);
}

void loop() { vTaskDelay(pdMS_TO_TICKS(1000)); }
