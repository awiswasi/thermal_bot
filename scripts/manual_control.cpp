#include <wiringPi.h>
#include <iostream>

// Define GPIO pins for the motors
const int motor1Pin1 = 0; // GPIO 17
const int motor1Pin2 = 1; // GPIO 18
const int motor2Pin1 = 2; // GPIO 27
const int motor2Pin2 = 3; // GPIO 22
const int motor3Pin1 = 4; // GPIO 23
const int motor3Pin2 = 5; // GPIO 24
const int motor4Pin1 = 6; // GPIO 25
const int motor4Pin2 = 7; // GPIO 4

enum MOTOR_STATUS { ARMED, DISARMED };

int STATUS;

void setup() {
    wiringPiSetup();

    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
    pinMode(motor3Pin1, OUTPUT);
    pinMode(motor3Pin2, OUTPUT);
    pinMode(motor4Pin1, OUTPUT);
    pinMode(motor4Pin2, OUTPUT);
}

void enableMotor(int pin1, int pin2) {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
}

void disableMotor(int pin1, int pin2) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
}

int main() {
    setup();

    if (STATUS == ARMED) {
        std::cout << "Enabling motors..." << std::endl;

        // Enable all motors
        enableMotor(motor1Pin1, motor1Pin2);
        enableMotor(motor2Pin1, motor2Pin2);
        enableMotor(motor3Pin1, motor3Pin2);
        enableMotor(motor4Pin1, motor4Pin2);
    }
    if (STATUS == DISARMED) {
        std::cout << "Disabling motors..." << std::endl;

        // Disable all motors
        disableMotor(motor1Pin1, motor1Pin2);
        disableMotor(motor2Pin1, motor2Pin2);
        disableMotor(motor3Pin1, motor3Pin2);
        disableMotor(motor4Pin1, motor4Pin2);
    }

    return 0;
}
