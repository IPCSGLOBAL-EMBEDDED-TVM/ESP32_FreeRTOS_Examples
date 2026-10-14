# Author : Adhith IPCS
# ESP32 FreeRTOS Examples (Arduino framework)

This pack contains small, independent sketches for learning the FreeRTOS APIs exposed by Arduino-ESP32.

## Examples
1. Task creation and LED blink
2. Two concurrent tasks
3. Pinning a task to a CPU core
4. Queue producer/consumer
5. Binary semaphore
6. Mutex for shared output
7. Event groups
8. Direct-to-task notifications
9. Software timer
10. Periodic task with `vTaskDelayUntil`
11. Suspend and resume tasks
12. Passing parameters to tasks
13. Stack high-water monitoring
14. Button event queue and LED task
15. Queue carrying a structure (simulated sensor values)
16. Wi-Fi managed by a task
17. Watchdog-friendly task pattern
18. Basic heap/task information

## Upload using Arduino CLI (PowerShell)
Replace `COM5` with your ESP32 COM port. Run commands from the folder containing the selected `.ino` file.

```powershell
arduino-cli core update-index
arduino-cli core install esp32:esp32
arduino-cli board list
arduino-cli compile --fqbn esp32:esp32:esp32 .
arduino-cli upload -p COM5 --fqbn esp32:esp32:esp32 .
arduino-cli monitor -p COM5 -c baudrate=115200
```

The FQBN above is for a common ESP32 Dev Module. Use the exact FQBN for your board if different.

## Notes
- Open only one example at a time; each folder is a separate sketch.
- Set the correct LED/button pins for your board. GPIO 2 and GPIO 0 are common on some boards but are not universal.
- Example 16 requires your Wi-Fi SSID and password.
- These are educational starting points, not a complete production RTOS design.
- Arduino-ESP32 already runs on FreeRTOS. Do not call `vTaskStartScheduler()` in Arduino sketches.
- Use `vTaskDelay()` or blocking RTOS APIs rather than busy-wait loops in tasks.
- Stack sizes and watchdog APIs can vary by ESP32 variant and Arduino-ESP32 core version.
