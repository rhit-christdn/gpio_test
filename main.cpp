#include <lgpio.h>
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    static const int PIN = 18; // BCM GPIO 18 (hardware PWM capable)

    int h = lgGpiochipOpen(0); // Open GPIO chip 0
    if (h < 0) {
        std::cerr << "Failed to open GPIO chip 0, error: " << h << std::endl;
        return 1;
    }
    std::cout << "Opened GPIO chip 0 successfully.\n";

    while (true) {
        std::cout << "Enter a percent for duty cycle (0-100): ";
        double dutyCycle;
        std::cin >> dutyCycle;

        if (dutyCycle < 0 || dutyCycle > 100) {
            std::cerr << "Invalid duty cycle. Please enter a value between 0 and 100.\n";
            continue;
        }

        int status = lgTxPwm(h, PIN, 1000, dutyCycle);
        if (status < 0) {
            std::cerr << "Failed to set PWM, error: " << status << std::endl;
        } else {
            std::cout << "PWM set to " << dutyCycle << "% duty at 1kHz on GPIO " << PIN << ".\n";
        }
    }

    lgGpiochipClose(h);
    return 0;
}
