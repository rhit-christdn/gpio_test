#include <lgpio.h>
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    static const int PIN = 18; // BCM GPIO 17

    int h = lgGpiochipOpen(0); // Open GPIO chip 0

    while (true){
        std::cout << "Enter a percent for duty cycle (0-100): ";
        double dutyCycle;
        std::cin >> dutyCycle;

        lgTxPwm(h, PIN, 1000, dutyCycle, 0, 0);

    }

    // std::cout << "pigpio version: " << gpioVersion() << std::endl;

    // if (gpioInitialise() < 0) {
    //     std::cerr << "pigpio initialization failed." << std::endl;
    //     return 1;
    // }
    // std::cout << "pigpio initialized successfully." << std::endl;

    // // Set frequency if desired (default is ~800Hz) 
    // double dutyCycle = (50 / 100.0) * 1000000; // Convert percentage to 0-1000000 range
    // gpioHardwarePWM(PIN, 1000, dutyCycle);

    // double percent = 50.0;

    // while (true) {
    //     std::cout << "Enter a percentage to set the duty cycle (0-100): ";
    //     std::cin >> percent;
    //     if (percent < 0 || percent > 100) {
    //         std::cerr << "Invalid percentage. Please enter a value between 0 and 100." << std::endl;
    //         continue;
    //     }

    //     dutyCycle = (percent / 100.0) * 1000000;
    //     gpioHardwarePWM(PIN, 1000, dutyCycle); // Update PWM with new duty cycle/


    //     std::this_thread::sleep_for(std::chrono::seconds(2));
    // }

    // gpioTerminate();
    return 0;
}
// Compile with: g++ -o main main.cpp -llgpio -lrt -lpthread
// Run with: sudo ./main