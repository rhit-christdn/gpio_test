#include <lgpio.h>
#include <iostream>

int main() {
    static const int PIN = 18; // BCM GPIO 18

    int h = lgGpiochipOpen(0);
    if (h < 0) {
        std::cerr << "Failed to open GPIO chip 0, error: " << h << std::endl;
        return 1;
    }
    std::cout << "Opened GPIO chip 0 successfully.\n";

    int status = lgGpioClaimOutput(h, 0, PIN, 0);
    if (status < 0) {
        std::cerr << "Failed to claim GPIO " << PIN << " for output, error: " << status << std::endl;
        return 1;
    }
    std::cout << "Claimed GPIO " << PIN << " for output.\n";

    while (true) {
        std::cout << "Enter a percent for duty cycle (0-100): ";
        double dutyCycle;
        std::cin >> dutyCycle;

        if (dutyCycle < 0 || dutyCycle > 100) {
            std::cerr << "Invalid duty cycle. Please enter 0-100.\n";
            continue;
        }

        int slots_left = lgTxPwm(h, PIN, 1000, dutyCycle, 0, 0);
        if (slots_left < 0) {
            std::cerr << "Failed to start PWM, error: " << slots_left << std::endl;
        } else {
            std::cout << "PWM set: " << dutyCycle << "% duty at 1kHz on GPIO " << PIN << ". Queue slots left: " << slots_left << "\n";
        }
    }

    lgGpioFree(h, PIN);
    lgGpiochipClose(h);
    return 0;
}
