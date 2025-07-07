#include <pigpio.h>
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    static const int LED_PIN = 17; // GPIO pin for the LED

    int gpioResult = 0;

    std :: cout << "pigpio version: " << gpioVersion() << std::endl;

    std::cout << "Initializing pigpio..." << std::endl;
    gpioResult = gpioInitialise();

    if (gpioResult < 0) {
        std::cerr << "pigpio initialization failed with error code: " << gpioResult << std::endl;
        return 1; // Exit if initialization fails
    }
    std::cout << "pigpio initialized successfully." << std::endl;

    gpioResult = gpioSetMode(LED_PIN, PI_OUTPUT);
    if (gpioResult != 0) {
        switch (gpioResult) {
            case PI_BAD_USER_GPIO:
                std::cerr << "Error: Bad GPIO number." << std::endl;
                break;
            case PI_BAD_GPIO:
                std::cerr << "Error: GPIO not in range." << std::endl;
                break;
            case PI_BAD_MODE:
                std::cerr << "Error: Invalid mode." << std::endl;
                break;
            default:
                std::cerr << "Unknown error setting GPIO mode." << std::endl;
        }
    }   

    while (true) {
        gpioWrite(LED_PIN, 1); // Turn on the LED
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Wait for 500 milliseconds
        gpioWrite(LED_PIN, 0); // Turn off the LED
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Wait for 500 milliseconds
    }

    gpioTerminate(); // Clean up and terminate pigpio

    return 0;

}