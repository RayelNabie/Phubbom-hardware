//
// Created by Rayel Nabie on 31/05/2026.
//

#ifndef PHUBBOM_HARDWARE_MOTOR_HANDLER_H
#define PHUBBOM_HARDWARE_MOTOR_HANDLER_H

class MotorHandler {
private:
    static unsigned long pulseStartTime;
    static unsigned long pulseDuration;
    static bool isPulsing;

public:
    static void on();
    static void off();
    static void pulse(unsigned long durationMs);
    static void update();
    static bool isPulseActive();
};


#endif //PHUBBOM_HARDWARE_MOTOR_HANDLER_H
