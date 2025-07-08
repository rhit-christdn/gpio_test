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
    double percent = 50.0;

    while (true) {
        gpioPWM(LED_PIN, dutyCycle); // Set PWM duty cycle

        std::cout << "Enter a percentage to set the duty cycle (0-100): ";
        std::cin >> percent;
        if (percent < 0 || percent > 100) {
            std::cerr << "Invalid percentage. Please enter a value between 0 and 100." << std::endl;
            continue;
        }

        dutyCycle = (percent * 255) / 100; // Convert percentage to duty cycle (0-255)
        gpioPWM(LED_PIN, dutyCycle); // Update PWM with new duty cycle


        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    gpioTerminate();
    return 0;
}
// Compile with: g++ -o main main.cpp -lpigpio -lrt -lpthread
// Run with: sudo ./main