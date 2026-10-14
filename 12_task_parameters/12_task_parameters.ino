#include <Arduino.h>

struct TaskConfig {
  const char *label;
  uint32_t delayMs;
};

TaskConfig configA = {"A", 600};
TaskConfig configB = {"B", 1300};

void configuredTask(void *parameter) {
  TaskConfig *config = static_cast<TaskConfig *>(parameter);
  for (;;) {
    Serial.printf("Task %s: interval %lu ms\n", config->label, (unsigned long)config->delayMs);
    vTaskDelay(pdMS_TO_TICKS(config->delayMs));
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreate(configuredTask, "ConfigA", 2048, &configA, 1, nullptr);
  xTaskCreate(configuredTask, "ConfigB", 2048, &configB, 1, nullptr);
}

void loop() { vTaskDelay(pdMS_TO_TICKS(1000)); }
