#include <pigpio.h>
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    static const int LED_PIN = 17; // BCM GPIO 17

    std::cout << "pigpio version: " << gpioVersion() << std::endl;

    if (gpioInitialise() < 0) {
        std::cerr << "pigpio initialization failed." << std::endl;
        return 1;
    }
    std::cout << "pigpio initialized successfully." << std::endl;

    // Set frequency if desired (default is ~800Hz)
    int frequency = gpioSetPWMfrequency(LED_PIN, 1000);
    std::cout << "PWM frequency set to: " << frequency << " Hz" << std::endl;

    int dutyCycle = 0;

    while (true) {
        gpioPWM(LED_PIN, dutyCycle); // Set PWM duty cycle

        std::cout << "Duty Cycle: " << (dutyCycle * 100 / 255) << "%" << std::endl;

        dutyCycle += (255 * 5) / 100; // Increase by 5%
        if (dutyCycle > 255) {
            dutyCycle = 0; // Reset to 0% after 100%
        }

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    gpioTerminate();
    return 0;
}
// Compile with: g++ -o main main.cpp -lpigpio -lrt -lpthread
// Run with: sudo ./main