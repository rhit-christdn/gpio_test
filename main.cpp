#include <lgpio.h>
#include <iostream>
#include <thread>
#include <chrono>


int main() {
    static const int PIN1 = 18; // BCM GPIO 18
    static const int pin2 = 13; // BCM GPIO 13
    static const int pin3 = 17; // BCM GPIO 17

    int h = lgGpiochipOpen(0);
    if (h < 0) {
        std::cerr << "Failed to open GPIO chip 0, error: " << h << std::endl;
        return 1;
    }
    std::cout << "Opened GPIO chip 0 successfully.\n";

    // int status1 = lgGpioClaimOutput(h, 0, PIN1, 0);
    // if (status1 < 0) {
    //     std::cerr << "Failed to claim GPIO " << PIN1 << " for output, error: " << status1 << std::endl;
    //     return 1;
    // }
    // std::cout << "Claimed GPIO " << PIN1 << " for output.\n";

    // int status2 = lgGpioClaimOutput(h, 0, pin2, 0);
    int status2 = lgGpioClaimInput(h, pin2, 0);
    if (status2 < 0) {
        std::cerr << "Failed to claim GPIO " << pin2 << " for input, error: " << status2 << std::endl;
        return 1;
    } 
    std::cout << "Claimed GPIO " << pin2 << " for input.\n";

    // int statu3 = lgGpioClaimOutput(h, 8, pin3, 1);
    // if (statu3 < 0) {
    //     std::cerr << "Failed to claim GPIO " << pin3 << " for output, error: " << statu3 << std::endl;
    //     return 1;
    // }
    // std::cout << "Claimed GPIO " << pin3 << " for output.\n";

    // lgGpioWrite(h, pin3, 1); // Release button A

    while (true) {
        // std::cout << "Enter a percent for duty cycle1 (0-100): ";
        // double dutyCycle1;
        // std::cin >> dutyCycle1;

        // if (dutyCycle1 < 0 || dutyCycle1 > 100) {
        //     std::cerr << "Invalid duty cycle. Please enter 0-100.\n";
        //     continue;
        // }

        // int slots_left = lgTxPwm(h, PIN1, 1000, dutyCycle1, 0, 0);
        // if (slots_left < 0) {
        //     std::cerr << "Failed to start PWM, error: " << slots_left << std::endl;
        // } else {
        //     std::cout << "PWM set: " << dutyCycle1 << "% duty at 1kHz on GPIO " << PIN1 << ". Queue slots left: " << slots_left << "\n";
        // }

        // std::cout << "Enter a percent for duty cycle2 (0-100): ";
        // double dutyCycle2;
        // std::cin >> dutyCycle2;
        // if (dutyCycle2 < 0 || dutyCycle2 > 100) {
        //     std::cerr << "Invalid duty cycle. Please enter 0-100.\n";
        //     continue;
        // }
        // int slots_left = lgTxPwm(h, pin2, 1000, dutyCycle2, 0, 0);
        // if (slots_left < 0) {
        //     std::cerr << "Failed to start PWM, error: " << slots_left << std::endl;
        // } else {
        //     std::cout << "PWM set: " << dutyCycle2 << "% duty at 1kHz on GPIO " << pin2 << ". Queue slots left: " << slots_left << "\n";
        // }

        // std::cout << "enter '1' to press button A" << std::endl;
        // int button;
        // std::cin >> button;
        // if (button == 1) {
        //     lgGpioWrite(h, pin3, 0); // Press button A
        //     std::cout << "Button A pressed." << std::endl;
        //     std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate button press duratio
        //     lgGpioWrite(h, pin3, 1); // Release button A
        //     std::cout << "Button A released." << std::endl;
        // } else {
        //     std::cout << "Invalid input. Please enter '1' to press button A.\n";
        // }

        std::cout << "enter 'a' to turn left" << std::endl;
        std::cout << "enter 'd' to turn right" << std::endl;
        char key;
        std::cin >> key;
        if (key == 'a') {
            int status = lgGpioClaimOutput(h, 0, pin2, 0);
            if (status < 0) {
                std::cerr << "Failed to claim GPIO " << pin2 << " for output, error: " << statu3 << std::endl;
                return 1;
            }

            lgGpioWrite(h, pin2, 0);
            std::this_thread::sleep_for(std::chrono::seconds(5)); // Simulate button press duration

            int status2 = lgGpioClaimInput(h, pin2, 0);
            if (status2 < 0) {
                std::cerr << "Failed to claim GPIO " << pin2 << " for input, error: " << status2 << std::endl;
                return 1;
            } 
            std::cout << "Claimed GPIO " << pin2 << " for input.\n";
        } else if (key == 'd') {
            int status = lgGpioClaimOutput(h, 0, pin2, 0);
            if (status < 0) {
                std::cerr << "Failed to claim GPIO " << pin2 << " for output, error: " << statu3 << std::endl;
                return 1;
            }

            lgGpioWrite(h, pin2, 1);
            std::this_thread::sleep_for(std::chrono::seconds(5)); // Simulate button press duration

            int status2 = lgGpioClaimInput(h, pin2, 0);
            if (status2 < 0) {
                std::cerr << "Failed to claim GPIO " << pin2 << " for input, error: " << status2 << std::endl;
                return 1;
            } 
            std::cout << "Claimed GPIO " << pin2 << " for input.\n";
        }

    }

    lgGpioFree(h, PIN1);
    lgGpioFree(h, pin2);
    lgGpiochipClose(h);
    return 0;
}

//git clone lg.git & make install required
// g++ -o main main.c -llgpio -lrt -lpthread
// sudo ./main

