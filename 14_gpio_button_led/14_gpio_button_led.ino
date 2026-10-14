#include <Arduino.h>

const int BUTTON_PIN = 0; // Change to the button pin used by your board
const int LED_PIN = 2;

QueueHandle_t buttonQueue;

void buttonTask(void *parameter) {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  bool lastState = HIGH;
  for (;;) {
    bool state = digitalRead(BUTTON_PIN);
    if (state != lastState) {
      vTaskDelay(pdMS_TO_TICKS(30)); // simple debounce
      state = digitalRead(BUTTON_PIN);
      if (state != lastState) {
        lastState = state;
        if (state == LOW) {
          uint8_t event = 1;
          xQueueSend(buttonQueue, &event, 0);
        }
      }
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void ledTask(void *parameter) {
  pinMode(LED_PIN, OUTPUT);
  uint8_t event;
  for (;;) {
    if (xQueueReceive(buttonQueue, &event, portMAX_DELAY) == pdPASS) {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      Serial.println("Button event: LED toggled");
    }
  }
}

void setup() {
  Serial.begin(115200);
  buttonQueue = xQueueCreate(5, sizeof(uint8_t));
  xTaskCreate(buttonTask, "Button", 2048, nullptr, 2, nullptr);
  xTaskCreate(ledTask, "LED", 2048, nullptr, 1, nullptr);
}

void loop() { vTaskDelay(pdMS_TO_TICKS(1000)); }
