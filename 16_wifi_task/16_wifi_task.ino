#include <Arduino.h>
#include <WiFi.h>

// Fill in your Wi-Fi credentials before uploading.
const char *WIFI_SSID = "YOUR_WIFI_NAME";
const char *WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

void wifiTask(void *parameter) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to Wi-Fi...");
    vTaskDelay(pdMS_TO_TICKS(500));
  }
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  for (;;) {
    Serial.printf("Wi-Fi status: %d\n", (int)WiFi.status());
    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}

void setup() {
  Serial.begin(115200);
  xTaskCreate(wifiTask, "WiFiTask", 4096, nullptr, 1, nullptr);
}

void loop() { vTaskDelay(pdMS_TO_TICKS(1000)); }
