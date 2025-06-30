#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"

// Define a tag for logging
static const char *TAG = "minimal_app";

// Global variable
int global_value = 0;

// Setup function - runs once at the beginning
void setup() {
    global_value = 10;
    ESP_LOGI(TAG, "Setup complete. Global value initialized to: %d", global_value);
    printf("Hello from ESP32 setup!\\n"); // Also using printf for basic output
}

// Loop function - runs repeatedly
void loop() {
    static int loop_counter = 0; // Static local variable to retain value between calls

    loop_counter++;
    global_value += 5;

    ESP_LOGI(TAG, "Loop iteration: %d, Global value: %d", loop_counter, global_value);
    printf("Loop count: %d, Global: %d\\n", loop_counter, global_value);

    // Reset global_value if it gets too large, just for demonstration
    if (global_value > 100) {
        global_value = 0;
        ESP_LOGW(TAG, "Global value reset to 0");
    }

    vTaskDelay(pdMS_TO_TICKS(2000)); // Delay for 2000 milliseconds (2 seconds)
}

// Main application entry point for ESP-IDF
void app_main(void) {
    setup();
    while (1) {
        loop();
    }
} 